/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /io_expander.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2019 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <module_config.h>
#ifndef KABUKI_TEK_IO_EXPANDER
#define KABUKI_TEK_IO_EXPANDER 1

namespace _ {

/* A controller for multiple SPI ports that have varying number of bytes.

Different controller configurations will have a different number of input
and output shift registers, but they all share the same strobe_. At the
beginning of each cycle the strobe_ clocks in the data into the shift
registers then shifts in the input signals in, which outputs the LED data
for that frame. This is accomplished by finding the longest shift register
chain of all the SPI ports and a counter that increments in a loop. This
index is checked to see if it is greater than the number of input and output
shift registers, and data is only sent and received on the correct UIA
indexes.
    

@code
CHA OutputData[5];
SPIPort controller8 (D11, D12, D13, D10, 1, &OutputData[5], 4,
&OutputData[0]);
@endcode
*/
class IoExpander {
 public:
  /* Simple constructor.
  @param num_in_bytes  The number of input shift registers.
  @param num_out_bytes The number of output shift registers.
  @param num_rows      The number of rows. */
  IoExpander(UIA* buffer, UIA num_in_bytes, UIA num_out_bytes, PinName mosi_pin,
             PinName miso_pin, PinName clock_pin, PinName strobe_pin,
             UIC frequency);

  /* Gets the number of input registers. */
  UIA GetNumInBytes();

  /* Gets the number of output registers. */
  UIA GetNumOutBytes();

  /* Attaches the controller to to this spi_. */
  // void Attach (Controller* controller);

  /* Switches to the given row number. */
  // void SetDevice (UIA device_number);

  /* Gets the digital input UIA at the given index. */
  void Update(UIA index);

 private:
  SPI spi_;            //< SPI spi_.
  UIA num_in_bytes_,   //< Number of in bytes.
      num_out_bytes_;  //< Number of out bytes.
  UIA *in_bytes_,      //< Input buffer.
      *out_bytes_;     //< Output buffer.
};
}  // namespace _
#endif
