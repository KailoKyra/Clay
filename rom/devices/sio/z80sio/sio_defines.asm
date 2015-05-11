        ;; SIO/0
SIO:		equ 0x10        ; I/O handler address

SIO_CHAN_A:	equ 0x10
SIO_CHAN_B:	equ 0x11
SIO_CHAN_A_C:	equ 0x12	; Channel A control mode
SIO_CHAN_B_C:	equ 0x13	; Channel B control mode

SIO_RR0:	equ 0x00
SIO_RR1:	equ 0x01
SIO_RR2:	equ 0x02
SIO_WR0:	equ 0x00
SIO_WR1:	equ 0x01
SIO_WR2:	equ 0x02
SIO_WR3:	equ 0x03
SIO_WR4:	equ 0x04
SIO_WR5:	equ 0x05

include 'devices/sio/z80sio/sio_registers_defines.asm'
