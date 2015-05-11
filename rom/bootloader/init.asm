	;; Init Clay
	
	;; ################ SYSTEM INIT #################
	di			; disable maskable interrupts
	im	2		; use interrupt mode 2
	;; configure MMU (rom/ram 0/ram 1/ ram 7 -stack) data placed on data bus : xxwwdddd (w = register nb, d = data)
	;; 0x0000 ; 0x7FFF ; 0xBFFF ; 0xFFFF;
	;; 0x8000; 0xC000 ; 0x10000 ; 0x14000 ; 0x18000 ; 0x1C000 ; 0x20000 ; 0x24000
	xor	A				; MMU register 0 - low rom (rom page 0 - 0x0000)
	out	(MMU), A
	ld	A, MMU_REG1 | RAM_1		; MMU register 1 - ram (page 1 - 0x08000)
	out	(MMU), A

	;; configure base system
	ld	SP, 0x7FFF	; Stack temporarily set at the top of the ram page 1
	xor	A		; A = 0
	ld	I, A		; Interrupt mode 2 vector table address (high byte)	

	;; configure peripherals
	call	SIO_reset
	call	CTC_reset
        call	AY_reset
 	call	VDP_reset
	;; ##############################################
	
	call	copy_ROM_to_RAM
	ld	SP, 0x3FFF	; Stack set at the top of the ram page 1 (which will be placed at virtual addr 0x0000-0x3FFF)
	
ram_boot_swap:	;; RAM/ROM boot swap code (duplicated on RAM, to swap RAM and ROM after boot)
	ld	A, MMU_REG0 | RAM_1		; MMU register 0 - ram (page 1 - 0x08000)
	out	(MMU), A			; At this point, the low ROM has been swaped with the RAM page 1
	ld	A, MMU_REG1 | RAM_2		; MMU register 1 - ram (page 2 - 0x0C000)
	out	(MMU), A
	ld	A, MMU_REG2 | RAM_3;		; MMU register 2 - ram (page 3 - 0x10000)
	out	(MMU), A
	ld	A, MMU_REG2 | RAM_4;		; MMU register 3 - ram (page 4 - 0x10000)
	out	(MMU), A
	ei					; Enable interrupts (im mode 2)
	jp	basic				; Jump to basic main code
	;; -----------------------------
ram_boot_swap_end:	
