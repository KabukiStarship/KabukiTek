/* IGEEK for mbed @version 0.x
@link    https://github.com/kabuki-starship/igeek.mbed.git
@file    /motorhbridge.inl
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#include "c_motorhbridge.h"

namespace _ {

HBridgeMotor::HBridgeMotor(PinName pwn_pin, PinName forward_pin,
                           PinName reverse_pin)
    : pulse_(pwn_pin), forward_(forward_pin), reverse_(reverse_pin) {
  pulse_width_ = 0.0f;
  pulse_.period(0.0f);
  forward_ = 0;
  reverse_ = 0;
}

HBridgeMotor::~HBridgeMotor() {}

void HBridgeMotor::Stop() {
  forward_ = reverse_ = 0;  //< Turn off to GetPrevent any unwanted behavior.
  pulse_width_ = 0.0f;
}

void HBridgeMotor::Move(FP4 value) {
  forward_ = reverse_ = 0;  //< Turn off to GetPrevent any unwanted behavior.
  pulse_width_ = value;
  forward_ = value < 0.0f ? 1 : 0;
  reverse_ = value > 0.0f ? 1 : 0;
}

const Operation* HBridgeMotor::Star(char_t index, Expr* expr) {
  static const Operation This = {"HBridgeMotor", NumOperations(2),
                                 FirstOperation('A'), "An H-Bridge motor.", 0};

  void* args[1];

  switch (index) {
    case '?':
      return &This;
    case 'A': {
      static const Operation OpA = {"Stop", Params<NIL>(), Params<0>(),
                                    "Stops the motor.", 0};
      if (!expr) return &OpA;
      Stop();
      return 0;  //< No return values.
    }
    case 'b': {
      static const Operation OpB = {
          "Move", Params<1, FP4>(), Params<1>(),
          "Sets the motor to move forward  (0.0 - 1.0) or backwards "
          "(-1.0 - 0.0) for x seconds.",
          0};
      if (!expr) return &OpB;
      FP4 input;
      if (Args(expr, Params<1, FP4>(), Args(args, &input))) return expr->result;
      Move(input);
      return expr->result;
    }
  }
  return nullptr;
}

}  // namespace _
