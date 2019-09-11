/* Kabuki Tek @version 0.x
@link    https://github.com/kabuki-starship/kabuki.tek.git
@file    /c_unicontroller.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#ifndef INCLUDED_KABUKI_FEATURE_TEK_UNICONTROLLER
#define INCLUDED_KABUKI_FEATURE_TEK_UNICONTROLLER 1

#include "c_button.h"
#include "c_debouncer.h"
#include "c_ioexpander.h"
#include "c_led.h"
#include "c_ledmatrix.h"
#include "c_ledrgb.h"
#include "c_portin.h"
#include "c_pot.h"
#include "c_rotaryknob.h"
#include "c_rotaryknobbank.h"

namespace _ {

/* Hardware control surface for MIDI and DMX.
A hardware control surface has knobs, buttons, LEDs, screens, sliders, clock
Synchronizers, and other types of electrical and digital IO. There are
typically a lot of LEDs that must be multiplexed. A control surface can
be only hooked up to a microcontroller, or it can be a combination of GPIO
and shift registers via SPI ports.

A Unicontroller may be expanded dynamically.

## 14 and 16-bit Values

MIDI and DMX both use the same method of channel LSB-MSB splitting. This
method splits the 14 or 16-bit value up into two 7 or 8-bit nibbles. For
MIDI channels 0-31 get mapped to channels 32-63.

## Components

* Mixer
* Potentiometers    } Knobs
* Rotary Encoders   }
* Buttons
* Monochrome LEDs
* Monochrome LED Rings
* RGB LEDs
* Touchscreen

## Mixer

Every knob has it's own mixer channel, which uses 16-bit unsigned integer
values. Buttons do not inherently have a mixer channel associated with them,
but additional mixer channels can be created by mapping Buttons to virtual
mixer channels (eventually).

## Controller and IoExpander Mixer Organization

The Controller and IoExpander both have the same format, allowing them
to share code.

[Pots][Rotary Encoders][Buttons][Misc]

## LED Multiplexing

@code
Button Buttons[] = {
}
@endcode
*/
class Unicontroller {
 public:
  enum {
    kDefaultLedBrightness = 128,
    kMaxMidiValue = 16383,  //< 2^14-1
    kNumAccellorationCurves = 3,
    kNumInBytes = 1,
    kNumOutBytes = 1,
  };

  /* Default constructor.
  @param leds The LEDs. */
  Unicontroller(UI1* mixer, ch_t num_channels, Led** leds, ch_t num_leds,
                LEDRGB** rgb_leds, ch_t num_rgb_leds, Button** buttons,
                ch_t num_buttons, Pot** Pots, ch_t num_pots, RotaryKnob** knobs,
                ch_t num_knobs, RotaryKnobBank** knob_banks, ch_t num_banks,
                // PortIn        ** port_in   , ch_t num_ports_in,
                IoExpander** extra_io, ch_t num_expanders);

  RotaryKnob** GetRotaryKnobs();
  Pot** GetPots();
  IoExpander** GetIoExpanders();
  // PortIn    ** GetPortsIn ();
  Led** GetLeds();
  LEDRGB** GetRgbLeds();

  /* Sets the RGB color mix for the LED. */
  void SetColorBalance(UI1 r, UI1 g, UI1 b);

  /* Update interrupt for the SPI port.
  FastDebouncer returns an XOR containing the state of which switches
  have changed. This is useful for triggering function pointers and
  detecting mechanical Encoders. What we will do is store the
  debounced switch results on the stack, and pass a pointer to this
  array into the Button and RotaryEncoder classes. */
  void PollInputs();

  /* Frame update handler for the LEDs. */
  void UpdateLEDs();

  /* Reads and writes bytes to all the SPI ports. */
  void UpdateSpiByte();

  /* Gets the timer count in microseconds. */
  SI4 GetTimerCount();

 private:
  UI1 brightness_,      //< Monochrome LED brightness.
      red_mix_,         //< Red LED mix.
      green_mix_,       //< Green LED mix.
      blue_mix_;        //< Blue LED mix.
  SI2 pulse_count_,     //< PWM counter.
      num_pulses_;      //< PWM pulses per cycle(rows * 256).
  ch_t spi_index_,      //< Index of the current SPI UI1.
      longest_chain_,   //< Longest SPI chain length.
      channel_count_,   //< Number of channels.
      num_leds_,        //< Number of Led(s).
      num_rgb_leds_,    //< Number of LEDRGB(s).
      num_buttons_,     //< Number of Button(s).
      num_pots_,        //< Number of Pot(s).
      num_knobs_,       //< Number of RotoaryKnob(s).
      num_knob_banks_,  //< Number of RotoaryKnobBank(s).
      // num_ports_in_,  //< Number of PortIn(s).
      num_expanders_;                  //< Number of IoExpander(s).
  Ticker ticker_;                      //< Controls update Ticker.
  Timer timer_;                        //< Microsecond timer.
  Debouncer<uintptr_t>** debouncers_;  //< Debouncers.
  Led** leds_;                         //< Array of Led(s).
  LEDRGB** rgb_leds_;                  //< Array of LEDRGB(s).
  RotaryKnob** knobs_;                 //< Pointers to RotaryKnob(s).
  Button** buttons_;                   //< Pointers to the Button(s).
  Pot** pots_;                         //< Pointers to Pot(s).
  IoExpander** extra_io_;              //< Pointers to IoExpander(s).
  // PortIn              ** ports_in_;      //< Number of PortIn(s).
  UI1* mixer_;  //< Mixer channels.
};              //< class Unicontroller

}  // namespace _
#endif
