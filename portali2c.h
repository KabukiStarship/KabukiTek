/* IGEEK for mbed @version 0.x
@link    https://github.com/kabuki-starship/igeek.mbed.git
@file    /portali2c.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#ifndef IGEEK_MBED_I2C_PORTAL_H
#define IGEEK_MBED_I2C_PORTAL_H

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
