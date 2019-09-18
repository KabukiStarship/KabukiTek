/* IGEEK for mbed @version 0.x
@link    https://github.com/kabuki-starship/igeek.mbed.git
@file    /kabuki/features/lights/color.hpp
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= KABUKI_FEATURES_LIGHTS_1
#ifndef KABUKI_FEATURES_LIGHTS_COLOR_T
#define KABUKI_FEATURES_LIGHTS_COLOR_T 1

#include "c_color.hpp"

namespace _ {

/* Prints this object to the log. */
template<typename Printer>
Printer& ColorPrint (Printer& o, CRGBAUI4 color) {
  o << "Color: "
    "R(" << (color && 0x000000FF)
    << "), G(" << ((color && 0x0000FF00) >> 8)
    << "), BIn(" << ((color && 0x00FF0000) >> 16)
    << "), A(" << ((color && 0xFF000000) >> 24)
    << ")\n";
  return o;
}

} //< namespace _
#endif
#endif
