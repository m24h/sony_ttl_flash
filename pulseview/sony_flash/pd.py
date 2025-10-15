## Copyright (c) Johnny (https://github.com/m24h) <jjkkxyz@gmail.com> 
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, see <http://www.gnu.org/licenses/>.
##

from enum import Enum
import sigrokdecode as srd

'''
OUTPUT_PYTHON format:

Packet:
[<ptype>, <pdata>]

<ptype>:
 - 'READ' (Reading from flash, with bytearray pdata)
 - 'WRITE' (Writing to flash, with bytearray pdata)
 - 'EVENT' (other events than Read/Write, pdata can be 'PRE'/'FORMAL'/'TRIGGER'/'FLASHING'/'DUMB')
 - 'ERR' (Failed to decode, pdata can be 'TRUNCATED'/'NOISE')
'''

class Decoder(srd.Decoder):
    api_version=3
    id='sony_flash'
    name='Sony Flash'
    longname='Sony camera-flash protocol'
    desc='Two-wire, Sony camera-flash serial bus.'
    license='gplv2+'
    inputs=['logic']
    outputs=['sony_flash']
    tags=['Sony']
    channels=(
        {'id': 'clk', 'name': 'CLK', 'desc': 'F2:Serial clock line'},
        {'id': 'dat', 'name': 'DAT', 'desc': 'F3:Serial data line'},
    )
    optional_channels=(
        {'id': 'syn', 'name': 'Syn', 'desc': 'F1:Fire flash'},
    )
    options=()
    annotations=(
        ('data-command', 'F2 R/W Command'),
        ('data-read', 'F3 Data read'),
        ('data-write', 'F3 Data written'),
        ('events', 'Events'),
        ('err', 'Error'),
        ('sum', 'Data summary'),
    )
    annotation_rows=(
        ('data', 'Command/Data', (0, 1, 2)),
        ('flashing', 'Pre/formal Flash', (3,)),
        ('errors', 'Errors', (4,)),
        ('summary', 'Data Summary', (5,)),
    )
    binary=()

    def wait(self, cond):
        if not self.has_channel(2):
            return super().wait(cond)
        cond.append({2:'f'})
        while True:
            ret=super().wait(cond) # The timeout setting becomes inaccurate, but it doesn't matter
            if self.matched[-1]:
                self.put(self.samplenum, self.samplenum+1, self.out_python, ['EVENT', 'TRIGGER'])
                self.put(self.samplenum, self.samplenum+1, self.out_ann, [3, ['Trigger', 'Trig', 'T']])
            if any(self.matched[:-1]):
                return ret[:-1]

    def metadata(self, key, value):
        if key == srd.SRD_CONF_SAMPLERATE:
            self.samplerate=value

    def start(self):
        self.out_python=self.register(srd.OUTPUT_PYTHON)
        self.out_ann=self.register(srd.OUTPUT_ANN)
        self.reset()
                
    def reset(self):
        self.state=None
        
    def decode_byte(self):  
         # normally a byte starts 500us after R/W clock signal, and 9-14 bytes are done in 20ms, 1ms seems to be a good timeout value
        self.wait([{0:'r'}, {'skip': int(1.0e-3*self.samplerate)}])
        if not self.matched[0]:
            return None
        ss=self.samplenum
        val=0
        for i in range(8):
            if i>0:
                self.wait([{0:'r'}, {'skip': int(100.0e-6*self.samplerate)}]) # normally a bit uses 15-30us, 100us seems to be OK
                if not self.matched[0]:
                    self.put(ss, es, self.out_python, ['ERR', 'TRUNCATED'])
                    self.put(ss, es, self.out_ann, [4, ['Truncated', 'Trunc', 'T']])
                    return None
            pins=self.wait([{0:'f'}])
            es=self.samplenum
            val+=pins[1]<<i # LSB first
        return (val, ss, es)

    def decode(self):
        ss=self.samplenum
        es=self.samplenum
        while True:
            if self.state is None: #idle
                self.wait([{0:'r'}])
                ss=self.samplenum
                self.wait([{0:'f'}])
                es=self.samplenum
                dur=(es-ss)*1.0e6/self.samplerate # microsecond
                if dur>500: # seems to happen in camera initialization
                    self.put(ss, es, self.out_python, ['EVENT', 'DUMB'])
                    self.put(ss, es, self.out_ann, [3, ['Dumb', 'D']])
                elif dur>220: # normally pre-flash has a 270us preamble pulse in clock line
                    self.state=2
                elif dur>130: # normally writing has a 170us preamble pulse in clock line
                    self.put(ss, es, self.out_ann, [0, ['Write', 'W']]) 
                    self.state=1
                elif dur>60:  # normally reading has a 90us preamble pulse in clock line
                    self.put(ss, es, self.out_ann, [0, ['Read', 'R']])
                    self.state=0
                else:
                    self.put(ss, es, self.out_python, ['ERR', 'NOISE'])
                    self.put(ss, es, self.out_ann, [7, ['Noise', 'N']])
            elif self.state==0: # read, normally 9-11 bytes, 1 bytes per 500us, 15-30us per bit, LSB first
                bytes=bytearray()
                while True:
                    byte=self.decode_byte()
                    if byte is None:
                        self.put(ss, es, self.out_python, ['READ', bytes])
                        self.put(ss, es, self.out_ann, [5, ['R '+' '.join(['{:02X}'.format(b) for b in bytes])]])
                        self.state=None
                        break
                    else:
                        es=byte[2]
                        self.put(byte[1], byte[2], self.out_ann, [1, ['{:02X}'.format(byte[0])]])
                        bytes.append(byte[0])
            elif self.state==1: # write, normally 9 bytes, 1 bytes per 500us, 15-30us per bit, LSB first
                bytes=bytearray()
                while True:
                    byte=self.decode_byte()
                    if byte is None:
                        self.put(ss, es, self.out_python, ['WRITE', bytes])
                        self.put(ss, es, self.out_ann, [5, ['W '+' '.join(['{:02X}'.format(b) for b in bytes])]])
                        self.state=None
                        break
                    else:
                        es=byte[2]
                        self.put(byte[1], byte[2], self.out_ann, [2, ['{:02X}'.format(byte[0])]])
                        bytes.append(byte[0])                   
            elif self.state==2:  # pre-flash,  
                self.wait([{0:'r'}])
                t=self.samplenum
                self.wait([{0:'f'}])
                es=self.samplenum
                d=(es-t)*1.0e6/self.samplerate # microsecond
                if (60<d<130):
                    self.put(ss, es, self.out_python, ['EVENT', 'PRE'])
                    self.put(ss, es, self.out_ann, [3, ['Pre-flash', 'Pre', 'P']])
                else:
                    self.put(ss, es, self.out_python, ['EVENT', 'FORMAL'])
                    self.put(ss, es, self.out_ann, [3, ['Formal-flash', 'Frm', 'M']])
                self.wait([{1:'f'}])
                ss=self.samplenum
                self.wait([{1:'r'}])
                es=self.samplenum
                self.put(ss, es, self.out_python, ['EVENT', 'FLASHING'])
                self.put(ss, es, self.out_ann, [3, ['flashing', 'Fla', 'F']])
                self.state=None
                