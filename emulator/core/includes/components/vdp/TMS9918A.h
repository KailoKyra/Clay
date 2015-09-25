#ifndef     TMS9918A_H_
# define    TMS9918A_H_

// Resolution : 256 * 192, 16 colors

#include "defines.h"

# define            TMS9918A_RAM_SIZE       (16*1024)

# define            TMS9918A_VIDEO_CLK      (10.738635f*MHZ)
# define            TMS9918A_PIXEL_CLK      (TMS9918A_VIDEO_CLK / 2f)
# define            TMS9918A_VDP_CLK        (TMS9918A_VIDEO_CLK / 3f)

# define            TMS9918A_CPU_CYCLES_PER_PIXEL_CYCLE_RATIO    (CPU_SPEED / TMS9918A_PIXEL_CLK)

# define            TMS9918A_LINES                          (262)
# define            TMS9918_ACTIVE_DISPLAY_START_LINE       (3 + 13 + 27)           // Vertical sync + Top blanking + Top border
# define            TMS9918_ACTIVE_DISPLAY_END_LINE         (TMS9918_ACTIVE_DISPLAY_START_LINE + 192)

# define            TMS9918A_SCREEN_WIDTH   (256 + 15 + 13)     // active area + borders
# define            TMS9918A_SCREEN_HEIGHT  (192 + 27 + 24)     // active area + borders

enum        e_TMS9918A_palette
{
    TRANSPARENT = 0,
    BLACK,
    MEDIUM_GREEN,
    LIGHT_GREEN,
    DARK_BLUE,
    LIGHT_BLUE,
    DARK_RED,
    CYAN,
    MEDIUM_RED,
    LIGHT_RED,
    DARK_YELLOW,
    LIGHT_YELLOW,
    DARK_GREEN,
    MAGENTA,
    GRAY,
    WHITE = 15
};

typedef struct      s_tms9918a
{
    byte            wait_for_reg_number;            // Flag used when writing data to a register in 2 steps
    byte            temp_data_reg;
    uint16          address_reg;
    byte            reg[8 + 1];

    byte            ram[TMS9918A_RAM_SIZE];
    uint32          output_screen[TMS9918A_SCREEN_WIDTH * TMS9918A_SCREEN_HEIGHT];

    float           pixel_clk_cycle_counter;
    uint16          current_scanline;
}                   t_tms9918a;

void            tms9918a_init(t_tms9918a *self);
byte            tms9918a_read(t_tms9918a *self, byte mode);
void            tms9918a_write(t_tms9918a *self, byte data, byte mode);
void            tms9918a_update(t_tms9918a *self, unsigned int system_clock_tstastes);

// REG 0 (0 0 0 0 0 0 M3 EV)
# define        TMS9918A_REG0                       (0)
# define        TMS9918A_REG0_MODE_FLAG_3           (0x40)
# define        TMS9918A_REG0_EXTERNAL_VDP_ENABLE   (0x80)      // 1 = enable
// REG 1 (4/16K BLANK IE M1 M2 0 SIZE MAG)
# define        TMS9918A_REG1                       (1)
# define        TMS9918A_REG1_4K_16K_SELECTION      (0x01)      // Should be set to 1 (I guess ?)
# define        TMS9918A_REG1_BLANK_ENABLE          (0x02)      // Causes the display to go blank. displays borders only. 1 = enable display
# define        TMS9918A_REG_1_INTERRUPT_ENABLE     (0x04)      // 1 = enable VDP interrupts
# define        TMS9918A_REG_1_MODE_FLAG_1          (0x08)
# define        TMS9918A_REG_1_MODE_FLAG_2          (0x10)
# define        TMS9918A_REG_1_SPRITE_SIZE          (0x40)      // 0 = 8x8bit sprites    ; 1 = 16x16 sprites
# define        TMS9918A_REG_1_MAGNIFICATION        (0x80)      // 1 = double the size of the sprite on screen
// REG 2 (0 0 0 0 NAME_TABLE_BASE_ADDRESS)
# define        TMS9918A_REG2                       (2)
// REG 3 (COLOR_TABLE_BASE_ADDRESS)
# define        TMS9918A_REG3                       (3)
// REG 4 (0 0 0 0 0 PATTERN_GENERATOR_BASE_ADDRESS)
# define        TMS9918A_REG4                       (4)
// REG 5 ( 0 SPRITE_ATTRIBUTE_TABLE_BASE_ADDRESS)
# define        TMS9918A_REG_5                      (5)
// REG 6 ( 0 0 0 0 0 SPRITE_PATTERN_GENERATOR_BASE_ADDRESS)
# define        TMS9918A_REG_6                      (6)
// REG 7 (TEXT_COLOR1(4BITS) TEXT_COLOR0/BACKDROP_COLOR(4BITS))
# define        TMS9918A_REG_7                      (7)
// STATUS REG (F 5S C FIFTH_SPRITE_NUMBER)
# define        TMS9918A_STATUS_REG                 (8)

#endif
