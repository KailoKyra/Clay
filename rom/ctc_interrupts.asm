	;; Interrupts of the CTC

CTC_chan_3_int:
	ex AF, AF'
	exx
	;; Keep track of an interrupt nb (1 to x ?)
	;; Update the system timer
	;; Reminder : we should limit the update of some procedures like the keyboard matrix to less than 300 times/sec. 30/sec should be more than enough
	call kernel_kb_scan		;; Update the keyboard matrix
	;; Should I provide some space if the user want to update their own routine ?
	ex AF, AF'
	exx
	ei
	reti			; Does reti reenable interrupts (ei) ? If not, add it before reti.