/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /dmx_receiver.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_DMX_DMXRECIEVER_H
#define KABUKI_TEK_DMX_DMXRECIEVER_H

namespace _ {

/* DMXReceiver receiver.
@param kChannelCount  The number of DMX channels  (must be less than 512).
 */
template <IUC kChannelCount>
class DMXReceiver {
 public:
  enum {
    kNumDMXChannels = 512,
    kDMXStartCode = 0,
    kDMXTimeBreak = 100,  // 100us (88us-1s)
    kDMXTimeMAB = 12,     // 12us  (8us-1s)
    DMXTimeMBB = 200      // 10us  (0-1s)
  };

  enum DMXModes {
    kStateBegin,
    kStateDMXStart,
    kStateMode,
    kStateMAB,
    kStateData,
    kStateError,
    kStateDMXStop,
  };

  /* Simple constructor.
  @param TxPin UART Tx pin.
  @param RxPin UART Rx pin. */
  DMXReceiver(PinName TxPin, PinName RxPin) : rawSerial(Tx, Rx) {
    Clear();
    // state = kStateBegin;
    state_ = kStateBegin;
    dataReceived = 0;
    dataSent = 0;
    memset(buffer, 0, sizeof(buffer));
    memset(data_rx, 0, sizeof(data_rx));
    timeBreak = kDMXTimeBreak;
    timeMAB = kDMXTimeMAB;
    timeMBB = DMXTimeMBB;

#if defined(TARGET_LPC1768) || defined(TARGET_LPC2368)
    if (p_rx == p10) {
      uart = LPC_UART3;
      NVIC_SetPriority(UART3_IRQn, 1);
    } else if (p_rx == p14) {
      uart = (LPC_UART_TypeDef*)LPC_UART1;
      NVIC_SetPriority(UART1_IRQn, 1);
    } else if (p_rx == p27) {
      uart = LPC_UART2;
      NVIC_SetPriority(UART2_IRQn, 1);
    }
#elif defined(TARGET_LPC11U24)
    if (p_rx == p10) {
      uart = LPC_USART;
      NVIC_SetPriority(UART_IRQn, 1);
    }
#elif defined(TARGET_K64F) || defined(TARGET_KL46Z)
    // Need to associate the _uart private variable with the user selected pin.
    //  Hook the interrupt pin.
    if ((p_rx == PTE21) || (p_rx == PTA1)) {
      _uart = (UARTLP_Type *)UART0;
      NVIC_SetPriority(UART0_IRQn, 1);
    } else if (p_rx == PTE1) {
      _uart = (UARTLP_Type *)UART1;
      NVIC_SetPriority(UART1_IRQn, 1);
    } else if ((p_rx == PTE23) || (p_rx == PTE17)) {
      _uart = (UARTLP_Type *)UART2;
      NVIC_SetPriority(UART2_IRQn, 1);
    }
#endif

    serial.baud(250000);
    serial.format(8, Serial::None, 2);
    serial.attach(this, &DMXReceiver::InitSerial, Serial::RxIrq);

    // timeout.attach_us  (this, &DMXReceiver::InitTimer, DMX_TIME_BETWEEN);
  }

  /* Send the data
  @param Index DMX channel 0-511.
  @param Value   DMX channel data 0-255. */
  void SetChannel(IUB Index, IUA Value) {
    if (Index >= kNumDMXChannels || Index < StartChannel ||
        Index > StartChannel + kChannelCount - 1) {
      return;
    }

    buffer[Index] = Value;
  }

  /* Gets the channel data at the given index.
  @param Index DMX channel 0-511.
  @param Value   DMX channel data 0-255. */
  IUA GetChannel(IUC index) {
    if (index >= StartChannel + kChannelCount) return 0;
    return data[index];
  }

  /* Send the data
      @param Buffer  DMX data buffer
      @param Index DMX data address
      @param Length  Data length */
  void Copy(IUA* Buffer, ISC Index = 0, ISC Length = kNumDMXChannels) {
    if (Index >= kNumDMXChannels || Length > kNumDMXChannels - Index ||
        Buffer == nullptr)
      return;
    memcpy(buf, &data_rx[Index], len);
  }

