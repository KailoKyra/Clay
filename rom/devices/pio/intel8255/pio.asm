        ;; I8255A PIO       - OUTDATED & NON USED.

PIO_reset:
	ld	A, PIO_CONFIG_PORT_A_OUTPUT_PORT_C_OUTPUT
	out	(PIO_CONTROL_PORT), A
	xor	A				; A = 0
	out	(PIO_PORT_A), A			; Clean the port A
	out	(PIO_PORT_C), A			; AY in disconnected mode

	;; The AY doesn't seems to need a proper reset, as every register is set to 0, and the port A is set as input.
	;; Will see later if we need to do a software reset.
	
	ret
