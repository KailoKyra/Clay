	;;### test rom for Clay

include 'defines.asm'

	org	0x0000		;start
include 'init.asm'
include 'interrupts.asm'	;start at 0x038 - interrupt vector table and interrupt handlers
include 'kernel/kernel.asm'
include 'basic/basic.asm'

include 'copy_rom_to_ram.asm'	; init functions (copy_ROM_to_RAM)
include 'vdp.asm'		; VDP related functions
include 'ctc.asm'		; ctc related functions
include 'pio.asm'		; pio related functions
include 'sio.asm'		; sio related functions

if $ >= 0x4000
	FAIL -> Kernel and base basic code too big to fit in the first bank
endif
end
	;put here all non-vital base code ect ?