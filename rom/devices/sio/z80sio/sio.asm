	;; Z80 SIO/0 or Z80 DART

SIO_reset:
	;; Channel A  (data K7)
	ld	A, CHANNEL_RESET
	out	(SIO_CHAN_A_C), A
	ld	A, SIO_WR4
	out	(SIO_CHAN_A_C), A ; Select WR4
	ld	A, NO_PARITY | ONE_STOP_BIT | X1_CLOCK
	out	(SIO_CHAN_A_C), A
	ld	A, SIO_WR5
	out	(SIO_CHAN_A_C), A ; Select WR5
	ld	A, TX_ENABLE | TX_DATA_8BITS | DATA_TERMINAL_READY
	out	(SIO_CHAN_A_C), A
	ld	A, SIO_WR1
	out	(SIO_CHAN_A_C), A ; Select WR1
	ld	A, INT_ON_ALL_RX_CHAR | TX_INT_ENABLE ;
	out	(SIO_CHAN_A_C), A
	
	;; Channel B (RS232)
	ld	A, CHANNEL_RESET
	out	(SIO_CHAN_B_C), A
	ld	A, SIO_WR4
	out	(SIO_CHAN_B_C), A ; Select WR4
	ld	A, NO_PARITY | ONE_STOP_BIT | X1_CLOCK
	out	(SIO_CHAN_B_C), A
	ld	A, SIO_WR5
	out	(SIO_CHAN_B_C), A ; Select WR5
	ld	A, TX_ENABLE | TX_DATA_8BITS | DATA_TERMINAL_READY
	out	(SIO_CHAN_B_C), A
	ld	A, SIO_WR1
	out	(SIO_CHAN_B_C), A ; Select WR1
	ld	A, INT_ON_ALL_RX_CHAR | TX_INT_ENABLE | STATUS_AFFECTS_VECTOR
	out	(SIO_CHAN_B_C), A

	;; chan A & B
	ld	A, SIO_WR2
	out	(SIO_CHAN_B_C), A ; Select WR2
	ld	A, serial_int	  ; vector defined in interrupts_vector_table.asm
	out	(SIO_CHAN_B_C), A ; Set the interrupt vector
	ld	C, SIO_CHAN_A_C
	call	SIO_enable_int
	ld	C, SIO_CHAN_B_C
	call	SIO_enable_int
	ret
	
	;; Enable RX int on chan A | B
	;; Parameter : load chan X control register in register C
SIO_enable_int:	
	ld	A, SIO_WR3
	out	(C), A
	ld	A, RX_ENABLE | RX_DATA_8BITS
	out	(C), A ; Enable rx on chan A
	ret

SIO_disable_int:
	ld	A, SIO_WR3
	out	(C), A
	ld	A, RX_DATA_8BITS
	out	(C), A ; Enable rx on chan B
	ret

	;; Ready to send ON/OFF (Flow Control)
	;; Parameter : load chan X control register in register C
SIO_RTS_on:
	ld	A, SIO_WR5
	out	(C), A
	ld	A, DATA_TERMINAL_READY | TX_DATA_8BITS | TX_ENABLE | REQUEST_TO_SEND
	out	(C), A
	ret

SIO_RTS_OFF:
	ld	A, SIO_WR5
	out	(C), A
	ld	A, DATA_TERMINAL_READY | TX_DATA_8BITS | TX_ENABLE
	out	(C), A
	ret
