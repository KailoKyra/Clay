	;; Interrupts of the SIO (chan A & B)

SIO_chan_B_received_char:
	;; Get the char from the SIO chan B
	;; put the chan B RX buffer addr (buffer struct (cursors + buffer) ?) in a register, jump on SIO_fill_buffer
	reti

SIO_chan_A_received_char:
	;; Get the char from the SIO chan A
	;; put the chan A RX buffer addr (buffer struct (cursors + buffer) ?) in a register, jump on SIO_fill_buffer
	reti

SIO_chan_B_transmit_buffer_empty:
	;; If the chan B TX buffer is not empty, load a new char on the SIO, move the cursor
	reti

SIO_chan_A_transmit_buffer_empty:
	;; If the chan B TX buffer is not empty, load a new char on the SIO, move the cursor
	reti
