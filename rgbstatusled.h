/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /led_status_rgb.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2019 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <module_config.h>
#ifndef KABUKI_TEK_RGBSTATUSLED
#define KABUKI_TEK_RGBSTATUSLED 1

namespace _ {

#define _CreateRGBStatusLED \
  static RGBStatusLED<0, 1> Status(RED_LED, GREEN_LED, BLUE_LED);

#define Assert                                                              \
  (statement, message) {                                                    \
    if (!(statement)) {                                                     \
      printf("Assert: %s\r\n%s, line %d\r\n", #message, __FILE__, __LINE__) \
          Status.HandleAssert() while (true)                                \
    }                                                                       \
  }

namespace Primary {

typedef enum {
  Black = 0,
  Red = 1,
  Yellow = 2,
  Green = 3,
  Cyan = 4,
  Blue = 5,
  Magenta = 6,
  White = 7
} Color;
}  // namespace Primary

/* The on-board mbed RGB LED.
Some boards have PWM on the RGB LED, some don't. This class uses
DigitalOut (s). There are 8 potential combinations of color without PWM
(@wiki:"Color Space"), Black, Red, Yellow, Green, Cyan, Blue, Magenta, and
White.
    


@code
RGBStatusLED<0, 1> stausLED  (RED_LED, GREEN_LED, BLUE_LED);
//< Use <0, 1> if you're LED is active low.
RGBStatusLED<1, 0> stausLED  (p0, p1, p2);
//< Use <0, 1> if you're LED is active high.
    


status_led.SetColorA  (Color::);
    


@endcode
*/
template <SIC On, SIC Off>
class RGBStatusLED {
 public:
  enum { DefaultBrightness = 128 };

  /* Simple constructor. */
  RGBStatusLED(PinName red_pin, PinName green_pin, PinName blue_pin,
               FPC blink_delay = 0.2f)
      : frequency(aFrequency),
        red(red_pin),
        green(green_pin),
        blue(blue_pin),
        blinker(),
        color(Color::Black),
        colorA(Color::Black),
        colorB(Color::Black) {
    red = green = blue = 1;
  }

  /* Updates the RGB status LED "frame": color. */
  void Update() {
    switch (color) {
      case Color::Black:
        red = 1;
        green = 1;
        blue = 1;
        return;
      case Color::Red:
        red = 0;
        green = 1;
        blue = 1;
        return;
      case Color::Yellow:
        red = 0;
        green = 0;
        blue = 1;
        return;
      case Color::Green:
        red = 1;
        green = 0;
        blue = 1;
        return;
      case Color::Cyan:
        red = 1;
        green = 0;
        blue = 0;
        return;
      case Color::Blue:
        red = 1;
        green = 1;
        blue = 0;
        return;
      case Color::Magenta:
        red = 0;
        green = 1;
        blue = 0;
        return;
      case Color::White:
        red = 0;
        green = 0;
        blue = 0;
        return;
    }
  }

  /* Sets colorA. */
  void SetColorA(Primary::Color value) { colorA = value; }

  /* Sets colorB. */
  void SetColorB(Primary::Color value) { colorB = value; }

  /* Turns off the blinker. */
  void TurnOff() { red = green = blue = 1; }

  /* Turns on the blinker. */
  void TurnOn() {
    color = colorA;
    Update();
  }

  /* Sets the color of the blinker. */
  void SetColors(Primary::Color ColorA,
                 Primary::Color ColorB = Primary::Black) {
    colorA = ColorA;
    colorB = ColorB;
  }

  /* Starts flashing red and blue lights. */
  void FlashRedBlue() {
    colorA = Primary::Red;
    colorB = Primary::Blue;
    StartBlinking();
  }

  /* Starts blinking. */
  void StartBlinking() {
    blinker.attach(this, &RGBStatusLED::Blink, frequency);
    color = colorA;
    Update();
  }

  /* Stops blinking and turns off the LED. */
  void StopBlinking() {
    TurnOff();
    blinker.detach();
    color = Primary::Black;
    Update();
  }

  /* Starts blinking and turns on Color A. */
  void StopBlinkingA() {
    color = colorA;
    blinker.detach();
  }

  /* Starts blinking and turns on Color B. */
  void StopBlinkingB() {
    color = colorB;
    blinker.detach();
  }

  /* Sets the blink frequency. */
  void SetFrequency(FPC value) {
    frequency = value;
    blinker.attach(this, &RGBStatusLED::Blink, value);
  }

  /* Handler for the Assert macro. */
  void HandleAssert() { FlashRedBlue() }

 private:
  FPC frequency_;   //< The frequency of the blinking.
  DigitalOut red_,  //< Red LED on the mbed board.
      green_,       //< Green LED on the mbed board.
      blue_;        //< Blue LED on the mbed board.
  Ticker blinker_;  //< Ticker for blinking the LEDs.
  uint8_t color_,   //< The current color.
      colorA_,      //< Blink color A.
      colorB_;      //< Blink color B.

  /* Blinks the status RGB LED on the mbed board between colorA and
  colorB. */
  void Blink() {
    color = (color == colorA) ? colorB : colorA;
    Update();
  }
};
}  // namespace _

// _D_e_m_o_____________________________________________________________________

#if 0  //< Set to non-zero to run this demo.

using namespace kabuki - tek;

RGBStatusLED Status (LED_RED, LED_GREEN, LED_BLUE);
InterruptIn Switch3 (SW3);

/* Interrupt handler for SW2. */
void SW3Handler () {
    static SIC counter = 16;

    if (++counter > 15) {
        Status.FlashRedBlue (); counter = 0;
    } else if (counter & 1) {
        Status.StopBlinking ();
    } else {
        Status.SetColorA ((Primary::Color)(counter >> 1));
        Status.SetColorB (Primary::Black);
        Status.StartBlinking ();
    }
}

SIC main () {
    printf ("\r\nTesting mbed utils.\r\n");
    PrintLine ('-');

    Switch3.rise (&SW3Handler);
    //Status.StartBlinking ();

    while (true);
}
#endif
#endif
