@echo off
@setlocal EnableDelayedExpansion 

set sdcc_opts= -mmcs51 --model-small --stack-auto  --fsigned-char --opt-code-speed  --peep-return --peep-asm --peep-file peephole.txt --xram-size 1024 --code-size 8192 "-Wl -m,-M" "-Wa -v"

del my.lib 2>nul
for %%f in (stc\*.c) do (
	sdcc %sdcc_opts% -c %%f
	sdar r my.lib %%~nf.rel
	echo Add "%%f" to my.lib
)

for %%f in (*.c) do if /I not  "%%f"=="main.c" (
	sdcc %sdcc_opts% -c %%f
	sdar r my.lib %%~nf.rel
	echo Add "%%f" to my.lib
)

sdcc   %sdcc_opts% --out-fmt-ihx -o main.ihx -l my.lib main.c

packihx main.ihx >main.hex

makebin -p main.hex main.bin

findstr /c:"(REL," main.map

type main.mem
