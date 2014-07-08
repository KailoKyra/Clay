	;; defines of sio/0 registers bits

	;; RR0
RX_CHARACTER_AVAILABLE:	equ 0x01
INT_PENDING:		equ 0x02
TX_BUFFER_EMPTY:	equ 0x04
DATA_CARRIER_DETECT:	equ 0x08 ; The following are used with "external status interrupt" mode
RING_INDICATOR:		equ 0x10
CLEAR_TO_SEND:		equ 0x20
BREAK:			equ 0x80

	;; RR1
ALL_SENT:		equ 0x01
PARITY_ERROR:		equ 0x10
RX_OVERRUN_ERROR:	equ 0x20
FRAMING_ERROR:		equ 0x40

	;; RR2 (interrupt vector)

	;; WR0
;; first 3 bits are the register we want to write/read, then next 3 bits are the mode
NULL_CODE:		equ 0x00
RESET_EXT_STATUS_INT:	equ 0x10
CHANNEL_RESET:		equ 0x18
ENABLE_INT_ON_NEXT_RX:	equ 0x20
RESET_PENDING_TXINT:	equ 0x28
ERROR_RESET:		equ 0x30
RETURN_FROM_INT:	equ 0x38 ;accessible from chan A only

	;; WR1
EXT_INT_ENABLE:		equ 0x01
TX_INT_ENABLE:		equ 0x02
STATUS_AFFECTS_VECTOR:	equ 0x04
RX_INT_DISABLE:		equ 0x00
RX_INT_ON_FIRST_CHAR:	equ 0x08
INT_ON_ALL_RX_CHAR_PARITY_AFFECTS:	equ 0x10
INT_ON_ALL_RX_CHAR:	equ 0x18
WAIT_READY_ON_R_T:	equ 0x20
WAIT_READY_FUNCTION:	equ 0x40
WAIT_READY_ENABLE:	equ 0x80

	;; WR2 (interrupt vector)
	
	;; WR3
RX_ENABLE:		equ 0x01
SYNC_CHAR_LOAD_INIBHIT:	equ 0x02
ADDRESS_SEARCH_MODE:	equ 0x04
RX_CRC_ENABLE:		equ 0x08
ENTER_HUNT_PHASE:	equ 0x10
AUTO_ENABLE:		equ 0x20
RX_DATA_5BITS:		equ 0x00
RX_DATA_6BITS:		equ 0x80
RX_DATA_7BITS:		equ 0x40
RX_DATA_8BITS:		equ 0xC0

	;; WR4
NO_PARITY:		equ 0x00
PARITY_ENABLE:		equ 0x01
PARITY_EVEN:		equ 0x02
PARITY_ODD:		equ 0x00
ONE_STOP_BIT:		equ 0x04
ONE_HALF_STOP_BIT:	equ 0x08
TWO_STOP_BIT:		equ 0x0C
X1_CLOCK:		equ 0x00
X16_CLOCK:		equ 0x40
X32_CLOCK:		equ 0x80
X64_CLOCK:		equ 0xC0

	;; WR5
TX_CRC_ENABLE:		equ 0x01
REQUEST_TO_SEND:	equ 0x02
TX_ENABLE:		equ 0x08
SEND_BREAK:		equ 0x10
TX_DATA_5BITS:		equ 0x00
TX_DATA_6BITS:		equ 0x40
TX_DATA_7BITS:		equ 0x20
TX_DATA_8BITS:		equ 0x60
DATA_TERMINAL_READY:	equ 0x80 
