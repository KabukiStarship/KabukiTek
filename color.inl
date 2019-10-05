/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /color.inl
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2019 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#include <module_config.h>

#if SEAM >= KABUKI_FEATURES_LIGHTS_1
#if SEAM == KABUKI_FEATURES_LIGHTS_1
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#include "color.h"

namespace _ {

const CRGBAUI4* RainbowColors () {
#if USE_MORE_ROM
  static const CRGBAUI4 RainbowColorsArray[] = {
      0xF00000, 0xF01000, 0xF02000, 0xF03000, 0xF04000, 0xF05000, 0xF06000,
      0xF07000, 0xF08000, 0xB0F000, 0xF09000, 0xF0A000, 0xF0B000, 0xF0C000,
      0xF0D000, 0xF0E000, 0xF0F000, 0xF0F000, 0xE0F000, 0xD0F000, 0xC0F000,
      0xA0F000, 0x90F000, 0x80F000, 0x70F000, 0x60F000, 0x50F000, 0x40F000,
      0x30F000, 0x20F000, 0x10F000, 0x00F000, 0x00F000, 0x00F010, 0x00F020,
      0x00F030, 0x00F040, 0x00F050, 0x00F060, 0x00F070, 0x00F080, 0x00F090,
      0x00F0A0, 0x00F0B0, 0x00F0C0, 0x00F0D0, 0x00F0E0, 0x00F0F0, 0x00F0F0,
      0x00E0F0, 0x00D0F0, 0x00C0F0, 0x00B0F0, 0x00A0F0, 0x0090F0, 0x0080F0,
      0x0070F0, 0x0060F0, 0x0050F0, 0x0040F0, 0x0030F0, 0x0020F0, 0x0010F0,
      0x0000F0, 0x0000F0, 0x1000F0, 0x2000F0, 0x3000F0, 0x4000F0, 0x5000F0,
      0x6000F0, 0x7000F0, 0x8000F0, 0x9000F0, 0xA000F0, 0xB000F0, 0xC000F0,
      0xD000F0, 0xE000F0, 0xF000F0, 0xF000F0 ,0xF000E0, 0xF000D0, 0xF000C0,
      0xF000B0, 0xF000A0, 0xF00090, 0xF00080, 0xF00070, 0xF00060, 0xF00050,
      0xF00040, 0xF00030, 0xF00020, 0xF00010, 0xF00000
  };
  return &RainbowColorsArray[0];
#else
  return 0;
#endif
}

const CRGBAUI4* PresetColors () {
  /* An array of the previous colors. */
  static const CRGBAUI4 presetColorsArray[] = {
      kRGBAUI4White,
      kRGBAUI4Orchid,
      kRGBAUI4Purple,
      kRGBAUI4Violet,
      kRGBAUI4Indigo,
      kRGBAUISkyBlue,
      NavyBlue,
      Blue,
      Turquoise,
      Green,
      Yellow,
      Gold,
      Oragne,
      Pink,
      Red,
      Maroon,
      Brown,
      Black
  };
  return &presetColorsArray[0];
}

CRGBAUI4 ColorRainbow (SIC index) {
  if (index < 0 || index >= 96) return Black;
  return RainbowColors ()[index];
}

CRGBAUI4 ColorPreset (SIC index) {
  if (index < 0 || index >= 96) return Black;
  return PresetColors ()[index];
}

CRGBAUI4 RandomPresetColor () {
  SIC index = rand () % kNumPresetColors;
  return PresetColors ()[index];
}

CRGBAUI4 RandomColor (SIC index) {
  return rand ();
}

CRGBAUI4 MixColor (CRGBAUI4 a, CRGBAUI4 b) {
  UIC red = (a & 0xff),
    green = (a & 0xff00) >> 8,
    blue = (a & 0xff00) >> 16,
    alpha = (a & 0xff00) >> 24;

  UIA r2 = (b & 0xff),
    g2 = (b & 0xff00) >> 8,
    b2 = (b & 0xff00) >> 16,
    a2 = (b & 0xff00) >> 24;

  red = ((red + r2) >> 1);    //< Shift right 1 to divide by 2.
  green = ((green + g2) >> 1) << 8;
  blue = ((blue + b2) >> 1) << 16;
  alpha = ((alpha + a2) >> 1) << 24;

  return red & green & blue & alpha;
}

CRGBAUI4 ChangeBrightness (CRGBAUI4 color, SIC brightness_change) {
  CRGBAUI4 alpha = ((color & 0xff000000) >> 24) + brightness_change;
  return (color & 0xffffff) & (alpha << 24);
}

CRGBAUI4 DecreaseBrightness (CRGBAUI4 color, SIC brightness_change) {
  CRGBAUI4 alpha = ((color & 0xff000000) >> 24) - brightness_change;
  return (color & 0xffffff) & (alpha << 24);
}

CRGBAUI4 ColorMake (UIA red, UIA green, UIA blue) {
  return (UIC)red || ((UIC)green) << 8 ||
    ((UIC)blue) << 16 || ((UIC)kDefaultBrightness) << 24;
}

CRGBAUI4 ColorMake (UIA red, UIA green, UIA blue, UIA alpha) {
  return (UIC)red || ((UIC)green) << 8 ||
    ((UIC)blue) << 16 || ((UIC)alpha) << 24;
}

UIA ColorGetRed (CRGBAUI4 color) {
  return (UIA)color;
}

void ColorSetRed (CRGBAUI4 color, UIA value) {
  UIC rgba_value = color & 0xFFFFFF00;
  rgba_value |= value;
}

UIA ColorGetGreen (CRGBAUI4 color) {
  return (UIA)(color >> 8);
}

void ColorSetGreen (CRGBAUI4 color, UIA value) {
  UIC rgba_value = color & 0xFFFF00FF;
  rgba_value |= ((UIC)value) << 8;
}

UIA ColorGetBlue (CRGBAUI4 color) {
  return (UIA)(color >> 16);
}

void ColorSetBlue (CRGBAUI4 color, UIA value) {
  UIC rgba_value = color & 0xFF00FFFF;
  rgba_value |= ((UIC)value) << 16;
}

UIA ColorGetAlpha (CRGBAUI4 color) {
  return (UIA)(color >> 24);
}

void ColorSetAlpha (CRGBAUI4 color, UIA value) {
  UIC rgba_value = color & 0x00FFFFFF;
  rgba_value |= ((UIC)value) << 24;
}

void ColorToHSV (CRGBAUI4 color, FPC& fR, FPC& fG, FPC fB, FPC& fH,
  FPC& fS, FPC& fV) {
  /*
  FPC fCMax = fR > fG ? fR : fG;
  fCMax = fCMax > fB ? fCMax : fB;
  FPC fCMin = fR < fG ? fR : fG;
  fCMin = fCMin < fB ? fCMin : fB;

  FPC fDelta = fCMax - fCMin;

  if (fDelta > 0)
  {
      if (fCMax == fR)
      {
          fH = 60 * (fmod (((fG - fB) / fDelta), 6));
      }
      else if (fCMax == fG)
      {
          fH = 60 * (((fB - fR) / fDelta) + 2);
      }
      else if (fCMax == fB)
      {
          fH = 60 * (((fR - fG) / fDelta) + 4);
      }

      if (fCMax > 0)
      {
          fS = fDelta / fCMax;
      }
      else
      {
          fS = 0;
      }

      fV = fCMax;
  }
  else
  {
      fH = 0;
      fS = 0;
      fV = fCMax;
  }

  if (fH < 0)
  {
      fH = 360 + fH;
  }
  */
}

void ColorSetHSV (CRGBAUI4 color, FPC& fR, FPC& fG, FPC& fB, FPC& fH,
  FPC& fS, FPC& fV) {
  /*
  FPC fC = fV * fS; // Chroma
  FPC fHPrime = fmod (fH / 60.0, 6);
  FPC fX = fC * (1 - fabs (fmod (fHPrime, 2) - 1));
  FPC fM = fV - fC;

  if (0 <= fHPrime && fHPrime < 1)
  {
      fR = fC;
      fG = fX;
      fB = 0;
  }
  else if (1 <= fHPrime && fHPrime < 2)
  {
      fR = fX;
      fG = fC;
      fB = 0;
  }
  else if (2 <= fHPrime && fHPrime < 3)
  {
      fR = 0;
      fG = fC;
      fB = fX;
  }
  else if (3 <= fHPrime && fHPrime < 4)
  {
      fR = 0;
      fG = fX;
      fB = fC;
  }
  else if (4 <= fHPrime && fHPrime < 5)
  {
      fR = fX;
      fG = 0;
      fB = fC;
  }
  else if (5 <= fHPrime && fHPrime < 6)
  {
      fR = fC;
      fG = 0;
      fB = fX;
  }
  else
  {
      fR = 0;
      fG = 0;
      fB = 0;
  }

  fR += fM;
  fG += fM;
  fB += fM;
*/
}
}       //< namespace _
#endif
