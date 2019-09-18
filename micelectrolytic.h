/* IGEEK for mbed @version 0.x
@link    https://github.com/kabuki-starship/igeek.mbed.git
@file    /dmxreceiver.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#ifndef IGEEK_MBED_ELECTROLYTICMIC
#define IGEEK_MBED_ELECTROLYTICMIC 1

#include "c_photosensor.h"

namespace _ {

/* An electrolytic microphone. */
class ElectrolyticMic {
 public:
  /* Constructs . */
  ElectrolyticMic(PinName pin);

  /* Sets the minimum value to the given value. */
  UI2 GetMin();

  /* Sets the minimum value to the given value. */
  void SetMin(UI2 value);

  /* Gets the max value */
  UI2 GetMax();

  /* Attempts to set the max to the new value. */
  void SetMax(UI2 value);

  /* Bounds the min and max. */
  void BoundMinMax();

  /* Reads the value of the microphone. */
  UI2 Read();

  /* Prints this object to a terminal. */
  void Print();

 private:
  UI2 min_,         //< The normal min mic value.
      max_;         //< The normal max mic value.
  AnalogIn input_;  //< The analog input pin.
};
}  // namespace _
#endif
