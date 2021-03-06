/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /button.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_SENSOR_BUTTON
#define KABUKI_TEK_SENSOR_BUTTON

#include "mbed.h"

namespace _ {

/* A button stored as an offset.
Buttons are composed of a unsigned integer type that stores the bit offset
from the Controller. This bit offset then gets translated to a IUA offset
and a mask through some bit shifting.
*/
class Button {
 public:
  /* Constructs a button with the given bit offset. */
  Button(offset_t bit);

  /* Gets the state of the button. */
  inline IUA GetState(IUA* digital_ins);

  /* Polls the state of the switch using the debounced XOR. */
  inline void Poll(IUA* debounced_xor);

  /* Script operations. */
  const _::Op* Star(ISW index, _::Expr* expr);

 private:
  offset_t bit_offset_;  //< Offset to the packed button bits array.
  _::Event *press_,      //< Handler for button pressed event.
      *depress_,         //< Handler for button depressed event.
      *double_press_;    //< Handler for button depressed event.
};                       //< class Button

class ButtonOp : public _::Operand {
 public:
  /* Constructs a Button Operation. */
  ButtonOp(Button* object);

  /* Script operations. */
  virtual const _::Operation* Star(char_t index, _::Expr* expr);

 private:
  Button* object_;  //< Button object.
};                  //< class ButtonOp
}  // namespace _

#endif
