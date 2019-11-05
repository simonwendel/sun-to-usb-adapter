/*
 * Sun to USB keyboard adapter
 * Copyright (C) 2019  Simon Wendel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScanCodeTranslationMap.h"

#include <HID-Project.h>
#include <stdint.h>

namespace adapter
{
    bool ScanCodeTranslationMap::contains(int sunMakeCode) const
    {
        if (sunMakeCode < 0 || sunMakeCode > CONTAINER_SIZE - 1)
        {
            return false;
        }

        return translations[sunMakeCode] != 0;
    }

    uint8_t ScanCodeTranslationMap::getUsageId(int sunMakeCode) const
    {
        return translations[sunMakeCode];
    }

    ScanCodeTranslationMap::ScanCodeTranslationMap()
    {
        translations[0x01] = HID_KEYBOARD_STOP;
        translations[0x02] = HID_KEYBOARD_VOLUME_DOWN;
        translations[0x03] = HID_KEYBOARD_AGAIN;
        translations[0x04] = HID_KEYBOARD_VOLUME_UP;
        translations[0x05] = HID_KEYBOARD_F1;
        translations[0x06] = HID_KEYBOARD_F2;
        translations[0x07] = HID_KEYBOARD_F10;
        translations[0x08] = HID_KEYBOARD_F3;
        translations[0x09] = HID_KEYBOARD_F11;
        translations[0x0A] = HID_KEYBOARD_F4;
        translations[0x0B] = HID_KEYBOARD_F12;
        translations[0x0C] = HID_KEYBOARD_F5;
        translations[0x0D] = HID_KEYBOARD_RIGHT_ALT;
        translations[0x0E] = HID_KEYBOARD_F6;
        translations[0x10] = HID_KEYBOARD_F7;
        translations[0x11] = HID_KEYBOARD_F8;
        translations[0x12] = HID_KEYBOARD_F9;
        translations[0x13] = HID_KEYBOARD_LEFT_ALT;
        translations[0x14] = HID_KEYBOARD_UPARROW;
        translations[0x15] = HID_KEYBOARD_PAUSE;
        translations[0x16] = HID_KEYBOARD_PRINTSCREEN;
        translations[0x17] = HID_KEYBOARD_SCROLL_LOCK;
        translations[0x18] = HID_KEYBOARD_LEFTARROW;
        translations[0x19] = HID_KEYBOARD_MENU;
        translations[0x1A] = HID_KEYBOARD_UNDO;
        translations[0x1B] = HID_KEYBOARD_DOWNARROW;
        translations[0x1C] = HID_KEYBOARD_RIGHTARROW;
        translations[0x1D] = HID_KEYBOARD_ESCAPE;
        translations[0x1E] = HID_KEYBOARD_1_AND_EXCLAMATION_POINT;
        translations[0x1F] = HID_KEYBOARD_2_AND_AT;
        translations[0x20] = HID_KEYBOARD_3_AND_POUND;
        translations[0x21] = HID_KEYBOARD_4_AND_DOLLAR;
        translations[0x22] = HID_KEYBOARD_5_AND_PERCENT;
        translations[0x23] = HID_KEYBOARD_6_AND_CARAT;
        translations[0x24] = HID_KEYBOARD_7_AND_AMPERSAND;
        translations[0x25] = HID_KEYBOARD_8_AND_ASTERISK;
        translations[0x26] = HID_KEYBOARD_9_AND_LEFT_PAREN;
        translations[0x27] = HID_KEYBOARD_0_AND_RIGHT_PAREN;
        translations[0x28] = HID_KEYBOARD_MINUS_AND_UNDERSCORE;
        translations[0x29] = HID_KEYBOARD_EQUALS_AND_PLUS;
        translations[0x2A] = HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE;
        translations[0x2B] = HID_KEYBOARD_DELETE;
        translations[0x2C] = HID_KEYBOARD_INSERT;
        translations[0x2D] = HID_KEYBOARD_MUTE;
        translations[0x2E] = HID_KEYPAD_DIVIDE;
        translations[0x2F] = HID_KEYPAD_MULTIPLY;
        translations[0x30] = HID_KEYBOARD_POWER;
        translations[0x31] = HID_KEYBOARD_SELECT;
        translations[0x32] = HID_KEYPAD_PERIOD_AND_DELETE;
        translations[0x33] = HID_KEYBOARD_COPY;
        translations[0x34] = HID_KEYBOARD_HOME;
        translations[0x35] = HID_KEYBOARD_TAB;
        translations[0x36] = HID_KEYBOARD_Q_AND_Q;
        translations[0x37] = HID_KEYBOARD_W_AND_W;
        translations[0x38] = HID_KEYBOARD_E_AND_E;
        translations[0x39] = HID_KEYBOARD_R_AND_R;
        translations[0x3A] = HID_KEYBOARD_T_AND_T;
        translations[0x3B] = HID_KEYBOARD_Y_AND_Y;
        translations[0x3C] = HID_KEYBOARD_U_AND_U;
        translations[0x3D] = HID_KEYBOARD_I_AND_I;
        translations[0x3E] = HID_KEYBOARD_O_AND_O;
        translations[0x3F] = HID_KEYBOARD_P_AND_P;
        translations[0x40] = HID_KEYBOARD_LEFT_BRACKET_AND_LEFT_CURLY_BRACE;
        translations[0x41] = HID_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_CURLY_BRACE;
        translations[0x42] = HID_KEYBOARD_DELETE_FORWARD;
        translations[0x43] = HID_KEYBOARD_APPLICATION;
        translations[0x44] = HID_KEYPAD_7_AND_HOME;
        translations[0x45] = HID_KEYPAD_8_AND_UP_ARROW;
        translations[0x46] = HID_KEYPAD_9_AND_PAGE_UP;
        translations[0x47] = HID_KEYPAD_SUBTRACT;
        translations[0x48] = HID_KEYBOARD_EXECUTE;
        translations[0x49] = HID_KEYBOARD_PASTE;
        translations[0x4A] = HID_KEYBOARD_END;
        translations[0x4C] = HID_KEYBOARD_LEFT_CONTROL;
        translations[0x4D] = HID_KEYBOARD_A_AND_A;
        translations[0x4E] = HID_KEYBOARD_S_AND_S;
        translations[0x4F] = HID_KEYBOARD_D_AND_D;
        translations[0x50] = HID_KEYBOARD_F_AND_F;
        translations[0x51] = HID_KEYBOARD_G_AND_G;
        translations[0x52] = HID_KEYBOARD_H_AND_H;
        translations[0x53] = HID_KEYBOARD_J_AND_J;
        translations[0x54] = HID_KEYBOARD_K_AND_K;
        translations[0x55] = HID_KEYBOARD_L_AND_L;
        translations[0x56] = HID_KEYBOARD_SEMICOLON_AND_COLON;
        translations[0x57] = HID_KEYBOARD_QUOTE_AND_DOUBLEQUOTE;
        translations[0x58] = HID_KEYBOARD_BACKSLASH_AND_PIPE;
        translations[0x59] = HID_KEYBOARD_ENTER;
        translations[0x5A] = HID_KEYPAD_ENTER;
        translations[0x5B] = HID_KEYPAD_4_AND_LEFT_ARROW;
        translations[0x5C] = HID_KEYPAD_5;
        translations[0x5D] = HID_KEYPAD_6_AND_RIGHT_ARROW;
        translations[0x5E] = HID_KEYPAD_0_AND_INSERT;
        translations[0x5F] = HID_KEYBOARD_FIND;
        translations[0x60] = HID_KEYBOARD_PAGE_UP;
        translations[0x61] = HID_KEYBOARD_CUT;
        translations[0x62] = HID_KEYPAD_NUM_LOCK_AND_CLEAR;
        translations[0x63] = HID_KEYBOARD_LEFT_SHIFT;
        translations[0x64] = HID_KEYBOARD_Z_AND_Z;
        translations[0x65] = HID_KEYBOARD_X_AND_X;
        translations[0x66] = HID_KEYBOARD_C_AND_C;
        translations[0x67] = HID_KEYBOARD_V_AND_V;
        translations[0x68] = HID_KEYBOARD_B_AND_B;
        translations[0x69] = HID_KEYBOARD_N_AND_N;
        translations[0x6A] = HID_KEYBOARD_M_AND_M;
        translations[0x6B] = HID_KEYBOARD_COMMA_AND_LESS_THAN;
        translations[0x6C] = HID_KEYBOARD_PERIOD_AND_GREATER_THAN;
        translations[0x6D] = HID_KEYBOARD_SLASH_AND_QUESTION_MARK;
        translations[0x6E] = HID_KEYBOARD_RIGHT_SHIFT;
        translations[0x70] = HID_KEYPAD_1_AND_END;
        translations[0x71] = HID_KEYPAD_2_AND_DOWN_ARROW;
        translations[0x72] = HID_KEYPAD_3_AND_PAGE_DOWN;
        translations[0x76] = HID_KEYBOARD_HELP;
        translations[0x77] = HID_KEYBOARD_CAPS_LOCK;
        translations[0x78] = HID_KEYBOARD_LEFT_GUI;
        translations[0x79] = HID_KEYBOARD_SPACEBAR;
        translations[0x7A] = HID_KEYBOARD_RIGHT_GUI;
        translations[0x7B] = HID_KEYBOARD_PAGE_DOWN;
        translations[0x7C] = HID_KEYBOARD_NON_US_BACKSLASH_AND_PIPE;
        translations[0x7D] = HID_KEYPAD_ADD;
    }
} // namespace adapter
