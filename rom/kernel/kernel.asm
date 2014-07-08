	;; Kernel functions (keyboard scan, interrupt handling, stuff like that)
kernel:
include 'kernel/kernel_data.asm'

	;; ===========================================================================
	;; =============Scan the keyboard, and update the keys state array============
	;; ============= AF, BC, HL are changed. (566 cycles, 141.5 µs)  ============
	;; ===========================================================================
kernel_kb_scan:
	ld	HL, K_KEYBOARD_MATRIX
	ld	B, 10				; number of rows to scan
	ld	C, PIO_PORT_A			; To read the matrix scan (ini instruction)
	;; We may need to save the current reg value to restore it. The user may need it.
	;; Same goes for the PIO ? Should I add a "backup var"
	;; We may also need to set the AY in disconnected state before setting it in latch mode
	ld	A, AY_REGISTER_SELECT_MODE 	; Set the AY in Latch reg. mode
	out	(PIO_PORT_C), A
	ld	A, AY_PORTA_REG			; We set the current AY register to AY port A reg
	out	(PIO_PORT_A), A
	ld	A, AY_DISCONNECTED_MODE 	; Set the AY back in its disconnected mode
	out	(PIO_PORT_C), A
	ld	A, PIO_CONFIG_PORT_A_INPUT_PORT_C_OUTPUT ; As we're going to read the AY portA, we set the PIO port A in input mode
	out	(PIO_CONTROL_PORT), A
	ld	A, AY_READ_FROM_PSG_MODE	; Put the AY in Read mode, first row
	kernel_kb_scan_loop:
		out	(PIO_PORT_C), A
		;; May need to put the AY back in disconnected mode here (as stated in the doc)
		;; But it may work if we stay in the same mode, will see).
		add	A, 16				; We increment the row n°, which is on the most most significant quartet
		ini					; Read the first row (HL) = (C); ++HL; --B
		jp	NZ, kernel_kb_scan_loop		; We loop until all rows have been scanned
	ld	A, AY_DISCONNECTED_MODE 	; We've finished to use the AY, so we set it in disconnected mode
	out	(PIO_PORT_C), A
	ld	A, PIO_CONFIG_PORT_A_OUTPUT_PORT_C_OUTPUT ; Set the AY back in its previous state
	;; (or restore its previous state via a backup var ?)
	out	(PIO_CONTROL_PORT), A
	ret
	;; ==========================================================================

	
kernel_end: