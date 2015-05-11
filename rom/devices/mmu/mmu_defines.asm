        ;; MMU
MMU:		equ 0x00        ; I/O handler address
        ;; MMU Registers
MMU_REG0:	equ 0x00	; 0x0000 to 0x3FFF
MMU_REG1:	equ 0x10	; 0x4000 to 0x7FFF
MMU_REG2:	equ 0x20	; 0x8000 to 0xBFFF
MMU_REG3:	equ 0x30	; 0xC000 to 0xFFFF
        ;; MMU Memory pages (use like this: "OUT (MMU), REG | page" to map a given page in a given REG). 16K/page
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
