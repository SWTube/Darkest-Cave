/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <windows.h>
#include <winuser.h>

#include "CoreTypes.h"

#include "Debug/Log.h"

export module cave.Core.KeyboardInput;

import cave.Core.String;

namespace cave
{
	export class vKeyCode final
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////
		// Typing Keys (alphanumeric)
		// : letters (alpha), numbers, and other symbolic keys

		static const int32_t CAVE_0 = 0x30;
		static const int32_t CAVE_1 = 0x31;
		static const int32_t CAVE_2 = 0x32;
		static const int32_t CAVE_3 = 0x33;
		static const int32_t CAVE_4 = 0x34;
		static const int32_t CAVE_5 = 0x35;
		static const int32_t CAVE_6 = 0x36;
		static const int32_t CAVE_7 = 0x37;
		static const int32_t CAVE_8 = 0x38;
		static const int32_t CAVE_9 = 0x39;

		static const int32_t CAVE_A = 0x41;
		static const int32_t CAVE_B = 0x42;
		static const int32_t CAVE_C = 0x43;
		static const int32_t CAVE_D = 0x44;
		static const int32_t CAVE_E = 0x45;
		static const int32_t CAVE_F = 0x46;
		static const int32_t CAVE_G = 0x47;
		static const int32_t CAVE_H = 0x48;
		static const int32_t CAVE_I = 0x49;
		static const int32_t CAVE_J = 0x4A;
		static const int32_t CAVE_K = 0x4B;
		static const int32_t CAVE_L = 0x4C;
		static const int32_t CAVE_M = 0x4D;
		static const int32_t CAVE_N = 0x4E;
		static const int32_t CAVE_O = 0x4F;
		static const int32_t CAVE_P = 0x50;
		static const int32_t CAVE_Q = 0x51;
		static const int32_t CAVE_R = 0x52;
		static const int32_t CAVE_S = 0x53;
		static const int32_t CAVE_T = 0x54;
		static const int32_t CAVE_U = 0x55;
		static const int32_t CAVE_V = 0x56;
		static const int32_t CAVE_W = 0x57;
		static const int32_t CAVE_X = 0x58;
		static const int32_t CAVE_Y = 0x59;
		static const int32_t CAVE_Z = 0x5A;

		static const int32_t CAVE_BACKSPACE = 0x08;
		static const int32_t CAVE_TAB = 0x09;
		static const int32_t CAVE_ENTER = 0x0D;
		static const int32_t CAVE_CAPSLOCK = 0x14;
		static const int32_t CAVE_SPACE = 0x20;
		static const int32_t CAVE_LSHIFT = 0xA0;
		static const int32_t CAVE_RSHIFT = 0xA1;
		static const int32_t CAVE_COLON = 0xBA;
		static const int32_t CAVE_PLUS = 0xBB;
		static const int32_t CAVE_LBRACKET = 0xBC;
		static const int32_t CAVE_UNDERLINE = 0xBD;
		static const int32_t CAVE_RBRACKET = 0xBE;
		static const int32_t CAVE_QUESTION = 0xBF;
		static const int32_t CAVE_TILDE = 0xC0;
		static const int32_t CAVE_LBRACE = 0xDB;
		static const int32_t CAVE_PIPE = 0xDC;
		static const int32_t CAVE_RBRACE = 0xDD;
		static const int32_t CAVE_QUOTE = 0xDE;

		///////////////////////////////////////////////////////////////////////////////////
		// Control Keys
		// : Ctrl, Alt, Win, ESC, others

		static const int32_t CAVE_CONTROL = 0x11;
		static const int32_t CAVE_ALT = 0x12;
		static const int32_t CAVE_PAUSE = 0x13;
		static const int32_t CAVE_ESC = 0x1B;
		static const int32_t CAVE_PRINTSCREEN = 0x2C;
		static const int32_t CAVE_LWIN = 0x5B;
		static const int32_t CAVE_RWIN = 0x5C;
		static const int32_t CAVE_SCROLL = 0x91;

		static const int32_t CAVE_F1 = 0x70;
		static const int32_t CAVE_F2 = 0x71;
		static const int32_t CAVE_F3 = 0x72;
		static const int32_t CAVE_F4 = 0x73;
		static const int32_t CAVE_F5 = 0x74;
		static const int32_t CAVE_F6 = 0x75;
		static const int32_t CAVE_F7 = 0x76;
		static const int32_t CAVE_F8 = 0x77;
		static const int32_t CAVE_F9 = 0x78;
		static const int32_t CAVE_F10 = 0x79;
		static const int32_t CAVE_F11 = 0x7A;
		static const int32_t CAVE_F12 = 0x7B;

		///////////////////////////////////////////////////////////////////////////////////
		// Navigation Keys
		// : Arrow Keys, Home, End, Insert, Delete, Page Up, Page Down

		static const int32_t CAVE_LEFT = 0x25;
		static const int32_t CAVE_UP = 0x26;
		static const int32_t CAVE_RIGHT = 0x27;
		static const int32_t CAVE_DOWN = 0x28;

		static const int32_t CAVE_PAGEUP = 0x21;
		static const int32_t CAVE_PAGEDOWN = 0x22;
		static const int32_t CAVE_END = 0x23;
		static const int32_t CAVE_HOME = 0x24;
		static const int32_t CAVE_INSERT = 0x2D;
		static const int32_t CAVE_DELETE = 0x2E;

		///////////////////////////////////////////////////////////////////////////////////
		// Numeric Keypad
		// : numeric key and operators, others on Numpad

		static const int32_t CAVE_NUMPAD0 = 0x60;
		static const int32_t CAVE_NUMPAD1 = 0x61;
		static const int32_t CAVE_NUMPAD2 = 0x62;
		static const int32_t CAVE_NUMPAD3 = 0x63;
		static const int32_t CAVE_NUMPAD4 = 0x64;
		static const int32_t CAVE_NUMPAD5 = 0x65;
		static const int32_t CAVE_NUMPAD6 = 0x66;
		static const int32_t CAVE_NUMPAD7 = 0x67;
		static const int32_t CAVE_NUMPAD8 = 0x68;
		static const int32_t CAVE_NUMPAD9 = 0x69;

		static const int32_t CAVE_MULTIPLY = 0x6A;
		static const int32_t CAVE_ADD = 0x6B;
		static const int32_t CAVE_SUBTRACT = 0x6D;
		static const int32_t CAVE_DIVIDE = 0x6F;

		static const int32_t CAVE_NUMLOCK = 0x90;
		static const int32_t CAVE_DECIMAL = 0x6E;
	};

	export class Input
	{
	public:
		static bool GetKey(int32_t vKey);
	};

	bool Input::GetKey(int32_t vKey)
	{
		return GetAsyncKeyState(vKey);
	}

	export namespace KeyboardInputTest
	{
		void Main()
		{
			LOGDF(cave::eLogChannel::CORE, "%d", Input::GetKey(vKeyCode::CAVE_CONTROL));
		}
	}
}