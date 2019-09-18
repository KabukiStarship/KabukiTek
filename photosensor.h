/* IGEEK for mbed @version 0.x
@link    https://github.com/kabuki-starship/igeek.mbed.git
@file    /onfig.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#ifndef IGEEK_MBED_SENSORS_PHOTOSENSOR
#define IGEEK_MBED_SENSORS_PHOTOSENSOR 1

namespace _ {

/* A photosensor that detects light. */
class Photosensor {
 public:
  /* Constructs a photosensor. */
  Photosensor(PinName pin);

  /* Reads the photosensor. */
  FP4 Read();

  const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  AnalogIn input_;
};

class PhotosensorOp {
 public:
  /* Constructs a photosensor. */
  PhotosensorOp(Photosensor* photosensor);

  const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  Photosensor* photosensor_;
};
}  // namespace _
#endif
