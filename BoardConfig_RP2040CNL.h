/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2024 OpenStickCommunity (gp2040-ce.info)
 */

#ifndef PICO_BOARD_CONFIG_H_
#define PICO_BOARD_CONFIG_H_

#include "enums.pb.h"
#include "class/hid/hid.h"

#define BOARD_CONFIG_LABEL "MyRP2040"

// Main pin mapping Configuration
//                                                  // GP2040 | Xinput | Switch  | PS3/4/5  | Dinput |
#define GPIO_PIN_00 GpioAction::BUTTON_PRESS_UP
#define GPIO_PIN_01 GpioAction::BUTTON_PRESS_DOWN
#define GPIO_PIN_02 GpioAction::BUTTON_PRESS_LEFT
#define GPIO_PIN_03 GpioAction::BUTTON_PRESS_RIGHT

#define GPIO_PIN_04 GpioAction::BUTTON_PRESS_B1
#define GPIO_PIN_05 GpioAction::BUTTON_PRESS_B2
#define GPIO_PIN_06 GpioAction::BUTTON_PRESS_B3
#define GPIO_PIN_09 GpioAction::BUTTON_PRESS_B4

#define GPIO_PIN_15 GpioAction::BUTTON_PRESS_R1
#define GPIO_PIN_16 GpioAction::BUTTON_PRESS_L1
#define GPIO_PIN_13 GpioAction::BUTTON_PRESS_R2
#define GPIO_PIN_14 GpioAction::BUTTON_PRESS_L2

#define GPIO_PIN_08 GpioAction::BUTTON_PRESS_S1
#define GPIO_PIN_10 GpioAction::BUTTON_PRESS_S2

#define GPIO_PIN_11 GpioAction::BUTTON_PRESS_L3
#define GPIO_PIN_12 GpioAction::BUTTON_PRESS_R3

#define GPIO_PIN_17 GpioAction::BUTTON_PRESS_A1
#define GPIO_PIN_18 GpioAction::BUTTON_PRESS_A2
#define GPIO_PIN_21 GpioAction::BUTTON_PRESS_A3
#define GPIO_PIN_22 GpioAction::BUTTON_PRESS_A4

// Duplicados según tu configuración actual
#define GPIO_PIN_07 GpioAction::BUTTON_PRESS_A1
#define GPIO_PIN_19 GpioAction::BUTTON_PRESS_S1
#define GPIO_PIN_20 GpioAction::BUTTON_PRESS_S2

// Reservados para add-ons
#define GPIO_PIN_23 GpioAction::ASSIGNED_TO_ADDON   // WS2812
#define GPIO_PIN_25 GpioAction::ASSIGNED_TO_ADDON   // LED onboard

#define GPIO_PIN_24 GpioAction::ASSIGNED_TO_ADDON
#define GPIO_PIN_26 GpioAction::ASSIGNED_TO_ADDON   // Analog X
#define GPIO_PIN_27 GpioAction::ASSIGNED_TO_ADDON   // Analog Y
#define GPIO_PIN_28 GpioAction::ASSIGNED_TO_ADDON
#define GPIO_PIN_29 GpioAction::ASSIGNED_TO_ADDON

// Keyboard Mapping Configuration
#define KEY_DPAD_UP     HID_KEY_ARROW_UP
#define KEY_DPAD_DOWN   HID_KEY_ARROW_DOWN
#define KEY_DPAD_LEFT   HID_KEY_ARROW_LEFT
#define KEY_DPAD_RIGHT  HID_KEY_ARROW_RIGHT

#define KEY_BUTTON_B1   HID_KEY_SHIFT_LEFT
#define KEY_BUTTON_B2   HID_KEY_Z
#define KEY_BUTTON_B3   HID_KEY_CONTROL_LEFT
#define KEY_BUTTON_B4   HID_KEY_ALT_LEFT

#define KEY_BUTTON_L1   HID_KEY_C
#define KEY_BUTTON_R1   HID_KEY_SPACE
#define KEY_BUTTON_L2   HID_KEY_V
#define KEY_BUTTON_R2   HID_KEY_X

#define KEY_BUTTON_S1   HID_KEY_5
#define KEY_BUTTON_S2   HID_KEY_1

#define KEY_BUTTON_L3   HID_KEY_EQUAL
#define KEY_BUTTON_R3   HID_KEY_MINUS

#define KEY_BUTTON_A1   HID_KEY_9
#define KEY_BUTTON_A2   HID_KEY_F2
#define KEY_BUTTON_A3   HID_KEY_F3
#define KEY_BUTTON_A4   HID_KEY_F4

#define KEY_BUTTON_FN   -1

// WS2812 integrado
#define BOARD_LEDS_PIN 23
#define LED_BRIGHTNESS_MAXIMUM 100
#define LED_BRIGHTNESS_STEPS 5
#define LED_FORMAT LED_FORMAT_GRB
#define LEDS_PER_PIXEL 1

#endif