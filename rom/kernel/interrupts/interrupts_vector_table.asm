	;; -------------- INTERRUPTS VECTOR TABLE ---------------------
if $ & 1
	nop			; Interrupts should start on an even address.
endif

serial_int:			    ; (the vectors are in sio_interrupt.asm)
	dw dummy				; Chan B transmit buffer empty
	dw dummy				; Chan B external/status change
	dw SIO_chan_B_received_char 		; Chan B Received character is available
	dw dummy				;  Chan B Special Receive Condition (parity error, rx overrun, framing error...)
	dw SIO_chan_A_transmit_buffer_empty	; Chan A transmit buffer empty
	dw dummy				; Chan A external/status change
	dw SIO_chan_A_received_char		; Chan A Received character is available
	dw dummy				; Chan A Special Receive Condition (parity error, rx overrun, framing error...)

if $ | 0x02			; The CTC vectors should start at an address with D[0-2] bits low.
	ds 2
endif
if $ | 0x04
	ds 4
endif
ctc_int:
	dw dummy		; chan 0 (not used)
	dw dummy		; chan 1 (not used)
	dw dummy		; chan 2 (not used)
	dw CTC_chan_3_int	; chan 3 (300 ticks/sec. See ctc_interrupts.asm)

dummy:	reti
