#ifndef     _Z80CTC_H_
# define    _Z80CTC_H_

#include "defines.h"

// TODO : implement daisy chaining.

/*
 * ------------------
 * |CLK/TRG0      D0|
 * |ZC/TO0        D1|
 * |              D2|
 * |              D3|
 * |CLK/TRG1      D4|
 * |ZC/TO1        D5|
 * |              D6|
 * |              D7|
 * |CLK/TRG2
 * |ZC/TO2       /CE|
 * |             CS0|
 * |             CS1|
 * |CLK/TRG3     /M1|
 * |           /IORQ|
 * |             /RD|
 * |
 * |            /INT|
 * |             IEI|
 * |             IEO|
 * |                |
 * |/RESET      CLK |
 * ------------------
 */

# define            Z80CTC_DATA_IS_CONTROL_WORD     0x01            // usage : data & Z80CTC_DATA_IS_CONTROL_WORD
typedef union
{
    byte    data;
    struct
    {
        bit       is_control_or_vector      : 1;       // Vector (0) / Control (1)
        bit       soft_reset                : 1;       // No (0) / Yes (1)
        bit       time_constant_follows     : 1;       // No (0) / Yes (1)
        bit       timer_trigger_selection   : 1;       // Automatic trigger when time constant is loaded (0) / clk/trg input starts timer (1)       <- Timer mode only
        bit       clk_trg_edge_selection    : 1;       // Falling edge (0) / Rising edge (1)
        bit       prescaler_value           : 1;       // 16 (0) / 256 (1)
        bit       channel_mode              : 1;       // Timer mode (O) / Selects counter Mode (1)
        bit       interrupt_enable          : 1;       // No (0) / Yes (1)

    };
}                   t_z80ctc_control_word;

// An idea for the clock input would be to make a "Clock Input" object, with a cycle counter, edges, ect ect. For now, just use CPU clock t-cycle count.

typedef struct      s_z80ctc_channel
{
    t_z80ctc_control_word   control_reg;
    byte                    timer_reg;
    byte                    vector_reg;                 // Only useful with channel 0.
    byte                    counter;
    unsigned int            prescaler_cycle_counter;
    byte                    raise_interrupt;            // This goes to 1 when an interrupt have to be raised for that counter.
    byte                    is_init;                    // In case of reset, the channel must be setup before used.
}                   t_z80ctc_channel;

typedef struct          s_z80ctc
{
    t_z80ctc_channel    channel[4];
    byte                interrupt_request;
    byte                interrupt_channel_vector;
}                       t_z80ctc;

void            z80ctc_init(t_z80ctc *self);
void            z80ctc_write(t_z80ctc *self, byte cs, byte data);           // CS = the two channel_select pins
byte            z80ctc_read(t_z80ctc *self, byte cs);
void            z80ctc_update(t_z80ctc *self, unsigned int system_clock_tstates);

void            z80ctc_ack_interrupt_req(t_z80ctc *self);

#endif
