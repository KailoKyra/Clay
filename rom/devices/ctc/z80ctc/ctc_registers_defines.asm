	;; CTC registers defines
	
CTC_CONTROL_MODE:	equ 0x01
	
	;; control mode flags
CTC_SOFT_RESET:		equ 0x02
TIME_CONSTANT_FOLLOWS:	equ 0x04
TIMER_TRIGGER_ENABLED:	equ 0x08 ; Clk/trg pulse stars timer if this bit is 1
CLK_TRG_RISING_EDGE:	equ 0x10
PRESCALER_16X:		equ 0x00
PRESCALER_256X:		equ 0x20
COUNTER_MODE:		equ 0x40
ENABLE_INTERRUPT:	equ 0x80