	;; This file contains all the global variables, buffers etc of the basic. prefix = BA(SIC)

test_message: db	"Clay - This is a test message",10,0

BA_input_buffer:	defs	0xFF	; User input buffer. Max 255 characters
BA_input_buffer_cursor:	db	0x00