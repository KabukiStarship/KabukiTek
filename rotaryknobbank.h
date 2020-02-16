/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /rotary_knob_bank.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_ROTARYENCODERBANK
#define KABUKI_TEK_ROTARYENCODERBANK 1

#include "button.h"
#include "led.h"

namespace _ {

typedef enum { kNoButtons = 0, kButtonsTop, kButtonsBottom } LedRingConfig;

/* A bank of rotary encoders with LED rings and optional bank switch button(s).
Rotary encoder groups can have one or more banks of controls such as Aux
sends, etc. Banks are sequentially in the mixer starting at the
startChannel.
    


Switching Banks
---------------
Switching banks can be done using a single button that cycles through the
banks, or there can be a dedicated button per bank, or there can be no
buttons at all. The user inputs the number of buttons, and if it is one and
then numButtons is more than one, then that mode is chosen. If there is no
    


Wiring Configuration
--------------------
All Blue-Storm LED Encoder
Rings use 15 segments. All LED encoder rings use the same wiring patterns
that makes multiplexing code simple. ColA has 8 rows, and ColB has 7 rows.
The design can also include a 16th LED either on top or on bottom.
    


LEDRingConfig.kNoButtons
```
Row 8------------D8--------------SS------------D8
Row 7---------D7----D9-----------SS---------D7----D9
Row 6-------D6--------D10--------SS-------D6--------D10
Row 5------D5-----------D11------SS------D5-----------D11
Row 4-----D4-------------D12-----SS-----D4-------------D12
Row 3------D3-----------D13------SS------D3-----------D13
Row 2--------D2-------D14--------SS--------D2-------D14
Row 1----------D1---D15----------SS----------D1---D15
Col 1__________/___/_________________________/____/
Col 2__________/___/_________________________/
Col 2K________/___/
Col (2k + 1)__/
```

@todo There are three configurations of the LED encoder ring, the
ButtonsOnTop, and ButtonsOnBottom configurations.
    


The power for the LED comes from the shift register, so only one LED per
column may be on at one time. The rows will always be the same on every
control surface, but the columns will vary significantly. The rows will
always be on a single shift register but the columns will be stored as a
    


There will be both monochrome and RGB LEDs on the same buss, so the IUA
array will be shared by multiple.
*/
class KABUKI RotaryKnobBank {
 public:
  /* Constructor.
  @param num_knobs     Number of rotary encoders.
  @param num_banks     Number of banks.
  @param start_channel The starting channel on the mixer.
  @param rows          Pointer to row IUA.
  @param columns       Pointer to the array of column bytes. */
  RotaryKnobBank(ch_t num_knobs, ch_t start_channel, ch_t num_banks,
                 const IUA* rows, const IUA* columns);

  /* Gets the number of channels this bank controls. */
  ch_t GetNumChannels();

  /* Switches the bank to new value. */
  void SwitchBank(ch_t value);

  /* Cycles the bank. */
  void CycleBank();

  /* Frame update handler for the LEDs.
  This handler has a counter that counts from 0-255 in an infinite loop.
  Each time around the loop, all of the LEDs get turned on. */
  void Update(ISB* channel, ISB* min_values, ISB* max_values,
              IUA* spi_out_bytes, ISB row, int8_t count);

  /* Prints this object to a terminal. */
  Printer& Print(Printer& o) {
    /* Script operations. */
    const Operation* Star(char_t index, Expr * expr);

   private:
    ch_t channel_count_,   //< Number of knobs  (rotary encoders).
        start_channel_,    //< Start channel in the mixer.
        num_banks_,        //< Number of banks.
        num_buttons_,      //< Number of buttons.
        current_bank_,     //< Currently selected bank.
        current_channel_,  //< Current bank start channel in the mixer.
        wiring_config_;    //< RotaryEncoderBank wiring configuration.
    const IUA *rows_,      //< Pointer to the array of columns bits.
        *columns_;         //< Pointer to the array of columns bits.
    Button* buttons_;      //< Pointer to the array of buttons.
    Led* lights_;          //< Pointer to the array of LEDs.

    /* Updates the mixer channel number LED ring. */
    void UpdateChannel(IUB index, ISB * channels, ISB * min_values,
                       ISB * max_values, IUA * spi_out_bytes, IUB row,
                       IUA count);
  };

  class RotaryEncoderBankOp : public Operand {
   public:
    /* Constructs a RotaryEncoderBank Operation. */
    RotaryEncoderBankOp(RotaryKnobBank* object);

    /* Script operations. */
    virtual const Operation* Star(char_t index, Expr* expr);

   private:
    RotaryKnobBank* object_;  //< The RotaryEncoderBank.
  };
}  // namespace _
#endif
