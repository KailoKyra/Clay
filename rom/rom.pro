TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \

OTHER_FILES += \
    Makefile \
    basic/basic.asm \
    basic/basic_data.asm \
    devices/ctc/z80ctc/ctc.asm \
    devices/ctc/z80ctc/ctc_interrupts.asm \
    devices/ctc/z80ctc/ctc_registers_defines.asm \
    devices/sio/z80sio/sio.asm \
    devices/sio/z80sio/sio_interrupts.asm \
    devices/sio/z80sio/sio_registers_defines.asm \
    devices/sound/ay_3_8912/ay_registers_defines.asm \
    devices/vdp/tms9918/vdp.asm \
    kernel/interrupts/interrupts.asm \
    kernel/interrupts/interrupts_vector_table.asm \
    kernel/kernel.asm \
    kernel/kernel_data.asm \
    defines.asm \
    main.asm \
    devices/devices_defines.asm \
    devices/sio/z80sio/sio_defines.asm \
    devices/mmu/mmu_defines.asm \
    devices/ctc/z80ctc/ctc_defines.asm \
    devices/sound/ay_3_8912/ay_defines.asm \
    bootloader/copy_rom_to_ram.asm \
    bootloader/init.asm \
    devices/sound/ay_3_8912/ay.asm
