	;; This file contains all the global variables, buffers and flags used by the kernel.

K_KEYBOARD_MATRIX:	defs	10, 0xFF	; The keyboard matrix is made of 10 * 8 bytes (80 flags, active low)
K_KEYBOARD_FLAGS:	db	0		; Capslock flag, ect

 ;K_MMU_STATE:		db	0 ; May not be useful for now