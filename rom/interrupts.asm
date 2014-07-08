interrupts:
	if $ >= 0x38		; if init is too big and overlap on the interrupt mode 1 vector
 		FAIL -> init overlap the interrupts code
	else
	  defs	0x38 - $	; pad the mode 1 interrupt vector to force it to 0x38
	endif
	;; Interrupt mode 1 code (unused)
	reti
	;; -------------- INTERRUPTS VECTOR TABLE ---------------------
include 'interrupts_vector_table.asm'
	;; Interrupts handlers
include 'sio_interrupts.asm'	;; SIO
include 'ctc_interrupts.asm'	;; CTC
interrupts_end:
