	;;### test rom for Clay

include 'defines.asm'

	org	0x0000		;start
include 'bootloader/init.asm'
include 'kernel/interrupts/interrupts.asm'	;start at 0x038 - interrupt vector table and interrupt handlers
include 'kernel/kernel.asm'
include 'basic/basic.asm'

include 'bootloader/copy_rom_to_ram.asm'	; init functions (copy_ROM_to_RAM)
include 'devices/vdp/tms9918/vdp.asm'		; VDP related functions
include 'devices/ctc/z80ctc/ctc.asm'		; ctc related functions
include 'devices/sound/ay_3_8912/ay.asm'	; ay related functions
include 'devices/sio/z80sio/sio.asm'		; sio related functions

if $ >= 0x4000
	FAIL -> Kernel and base basic code too big to fit in the first bank
endif
end
	;put here all non-vital base code ect ?
