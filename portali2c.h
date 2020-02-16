/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /portal_i2c.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_I2C_PORTAL_H
#define KABUKI_TEK_I2C_PORTAL_H

namespace _ {

/* A Portal for a half-duplex I2C data link. */
class I2cPortal : public _::Portal {
  /* Constructor creates a loop back port. */
  I2cPortal(_::Expr* expr, PinName sda_pin, PinName scl_pin);

  /* Feeds tx messages through the a without scanning them. */
  virtual void Feed();

  /* Pulls rx messages through the a and runs them through the scanner. */
  virtual void Pull();

 private:
  _::Expr* expr_;  //< Expr for this Portal.
  I2C i2c_;        //< mbed Serial port.
};                 //< class I2CPortal
}  // namespace _
#endif
