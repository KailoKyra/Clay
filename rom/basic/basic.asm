	;; ClayBasic main code

basic:	
	ld	BC, test_message
	loop:
		ld	A, (BC)
	       	out	(DEBUG), A

	;		ld	A, (K_KEYBOARD_MATRIX)
	;		out	(DEBUG), A
	;		ld	A, (BC)

	
		or	A		; a | a = 0 ? (faster than cp 0)
		jp Z,	basic		; print the message again
		inc	BC

		call	CTC_chan_3_int	; temp. Testing CTC chan 3 interrupt (300ticks/sec) (kb scan ect)
	
		jp	loop
	
include 'basic/basic_data.asm'
basic_end: