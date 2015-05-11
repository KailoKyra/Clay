	;; ClayBasic main code

basic:	
    jp basic        ; tmp test

print_sentence:
	ld	BC, test_message
	loop:
                ld	A, (BC)
             ;  	out	(DEBUG), A

	;		ld	A, (K_KEYBOARD_MATRIX)
	;		out	(DEBUG), A
	;		ld	A, (BC)

                or	A		; a | a = 0 ? (faster than cp 0)
                jp Z,	print_sentence_end	; print the message again
                inc	BC
		jp	loop

print_sentence_end:
        ret

include 'basic/basic_data.asm'
basic_end:

