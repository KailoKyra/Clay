TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    lib/libz80/z80.c                               \
    src/main.c                                     \
    src/clay.c                                     \
    src/components/74xx/74xx138.c                  \
    src/components/74xx/74xx145.c                  \
    src/components/74xx/74xx386.c                  \
    src/components/74xx/74xx574.c                  \
    src/components/ctc/z80ctc.c                    \
    src/components/keyboard/keyboard.c             \
    src/components/sio/z80sio.c                    \
    src/components/vdp/TMS9918A.c \
    src/mmu.c \
    src/io_handler.c \
    src/components/pio/intel_8255.c \
    src/components/sound/ay_3_8912.c \
    src/components/sound/audio_output.c \
    src/utils/circular_buffer.c


OTHER_FILES += \
    Makefile

HEADERS += \
    includes/clay.h                                     \
    lib                                                 \
    includes/components/74xx/74xx138.h                  \
    includes/components/74xx/74xx145.h                  \
    includes/components/74xx/74xx386.h                  \
    includes/components/74xx/74xx574.h                  \
    includes/components/ctc/z80ctc.h                    \
    includes/components/keyboard/keyboard.h             \
    includes/components/sio/z80sio.h                    \
    includes/components/vdp/TMS9918A.h \
    includes/defines.h \
    includes/mmu.h \
    includes/io_handler.h \
    includes/components/components.h \
    includes/components/pio/intel_8255.h \
    includes/components/sound/ay_3_8912.h \
    includes/components/sound/audio_output.h \
    includes/utils/circular_buffer.h

INCLUDEPATH += .                                        \
                lib                                     \
                includes                                \
                includes/components

