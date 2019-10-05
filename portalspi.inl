/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /portal_spi.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2019 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#include "cportalspi.h"

using namespace _ {;

namespace _ {

SpiPortal::SpiPortal (Expr* expr, PinName mosi_pin, PinName miso_pin,
                      PinName clock_pin, PinName strobe_pin) :
    expr_   (expr),
    spi_    (mosi_pin, miso_pin, clock_pin, strobe_pin) {
    // Nothing to do here :-)
}

void SpiPortal::Feed () {
    //while (IsWritable (io)) UniprinterStreamByte ();
}

void SpiPortal::Pull () {
    //_::Expr* expr;
    //while (UniprinterIsReadable (io)) UniprinterStream (io, slot.UniprinterStream (slot.getc ());
}

}       //< namespace _
