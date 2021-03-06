/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /led_rgb.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#include "ledrgb.h"
//#include "../script/color.h"

namespace _ {

/* Creates an LEDRGB in the off position. */
LEDRGB::LEDRGB(CRGBAUI4 color, offset_t red_offset, offset_t green_offset,
               offset_t blue_offset)
    : color_(color),
      red_offset_(red_offset),
      green_offset_(green_offset),
      blue_offset_(blue_offset) {}

CRGBAUI4 LEDRGB::GetColor() { return color_; }

void LEDRGB::SetColor(CRGBAUI4 value) { color_ = value; }

IUA LEDRGB::GetRed() { return (IUA)color_; }

void LEDRGB::SetRed(CRGBAUI4 value) {
  CRGBAUI4 color = 0xffff00ff;  //< Mask for removing red channel.
  color &= color_;             //< Mask off the red value.
  color |= value << 8;         //< Add the new red channel.
}

IUA LEDRGB::GetGreen() { return (IUA)(color_ >> 8); }

void LEDRGB::SetGreen(CRGBAUI4 value) {
  CRGBAUI4 color = 0xffff00ff;  //< Mask for removing green channel.
  color &= color_;             //< Mask off the green value.
  color |= value << 8;         //< Add the new green channel.
}

IUA LEDRGB::GetBlue() { return (IUA)(color_ >> 16); }

void LEDRGB::SetBlue(CRGBAUI4 value) {
  CRGBAUI4 color = 0xff00ffff;  //< Mask for removing blue channel.
  color &= color_;             //< Mask off the blue value.
  color |= value << 8;         //< Add the new blue channel.
}

IUA LEDRGB::GetBrightness() { return (IUA)(color_ >> 24); }

void LEDRGB::SetBrightness(CRGBAUI4 value) {
  CRGBAUI4 color = 0x00ffffff;  //< Mask for removing brightness channel.
  color &= color_;             //< Mask off the brightness value.
  color |= value << 8;         //< Add the new brightness channel.
}

offset_t LEDRGB::GetRedOffset() { return red_offset_; }

offset_t LEDRGB::GetGreenOffset() { return green_offset_; }

offset_t LEDRGB::GetBlueOffset() { return blue_offset_; }

}  // namespace _
