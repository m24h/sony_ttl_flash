## Copyright (C) Johnny (https://github.com/m24h) <jjkkxyz@gmail.com> 
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
'''
Sony camera-flash communication protocol.
bus using two signals (F2 = serial clock line (flash ready pin for older camera-flash),  F3 = serial data line (TTL OK pin for older camera-flash)).
'''

from .pd import Decoder
