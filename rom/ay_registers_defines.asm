	;; AY-3-891x registers defines

	;; Tone period control registers (12bits values)
AY_CHAN_A_TONE_FINE_REG:	equ 0x00	; Fine 8-bits tone period
AY_CHAN_A_TONE_COARSE_REG:	equ 0x01	; Coarse 4-bits tone period
AY_CHAN_B_TONE_FINE_REG:	equ 0x02
AY_CHAN_B_TONE_COARSE_REG:	equ 0x03
AY_CHAN_C_TONE_FINE_REG:	equ 0x04
AY_CHAN_C_TONE_COARSE_REG:	equ 0x05
	
	;; Noise generator control register (5 bits)
AY_NOISE_PERIOD_REG:		equ 0x06
	
	;; Multi-usage "!Enable" register
AY_ENABLE_REG:			equ 0x07
	;; Theses are flags to be used in the ENABLE reg.
AY_ENABLE_PORTA:		equ 0x40
AY_ENABLE_NOISE_ON_CHAN_C:	equ 0x20
AY_ENABLE_NOISE_ON_CHAN_B:	equ 0x10
AY_ENABLE_NOISE_ON_CHAN_A:	equ 0x08
AY_ENABLE_TONE_ON_CHAN_C:	equ 0x04
AY_ENABLE_TONE_ON_CHAN_B:	equ 0x02
AY_ENABLE_TONE_ON_CHAN_A:	equ 0x01

	;; Amplitude control registers
AY_CHAN_A_AMPLITUDE_REG:	equ 0x08 ; |Enveloppe on/off|volume (5 bits)
AY_CHAN_B_AMPLITUDE_REG:	equ 0x09
AY_CHAN_C_AMPLITUDE_REG:	equ 0x0A

	;; Envelope generator control (16 bits)
AY_ENVELOPE_FINE_TUNE_REG:	equ 0x0B ; 8bits envelope Fine tune
AY_ENVELOPE_COARSE_TUNE_REG:	equ 0x0C ; 8bits envelope Coarse tune

	;; Envelope Shape Cycle control (4 bits)
AY_ENVELOPE_SHAPE_CONTROL_REG:	equ 0x0D
AY_ENVELOPE_SHAPE_HOLD:		equ 0x01
AY_ENVELOPE_SHAPE_ALTERNATE:	equ 0x02
AY_ENVELOPE_SHAPE_ATTACK:	equ 0x03
AY_ENVELOPE_SHAPE_CONTINUE:	equ 0x04

	;; I/O Port A register (8 bits R/W)
AY_PORTA_REG:			equ 0x0E
	