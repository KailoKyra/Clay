TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.asm    \
    clayrom.rom \
    ay_registers_defines.asm \
    copy_rom_to_ram.asm \
    ctc.asm \
    ctc_interrupts.asm \
    ctc_registers_defines.asm \
    defines.asm \
    init.asm \
    interrupts.asm \
    interrupts_vector_table.asm \
    pio.asm \
    pio_registers_defines.asm \
    sio.asm \
    sio_interrupts.asm \
    sio_registers_defines.asm \
    vdp.asm \
    basic/basic.asm \
    basic/basic_data.asm \
    kernel/kernel.asm \
    kernel/kernel_data.asm


OTHER_FILES += \
    Makefile
