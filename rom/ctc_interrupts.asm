	;; Interrupts of the CTC

CTC_chan_3_int:
	ex AF, AF'
	exx
	;; Keep track of an interrupt nb (1 to x ?)
	;; Update the system timer
	;; Reminder : we should limit the update of some procedures like the keyboard matrix to less than 300 times/sec. 30/sec should be more than enough
        ;call kernel_kb_scan		;; Update the keyboard matrix
        call print_sentence
	;; Should I provide some space if the user want to update their own routine ?
        exx
        ex AF, AF'
	ei
        reti
