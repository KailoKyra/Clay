	;; Z80 CTC

CTC_reset:
	;; CH0 (tape baud rate)
	ld	A, CTC_CONTROL_MODE | CTC_SOFT_RESET | TIME_CONSTANT_FOLLOWS | PRESCALER_256X	; no int
	out	(CTC_CHAN_0), A
	ld	A, 6		; 1843200 / (256 * 6) = 1200 baud (check if it work irl)
	out	(CTC_CHAN_0), A

	;; CH1 (serial baud rate)
	ld	A, CTC_CONTROL_MODE | CTC_SOFT_RESET | TIME_CONSTANT_FOLLOWS | PRESCALER_16X	; no int
	out	(CTC_CHAN_1), A
	ld	A, 12		; 1843200 / (16 * 12) = 9600 baud
	out	(CTC_CHAN_1), A

	;; CH2 (unused)
	ld	A, CTC_CONTROL_MODE | CTC_SOFT_RESET
	out	(CTC_CHAN_2), A

	;; CH3 (time ticks, 300 per sec)
	ld	A, CTC_CONTROL_MODE | CTC_SOFT_RESET | TIME_CONSTANT_FOLLOWS | PRESCALER_256X | ENABLE_INTERRUPT
	out	(CTC_CHAN_3), A
	ld	A, 24		; 1843200 / (256*24) ~= 300 int / sec

	;; Vector Address
	ld	A, ctc_int	  ; vector defined in interrupts_vector_table.asm
	out	(CTC_CHAN_0), A
	
	ret
