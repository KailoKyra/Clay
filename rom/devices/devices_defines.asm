        ;; Clay-related devices defines.

include 'devices/mmu/mmu_defines.asm'
include 'devices/sio/z80sio/sio_defines.asm'
include 'devices/ctc/z80ctc/ctc_defines.asm'
include 'devices/sound/ay_3_8912/ay_defines.asm'


        ;; Debug in/out peripheral (works only with the clay emulator)
DEBUG:		equ 0x80        ; I/O handler address
