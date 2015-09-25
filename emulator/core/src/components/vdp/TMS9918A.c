#include <string.h>

#include "components/vdp/TMS9918A.h"

static const uint32      g_tms9918a_palette_toRGB[16] =
{
    0x00000000,     //TRANSPARENT,
    0xFF000000,     //BLACK,
    0xFF3EB849,     //MEDIUM_GREEN,
    0xFF74D07D,     //LIGHT_GREEN,
    0xFF5955E0,     //DARK_BLUE,
    0xFF8076F1,     //LIGHT_BLUE,
    0xFFB95E51,     //DARK_RED,
    0xFF65DBEF,     //CYAN,
    0xFFDB6559,     //MEDIUM_RED,
    0xFFFF897D,     //LIGHT_RED,
    0xFFCCC35E,     //DARK_YELLOW,
    0xFFDED087,     //LIGHT_YELLOW,
    0xFF3AA241,     //DARK_GREEN,
    0xFFB766B5,     //MAGENTA,
    0xFFCCCCCC,     //GRAY,
    0xFFFFFFFF,     //WHITE
};


void        tms9918a_init(t_tms9918a *self)
{
    memset(self, 0, sizeof(t_tms9918a));
}


byte        tms9918a_read(t_tms9918a *self, byte mode)
{
    if (mode & 1)
    {
        self->wait_for_reg_number = 0;                      // The doc specifies that this flag is reset when reading the status reg.
        return (self->reg[TMS9918A_STATUS_REG]);
    }
    else
    {
        const byte data = self->ram[self->address_reg];
        self->address_reg = (self->address_reg + 1) & TMS9918A_RAM_SIZE;
    }
}


void        tms9918a_write(t_tms9918a *self, byte data, byte mode)
{
    if (mode & 1)       // Write to a register mode (2 successive write, the data and (0x80 | reg))
    {
        if (self->wait_for_reg_number)
        {
            if ((data & 0xF8) == 0x80)                          // If we're waiting for a reg nr and it's valid (0x80 | 3 LSB)
                self->reg[data & 7] = self->temp_data_reg;
            else if (((data & 0xC0) == 0x40) || ((data & 0xC0) == 0x00))                     // Test the two first bit if it's a write to the address reg (0x40 in write mode, 0x00 in read mode)
                self->address_reg = (self->temp_data_reg << 8) | (data & 0x3F);
        }
        else
            self->temp_data_reg = data;
        self->wait_for_reg_number = !self->wait_for_reg_number;
    }
    else
    {
        self->ram[self->address_reg];
        self->address_reg = (self->address_reg + 1) & TMS9918A_RAM_SIZE;
    }
}




/*
 *      PARAMETER                           PIXEL CLOCK CYCLES
 *  HORIZONTAL                         PATTER OR MULTI          TEXT
 * -----------------------------------------------------------------
 * HORIZ ACTIVE DISPLAY                     256                 240
 * RIGHT BORDER                             15                  25
 * RIGHT BLANKING                           8                   8
 * HORIZONTAL SYNC                          26                  26
 * LEFT BLANKING                            2                   2
 * COLOR BURST                              14                  14
 * LEFT BLANKING                            8                   8
 * LEFT BORDER                              13                  19
 *
 * Total                                    342                 342
 *___________________________________________________________________
 *
 *  VERTICAL                                   LINE
 *-------------------------------------------------------------------
 * VERTICAL ACTIVE DISPLAY                      192
 * BOTTOM BORDER                                24
 * BOTTOM BLANKING                              3
 * VERTICAL SYNC                                3
 * TOP BLANKING                                 13
 * TOP BORDER                                   27
 *
 * Total                                        262 (242 outputed lines)
 */

/*
 * M1 M2 M3
 * 0  0  0  Graphics I mode
 * 0  0  1  Graphics II mode
 * 0  1  0  Multicolor Mode
 * 1  0  0  Text Mode
 * */
void        tms9918a_update(t_tms9918a *self, unsigned int system_clock_tstastes)
{
    const unsigned int    new_pixel_clk_counter = self->pixel_clk_cycle_counter + (system_clock_tstastes * TMS9918A_CPU_CYCLES_PER_PIXEL_CYCLE_RATIO);

    for (int i = self->pixel_clk_cycle_counter; i < new_pixel_clk_counter; ++i)
    {
        ++current_scanline;
        /*
         *
  // Increment scanline
  if (++VDP->Line>=VDP->Scanlines)
    VDP->Line=0;

  /* If refreshing display area, call scanline handler
  if ((VDP->Line>=TMS9918_ACTIVE_DISPLAY_START_LINE) && (VDP->Line<TMS9918_ACTIVE_DISPLAY_END_LINE))
    if (VDP->UCount>=100)
      Screen9918[VDP->Mode].LineHandler(VDP,VDP->Line-TMS9918_START_LINE);

  // If time for VBlank...
  if (VDP->Line==TMS9918_END_LINE)
  {
    // If drawing screen...
    if (VDP->UCount>=100)
    {
      // Refresh screen
      RefreshScreen(VDP->XBuf,VDP->Width,VDP->Height);
      // Reset update counter
      VDP->UCount-=100;
    }

    // Decrement/reset update counter
     VDP->UCount += DP->DrawFrames;
    */
        if (self->current_scanline == TMS9918A_LINES)
            ;
    }
    self->pixel_clk_cycle_counter += (system_clock_tstastes * TMS9918A_CPU_CYCLES_PER_PIXEL_CYCLE_RATIO);
}
