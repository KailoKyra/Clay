Clay
====

A Z80-based computer.

The emulator uses the Z80 emulation library from : https://github.com/ggambetta/libz80

Hardware
====

- Z80 CPU @ 4Mhz
- 128K SRAM, 32K ROM
- AY-3-8912 sound chip
- Intel 8255 for the sound chip, misc control lines and keyboard matrix lines scanning.
- Z80 SIO/0 serial interface for serial and tape recorder
- Z80 CTC for baudrate generation and time
- TMS9918A
