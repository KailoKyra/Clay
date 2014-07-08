	;; Transfert and place all the vital bios informations, buffers, values ect in RAM page 0, mapped on virtual page 1.

copy_ROM_to_RAM:
	ld	HL, ram_boot_swap 			; rom/ram swap code (to continue the execution on RAM after init)
	ld	DE, 0x4000 + ram_boot_swap 		; virtual page 1 + ram_boot_swap function offset
	ld	BC, ram_boot_swap_end - ram_boot_swap
	ldir
	
	ld	HL, 0x0038				; source (interrupts vector table)
	ld	DE, 0x4000 + 0x0038			; dest (virtual page 1 + 0x38)
	ld	BC, interrupts_end - interrupts		; Copy the interrupts code in RAM
	ldir

	ld	HL, kernel
	ld	DE, 0x4000 + kernel
	ld	BC, kernel_end - kernel
	ldir

	ld	HL, basic
	ld	DE, 0x4000 + basic
	ld	BC, basic_end - basic
	ldir
	
	ret
