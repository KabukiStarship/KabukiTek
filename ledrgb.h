/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /led_rgb.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2019 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <module_config.h>
#ifndef KABUKI_TEK_RGBLED
#define KABUKI_TEK_RGBLED 1

namespace _ {

/* A Red-Green-Blue LED.
Type UIA is going to be a integer type used for storing
@todo There needs to be a camera setup that scans the LEDs on the board and
stores an offset, like +/-16, that allows for adjusting brighter LEDs.
Its not a problem till we've determined it is a problem. */
class LEDRGB {
 public:
  /* Creates an LEDRGB in the off position. */
  LEDRGB(CRGBAUI4 color, offset_t r, offset_t g, offset_t b);

  /* Gets the color. */
  CRGBAUI4 GetColor();

  /* Sets the color to the new value. */
  void SetColor(CRGBAUI4 rgba);

  /* Gets the red channel. */
  UIA GetRed();

  /* Sets the red channel to the new value. */
  void SetRed(CRGBAUI4 value);

  /* Gets the green channel. */
  UIA GetGreen();

  /* Sets the green channel to the new value. */
  void SetGreen(CRGBAUI4 value);

  /* Gets the blue channel. */
  UIA GetBlue();

  /* Sets the blue channel to the new value. */
  void SetBlue(CRGBAUI4 value);

  /* Gets the brightness channel. */
  UIA GetBrightness();

  /* Sets the brightness channel to the new value. */
  void SetBrightness(CRGBAUI4 value);

  /* Gets the red LED offset. */
  offset_t GetRedOffset();

  /* Gets the green LED offset. */
  offset_t GetGreenOffset();

  /* Gets the blue LED offset. */
  offset_t GetBlueOffset();

 private:
  CRGBAUI4 color_;    //< RGBA color where A is additive brightness.
  ch_t red_offset_,   //< Red LED bit offset.
      green_offset_,  //< Green LED bit offset.
      blue_offset_,   //< Blue LED bit offset.
      reserved_;      //< Reserved for memory alignment.
};
}  // namespace _
#endif
