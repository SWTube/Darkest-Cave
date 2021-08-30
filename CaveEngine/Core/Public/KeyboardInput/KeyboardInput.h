/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once
///////////////////////////////////////////////////////////////////////////////////
// Typing Keys (alphanumeric)
// : letters (alpha), numbers, and other symbolic keys

// 0 ~ 9 Numeric Key
#define CAVE_0 0x30
#define CAVE_1 0x31
#define CAVE_2 0x32
#define CAVE_3 0x33
#define CAVE_4 0x34
#define CAVE_5 0x35
#define CAVE_6 0x36
#define CAVE_7 0x37
#define CAVE_8 0x38
#define CAVE_9 0x39

// alpha
#define CAVE_A 0x41
#define CAVE_B 0x42
#define CAVE_C 0x43
#define CAVE_D 0x44
#define CAVE_E 0x45
#define CAVE_F 0x46
#define CAVE_G 0x47
#define CAVE_H 0x48
#define CAVE_I 0x49
#define CAVE_J 0x4A
#define CAVE_K 0x4B
#define CAVE_L 0x4C
#define CAVE_M 0x4D
#define CAVE_N 0x4E
#define CAVE_O 0x4F
#define CAVE_P 0x50
#define CAVE_Q 0x51
#define CAVE_R 0x52
#define CAVE_S 0x53
#define CAVE_T 0x54
#define CAVE_U 0x55
#define CAVE_V 0x56
#define CAVE_W 0x57
#define CAVE_X 0x58
#define CAVE_Y 0x59
#define CAVE_Z 0x5A

// Others
#define CAVE_BACKSPACE 0x08
#define CAVE_TAB 0x09
#define CAVE_ENTER 0x0D
#define CAVE_CAPSLOCK 0x14
#define CAVE_SPACE 0x20 // Space Bar
#define CAVE_LSHIFT 0xA0 // Left Shift
#define CAVE_RSHIFT 0xA1 // Right Shift
#define CAVE_COLON 0xBA // ":" or ";"
#define CAVE_PLUS 0xBB // "+" or "=" (Not on NumPad)
#define CAVE_LBRACKET 0xBC // "<" or ","
#define CAVE_UNDERLINE 0xBD // "_" or "-" (Not on NumPad)
#define CAVE_RBRACKET 0xBE // ">" or "."
#define CAVE_QUESTION 0xBF // "?" or "/"
#define CAVE_TILDE 0xC0 // "~" or "`"
#define CAVE_LBRACE 0xDB // "{" or "["
#define CAVE_PIPE 0xDC // "|" or "\"
#define CAVE_RBRACE 0xDD // "}" or "]"
#define CAVE_QUOTE 0xDE // ' " ' or " ' "

///////////////////////////////////////////////////////////////////////////////////
// Control Keys
// : Ctrl, Alt, Win, ESC, others

#define CAVE_CONTROL 0x11
#define CAVE_ALT 0x12
#define CAVE_PAUSE 0x13
#define CAVE_ESC 0x1B
#define CAVE_PRINTSCREEN 0x2C
#define CAVE_LWIN 0x5B
#define CAVE_RWIN 0x5C
#define CAVE_SCROLL 0x91 // Scroll Lock

///////////////////////////////////////////////////////////////////////////////////
// Function Keys
// : F1 ~ F12

#define CAVE_F1 0x70
#define CAVE_F2 0x71
#define CAVE_F3 0x72
#define CAVE_F4 0x73
#define CAVE_F5 0x74
#define CAVE_F6 0x75
#define CAVE_F7 0x76
#define CAVE_F8 0x77
#define CAVE_F9 0x78
#define CAVE_F10 0x79
#define CAVE_F11 0x7A
#define CAVE_F12 0x7B

///////////////////////////////////////////////////////////////////////////////////
// Navigation Keys
// : Arrow Keys, Home, End, Insert, Delete, Page Up, Page Down

// Arrow keys
#define CAVE_LEFT 0x25
#define CAVE_UP 0x26
#define CAVE_RIGHT 0x27
#define CAVE_DOWN 0x28

#define CAVE_PAGEUP 0x21
#define CAVE_PAGEDOWN 0x22
#define CAVE_END 0x23
#define CAVE_HOME 0x24
#define CAVE_INSERT 0x2D
#define CAVE_DELETE 0x2E

///////////////////////////////////////////////////////////////////////////////////
// Numeric Keypad
// : numeric key and operators, others on Numpad

// 0 ~ 9 Numeric Key (with NumPad)
#define CAVE_NUMPAD0 0x60
#define CAVE_NUMPAD1 0x61
#define CAVE_NUMPAD2 0x62
#define CAVE_NUMPAD3 0x63
#define CAVE_NUMPAD4 0x64
#define CAVE_NUMPAD5 0x65
#define CAVE_NUMPAD6 0x66
#define CAVE_NUMPAD7 0x67
#define CAVE_NUMPAD8 0x68
#define CAVE_NUMPAD9 0x69

// Operators (/, *, -, +)
#define CAVE_MULTIPLY 0x6A // "*"
#define CAVE_ADD 0x6B // "+"
#define CAVE_SUBTRACT 0x6D // "-"
#define CAVE_DIVIDE 0x6F // "/"

// Others
#define CAVE_NUMLOCK 0x90
#define CAVE_DECIMAL 0x6E // "." (DELETE with Shift key)