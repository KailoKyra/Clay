        ;; AY-3-8912
AY:                         equ 0x30        ; I/O handler address

AY_READ:                    equ 0x31
AY_WRITE:                   equ 0x30
AY_REGISTER_LATCH:          equ 0x31

include 'devices/sound/ay_3_8912/ay_registers_defines.asm'
