/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /_seams/_main.cpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#include "_config.h"
#pragma once

int main () {
    // Setup Unicontroller
    RgbLed            tl_border_leds (0, 6,  5,   7),
                      tm_order_leds  (0, 10,  9,  8),
                      tr_border_leds (0, 24, 25, 26),
                      bl_border_leds (0,  6,  5,  7),
                      bm_border_leds (0, 13, 14, 15),
                      br_border_leds (0, 26, 25, 24);
    Pot               pot1           (0, A0),
                      pot2           (1, A1),
                      pot3           (2, A2),
                      pot4           (3, A3),
                      pot5           (4, A4),
                      pot6           (5, A5),
                      pot7           (6, A5),
                      pot8           (7, A5);
    RotaryKnob        enc1           (8, 0, 0),
                      enc2           (9, 0, 0),
                      enc3           (10, 0, 0),
                      enc4           (11, 0, 0),
                      enc5           (12, 0, 0),
                      enc6           (13, 0, 0),
                      enc7           (14, 0, 0),
                      enc8           (15, 0, 0),
                      enc9           (16, 0, 0),
                      enc10          (17, 0, 0),
                      enc11          (18, 0, 0);
    Button            sw1            (19),
                      sw2            (20),
                      enc1_sw        (21),
                      enc2_sw        (22);
    Led** leds = nullptr;
    RgbLed* rgb_leds[] = { &tl_border_leds, &tm_order_leds, &tr_border_leds,
                           &bl_border_leds, &bm_border_leds,
                           &br_border_leds };
    Pot* pots[] = { &pot1, &pot2, &pot3, &pot4, &pot5, &pot6, &pot7,
                    &pot8 };
    RotaryKnob* knobs[] = { &enc1, &enc2, &enc3, &enc4, &enc5, &enc6, &enc7,
                            &enc8, &enc9, &enc10, &enc11 };
    Button* buttons[] = { &sw1, &sw2, &enc1_sw, &enc2_sw };

    static const byte top_led_rows[] = {       1 << 0,      //< 1
                                               1 << 1,      //< 2
                                               1 << 2,      //< 3
                                               1 << 3,      //< 4
                                               1 << 4,      //< 5
                                               1 << 5,      //< 6
                                               1 << 6,      //< 7
                                               1 << 7 };    //< 8
    static const byte top_led_columns[] = {    20,          //< 1
                                               17,          //< 2
                                               18,          //< 3
                                               19,          //< 4
                                               16,          //< 5
                                               21,          //< 6
                                               22,          //< 7
                                               23,          //< 8
                                               11,          //< 9
                                               12,          //< 10
                                               13,          //< 11
                                               14,          //< 12
                                               15,          //< 13
                                               4,           //< 14
                                               3,           //< 15
                                               2,           //< 16
                                               1,           //< 17
                                               0 };         //< 18
    static const byte bottom_led_rows[] = {    1 << 4,      //< 1
                                               1 << 5,      //< 2
                                               1 << 6,      //< 3
                                               1 << 7,      //< 4
                                               1 << 0,      //< 5
                                               1 << 1,      //< 6
                                               1 << 2,      //< 7
                                               1 << 3 };    //< 8
    static const byte bottom_led_columns[] = { 4,           //< 1
                                               3,           //< 2
                                               2,           //< 3
                                               8,           //< 4
                                               9,           //< 5
                                               10,          //< 6
                                               11,          //< 7
                                               12,          //< 8
                                               23,          //< 9
                                               22,          //< 10
                                               21,          //< 11
                                               20,          //< 12
                                               19,          //< 13
                                               18,          //< 14
                                               17,          //< 15
                                               16,          //< 16
                                               0,           //< 17
                                               1, };        //< 18

    RotaryKnobBank bank1 (8, 1, 1, top_led_rows, top_led_columns),
                   bank2 (8, 1, 1, bottom_led_rows, bottom_led_columns);

    RotaryKnobBank* knob_banks[] = { &bank1, &bank2 };

    uint32_t spi_frequency = 250000;

    //PortIn port1 (Port1, 0);
    //PortIn** ports_in[] = { &port1 };

    byte spi_buffer_[14];
    IoExpander top_io     (&spi_buffer_[0 ], 5, 4, D11, D12, D13, D10,
    		               spi_frequency),
               bottom_io  (&spi_buffer_[13], 0, 8, D11, D12, D13, D10,
		                   spi_frequency);
    IoExpander* extra_io[] = { &top_io, &bottom_io };

    ch_t num_channels = 21;
    byte mixer[3 * num_channels];
    Unicontroller ctrlr (mixer     , num_channels,
                         leds      ,  0,
                         rgb_leds  ,  6,
                         buttons   ,  2,
                         pots      ,  8,
                         knobs     , 11,
						 knob_banks,  2,
                         //ports_in, 1,
                         extra_io  , 2);
}
