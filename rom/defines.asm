	;; defines

	;; Peripherals addresses :
	;; MMU
MMU:		equ 0x00
	;; MMU Registers
MMU_REG0:	equ 0x00	; 0x0000 to 0x3FFF
MMU_REG1:	equ 0x10	; 0x4000 to 0x7FFF
MMU_REG2:	equ 0x20	; 0x8000 to 0xBFFF
MMU_REG3:	equ 0x30	; 0xC000 to 0xFFFF
	;; MMU Memory pages (to use with OUT (MMU), REG | page)
LO_ROM:		equ 0x00	; contain base system code, interrupts, common functions ... Part of it are duplicated on RAM page 1
HI_ROM:		equ 0x01	; misc functions (kernel, basic...) and data
RAM_1:		equ 0x02
RAM_2:		equ 0x03
RAM_3:		equ 0x04
RAM_4:		equ 0x05
RAM_5:		equ 0x06
RAM_6:		equ 0x07
RAM_7:		equ 0x08
RAM_8:		equ 0x09

	;; SIO/0
SIO:		equ 0x10
	
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
include 'sio_registers_defines.asm'

	;; CTC
CTC:		equ 0x20
	
CTC_CHAN_0:	equ 0x20
CTC_CHAN_1:	equ 0x21
CTC_CHAN_2:	equ 0x22
CTC_CHAN_3:	equ 0x23
include 'ctc_registers_defines.asm'

	;; PIO
PIO:		equ 0x30

PIO_PORT_A:	equ 0x30
PIO_PORT_B:	equ 0x31
PIO_PORT_C:	equ 0x32
PIO_CONTROL_PORT:	equ	0x33
include 'pio_registers_defines.asm'

	;; AY-3-8912 (accessible through the PIO)
	;; PIO port C
AY_DISCONNECTED_MODE:	equ 0x00
AY_READ_FROM_PSG_MODE:	equ 0x02
AY_WRITE_TO_PSG_MODE:	equ 0x01
AY_REGISTER_SELECT_MODE:	equ 0x03
include 'ay_registers_defines.asm'
	
	;; Debug in/out peripheral (works only with the clay emulator)
DEBUG:		equ 0x80
