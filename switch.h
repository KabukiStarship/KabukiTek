/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /switch.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_BOUNCYSWITCH
#define KABUKI_TEK_BOUNCYSWITCH 1

#include <mbed.h"

namespace _ {

/* A software debounced switch. */
class Switch : public _::Operation {
 public:
  /* A software debcounced switch. */
  Switch(PinName din_pin);

  /* Script operations. */
  const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  DigitalIn input_;  //< The DIN pin.
};

class SwitchOp : public _::Operation {
 public:
  SwitchOp(Switch* sw);

  virtual const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  Switch* object_;  //< The Switch.
};                  //< SwitchOp
}  // namespace _
#endif
