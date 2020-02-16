/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /flying_fader.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_FLYING_FADER
#define KABUKI_TEK_FLYING_FADER 1

namespace _ {

/* A bank of one or more groups of flying faders.
    Flying faders on most mixers have pages full of controls, and work similar
    to the RotaryEncoder class.
*/
class FlyingFader {
 public:
  /* Constructs a blank flying fader. */
  FlyingFader();

  /* Prints this object to a console. */
  void Print();

  const _::Operation* Star(char_t index, _::Expr* expr);

 private:
};

class FlyingFaderOp {
 public:
  FlyingFaderOp(FlyingFader* ff);

  virtual const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  FlyingFader* ff_;  //< Pointer to the selected FlyingFader object.
};
}  // namespace _
#endif