  /* Start DMX send operation */
  void Start() {
    if (state_ == kStateDMXStop) {
      state_ = kStateBegin;
      dataSent = 0;
      timeout.attach_us(this, &DMXReceiver::InitTimer, timeMBB);
    }
  }

  /* Stop DMX send operation */
  void Stop() {
    serial.attach(0, Serial::TxIrq);
    timeout.detach();
    state_ = kStateDMXStop;
  }

  /* Clear DMX data */
  void Clear() {
    ISC i;

    for (i = 0; i < kNumDMXChannels; i++) {
      buffer[i] = 0;
      data_rx[i] = 0;
    }
  }

  /* Marks the DMX data as being received. */
  ISC MarkReceived() {
    ISC r = dataReceived;
    dataReceived = 0;
    return r;
  }

  /* Marks data as being sent. */
  ISC MarkSent() {
    ISC r = dataSent;
    dataSent = 0;
    return r;
  }

  /* Checks the timing parameters. */
  void CheckTimingParameters() {
    if (BreakTime < 88 || BreakTime > 1000000) return -1;
    if (MABTime < 8 || MABTime > 1000000) return -1;
    if (MBBTime < 0 || MBBTime > 1000000) return -1;

    timeBreak = BreakTime;
    timeMAB = MABTime;
    timeMBB = MBBTime;
    return 0;
  }

 private:
#if defined(TARGET_LPC1768) || defined(TARGET_LPC2368) || \
    defined(TARGET_LPC4088) || defined(TARGET_LPC11XX)
  LPCserial_TypeDef* uart;
#elif defined(TARGET_LPC11UXX)
  LPC_USART_Type* uart;
#else
  ///#error "CPU not supported."
  Assert(false, "CPU not supported!");
#endif

  Serial dmx_;                  //< The DMX serial port.
  Timeout timeout_;             //< The timeout timer.
  volatile DMXState state_;     //< The current state.
  volatile ISC start_channel_,  //< The start DMX channel.
      channel_count_,           //< The number of DMX channels.
      index_;                   //< The index in the 512 DMX channels.
  ISC is_done_;                 //< Flag for if the Rx or Tx process is done.
  IUA* data_;                   //< Pointer to the data.

  void InitTimer() {  //< Initializes the timer.
    switch (state_) {
      case kStateBegin:  //< Break Time
        timeout.detach();
        rawSerial->LCR |= (1 << 6);
        state_ = kStateMode;
        timeout.attach_us(this, &DMXReceiver::InitTimer, timeBreak);
        break;
      case kStateMode:  //< Mark After Break
        timeout.detach();
        rawSerial->LCR &= ~(1 << 6);
        state_ = kStateMAB;
        timeout.attach_us(this, &DMXReceiver::InitTimer, timeMAB);
        break;
      case kStateMAB:  //< Start code
        timeout.detach();
        Channel_tx = 0;
        state_ = kStateData;
        serial.attach(this, &DMXReceiver::InitSerial, Serial::TxIrq);
#ifdef DMXserial_DIRECT
        while (!(rawSerial->LSR & (1 << 5)))
          ;
        rawSerial->THR = DMX_START_CODE;
#else
        serial.putc(DMX_START_CODE);
#endif
        break;
    }
  }

  void InitSerial() {
    ISC flg, dat;

    flg = rawSerial->LSR;
#ifdef DMXserial_DIRECT
    dat = rawSerial->RBR;
#else
    dat = serial.getc();
#endif

    if (flg & ((1 << 7) | (1 << 3) | (1 << 4))) {
      // Break Time
      if (Channel_rx >= 24 && state_ == kStateData) {
        dataReceived = 1;
      }
      state_ = kStateMode;
      return;
    }

    if (state_ == kStateMode) {
      // Start Code
      if (dat == DMX_START_CODE) {
        Channel_rx = 0;
        state_ = kStateData;
      } else {
        state_ = kStateError;
      }

    } else if (state_ == kStateData) {
      // Data
      data_rx[Channel_rx] = dat;
      Channel_rx++;

      if (Channel_rx >= kNumDMXChannels) {
        dataReceived = 1;
        state_ = kStateBegin;
      }
    }
  }
};
}  // namespace _
#endif
