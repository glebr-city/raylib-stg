//
// Created by n on 15/08/2026.
//

#ifndef RAYLIB_STG_KEYNAMEDICTIONARY_H
#define RAYLIB_STG_KEYNAMEDICTIONARY_H
#include <array>
#include <map>
#include <string>


// Evaluates at compile-time if given a constant, but usable at runtime too!
constexpr std::string_view GetMyKeyName(const KeyboardKey k) {
    switch (k)
    {
    case KEY_NULL: return "none";
    case KEY_APOSTROPHE: return "'";
    case KEY_COMMA: return ",";
    case KEY_MINUS: return "-";
    case KEY_PERIOD: return ".";
    case KEY_SLASH: return "/";
    case KEY_ZERO: return "0";
    case KEY_ONE: return "1";
    case KEY_TWO: return "2";
    case KEY_THREE: return "3";
    case KEY_FOUR: return "4";
    case KEY_FIVE: return "5";
    case KEY_SIX: return "6";
    case KEY_SEVEN: return "7";
    case KEY_EIGHT: return "8";
    case KEY_NINE: return "9";
    case KEY_SEMICOLON: return ";";
    case KEY_EQUAL: return "=";
    case KEY_A: return "a";
    case KEY_B: return "b";
    case KEY_C: return "c";
    case KEY_D: return "d";
    case KEY_E: return "e";
    case KEY_F: return "f";
    case KEY_G: return "g";
    case KEY_H: return "h";
    case KEY_I: return "i";
    case KEY_J: return "j";
    case KEY_K: return "k";
    case KEY_L: return "l";
    case KEY_M: return "m";
    case KEY_N: return "n";
    case KEY_O: return "o";
    case KEY_P: return "p";
    case KEY_Q: return "q";
    case KEY_R: return "r";
    case KEY_S: return "s";
    case KEY_T: return "t";
    case KEY_U: return "u";
    case KEY_V: return "v";
    case KEY_W: return "w";
    case KEY_X: return "x";
    case KEY_Y: return "y";
    case KEY_Z: return "z";
    case KEY_LEFT_BRACKET: return "[";
    case KEY_BACKSLASH: return "\\";
    case KEY_RIGHT_BRACKET: return "]";
    case KEY_GRAVE: return "`";
    case KEY_SPACE: return "space";
    case KEY_ESCAPE: return "esc";
    case KEY_ENTER: return "enter";
    case KEY_TAB: return "tab";
    case KEY_BACKSPACE: return "bckspc";
    case KEY_INSERT: return "ins";
    case KEY_DELETE: return "del";
    case KEY_RIGHT: return "right";
    case KEY_LEFT: return "left";
    case KEY_DOWN: return "down";
    case KEY_UP: return "up";
    case KEY_PAGE_UP: return "pgup";
    case KEY_PAGE_DOWN: return "pgdwn";
    case KEY_HOME: return "home";
    case KEY_END: return "end";
    case KEY_CAPS_LOCK: return "cpslck";
    case KEY_SCROLL_LOCK: return "scrlck";
    case KEY_NUM_LOCK: return "numlck";
    case KEY_PRINT_SCREEN: return "prtsc";
    case KEY_PAUSE: return "pause";
    case KEY_F1: return "f1";
    case KEY_F2: return "f2";
    case KEY_F3: return "f3";
    case KEY_F4: return "f4";
    case KEY_F5: return "f5";
    case KEY_F6: return "f6";
    case KEY_F7: return "f7";
    case KEY_F8: return "f8";
    case KEY_F9: return "f9";
    case KEY_F10: return "f10";
    case KEY_F11: return "f11";
    case KEY_F12: return "f12";
    case KEY_LEFT_SHIFT: return "lshift";
    case KEY_LEFT_CONTROL: return "lctrl";
    case KEY_LEFT_ALT: return "lalt";
    case KEY_LEFT_SUPER: return "lsuper";
    case KEY_RIGHT_SHIFT: return "rshift";
    case KEY_RIGHT_CONTROL: return "rctrl";
    case KEY_RIGHT_ALT: return "ralt";
    case KEY_RIGHT_SUPER: return "rsuper";
    case KEY_KB_MENU: return "kbmenu";
    case KEY_KP_0: return "num0";
    case KEY_KP_1: return "num1";
    case KEY_KP_2: return "num2";
    case KEY_KP_3: return "num3";
    case KEY_KP_4: return "num4";
    case KEY_KP_5: return "num5";
    case KEY_KP_6: return "num6";
    case KEY_KP_7: return "num7";
    case KEY_KP_8: return "num8";
    case KEY_KP_9: return "num9";
    case KEY_KP_DECIMAL: return "num.";
    case KEY_KP_DIVIDE: return "num/";
    case KEY_KP_MULTIPLY: return "num*";
    case KEY_KP_SUBTRACT: return "num-";
    case KEY_KP_ADD: return "num+";
    case KEY_KP_ENTER: return "numentr";
    case KEY_KP_EQUAL: return "num=";
    case KEY_BACK: return "android_back";
    case KEY_MENU: return "android_menu";
    case KEY_VOLUME_UP: return "android_vol_up";
    case KEY_VOLUME_DOWN: return "android_vol_down";
    default: return "???";
    }   
}
/*
    inline constexpr auto MY_KEY_NAMES = std::map<size_t, std::string>{
    {0,"NULL"},
    {39,"APOSTROPHE"},
    {44,"COMMA"},
    {45,"MINUS"},
    {46,"PERIOD"},
    {47,"SLASH"},
    {48,"ZERO"},
    {49,"ONE"},
    {50,"TWO"},
    {51,"THREE"},
    {52,"FOUR"},
    {53,"FIVE"},
    {54,"SIX"},
    {55,"SEVEN"},
    {56,"EIGHT"},
    {57,"NINE"},
    {59,"SEMICOLON"},
    {61,"EQUAL"},
    {65,"A"},
    {66,"B"},
    {67,"C"},
    {68,"D"},
    {69,"E"},
    {70,"F"},
    {71,"G"},
    {72,"H"},
    {73,"I"},
    {74,"J"},
    {75,"K"},
    {76,"L"},
    {77,"M"},
    {78,"N"},
    {79,"O"},
    {80,"P"},
    {81,"Q"},
    {82,"R"},
    {83,"S"},
    {84,"T"},
    {85,"U"},
    {86,"V"},
    {87,"W"},
    {88,"X"},
    {89,"Y"},
    {90,"Z"},
    {91,"LEFT_BRACKET"},
    {92,"BACKSLASH"},
    {93,"RIGHT_BRACKET"},
    {96,"GRAVE"},
    {32,"SPACE"},
    {256,"ESCAPE"},
    {257,"ENTER"},
    {258,"TAB"},
    {259,"BACKSPACE"},
    {260,"INSERT"},
    {261,"DELETE"},
    {262,"RIGHT"},
    {263,"LEFT"},
    {264,"DOWN"},
    {265,"UP"},
    {266,"PAGE_UP"},
    {267,"PAGE_DOWN"},
    {268,"HOME"},
    {269,"END"},
    {280,"CAPS_LOCK"},
    {281,"SCROLL_LOCK"},
    {282,"NUM_LOCK"},
    {283,"PRINT_SCREEN"},
    {284,"PAUSE"},
    {290,"F1"},
    {291,"F2"},
    {292,"F3"},
    {293,"F4"},
    {294,"F5"},
    {295,"F6"},
    {296,"F7"},
    {297,"F8"},
    {298,"F9"},
    {299,"F10"},
    {300,"F11"},
    {301,"F12"},
    {340,"LEFT_SHIFT"},
    {341,"LEFT_CONTROL"},
    {342,"LEFT_ALT"},
    {343,"LEFT_SUPER"},
    {344,"RIGHT_SHIFT"},
    {345,"RIGHT_CONTROL"},
    {346,"RIGHT_ALT"},
    {347,"RIGHT_SUPER"},
    {348,"KB_MENU"},
    {320,"KP_0"},
    {321,"KP_1"},
    {322,"KP_2"},
    {323,"KP_3"},
    {324,"KP_4"},
    {325,"KP_5"},
    {326,"KP_6"},
    {327,"KP_7"},
    {328,"KP_8"},
    {329,"KP_9"},
    {330,"KP_DECIMAL"},
    {331,"KP_DIVIDE"},
    {332,"KP_MULTIPLY"},
    {333,"KP_SUBTRACT"},
    {334,"KP_ADD"},
    {335,"KP_ENTER"},
    {336,"KP_EQUAL"},
    {4,"BACK"},
    {5,"MENU"},
    {24,"VOLUME_UP"},
};
*/
/*
           typedef enum {
               "KEY_NULL            = 0,        // Key: NULL, used for no key pressed
               ""KEY_APOSTROPHE      = 39,       // Key: '
               ""KEY_COMMA           = 44,       // Key: ,
               ""KEY_MINUS           = 45,       // Key: -
               ""KEY_PERIOD          = 46,       // Key: .
               "KEY_SLASH           = 47,       // Key: /
               "KEY_ZERO            = 48,       // Key: 0
               "KEY_ONE             = 49,       // Key: 1
               "KEY_TWO             = 50,       // Key: 2
               "KEY_THREE           = 51,       // Key: 3
               "KEY_FOUR            = 52,       // Key: 4
               "KEY_FIVE            = 53,       // Key: 5
               "KEY_SIX             = 54,       // Key: 6
               "KEY_SEVEN           = 55,       // Key: 7
               "KEY_EIGHT           = 56,       // Key: 8
               "KEY_NINE            = 57,       // Key: 9
               "KEY_SEMICOLON       = 59,       // Key: ;
               "KEY_EQUAL           = 61,       // Key: =
               "KEY_A               = 65,       // Key: A | a
               "KEY_B               = 66,       // Key: B | b
               "KEY_C               = 67,       // Key: C | c
               "KEY_D               = 68,       // Key: D | d
               "KEY_E               = 69,       // Key: E | e
               "KEY_F               = 70,       // Key: F | f
               "KEY_G               = 71,       // Key: G | g
               "KEY_H               = 72,       // Key: H | h
               "KEY_I               = 73,       // Key: I | i
               "KEY_J               = 74,       // Key: J | j
               "KEY_K               = 75,       // Key: K | k
               "KEY_L               = 76,       // Key: L | l
               "KEY_M               = 77,       // Key: M | m
               "KEY_N               = 78,       // Key: N | n
               "KEY_O               = 79,       // Key: O | o
               "KEY_P               = 80,       // Key: P | p
               "KEY_Q               = 81,       // Key: Q | q
               "KEY_R               = 82,       // Key: R | r
               "KEY_S               = 83,       // Key: S | s
               "KEY_T               = 84,       // Key: T | t
               "KEY_U               = 85,       // Key: U | u
               "KEY_V               = 86,       // Key: V | v
               "KEY_W               = 87,       // Key: W | w
               "KEY_X               = 88,       // Key: X | x
               "KEY_Y               = 89,       // Key: Y | y
               "KEY_Z               = 90,       // Key: Z | z
               "KEY_LEFT_BRACKET    = 91,       // Key: [
               "KEY_BACKSLASH       = 92,       // Key: '\'
               "KEY_RIGHT_BRACKET   = 93,       // Key: ]
               "KEY_GRAVE           = 96,       // Key: `
               "KEY_SPACE           = 32,       // Key: Space
               "KEY_ESCAPE          = 256,      // Key: Esc
               "KEY_ENTER           = 257,      // Key: Enter
               "KEY_TAB             = 258,      // Key: Tab
               "KEY_BACKSPACE       = 259,      // Key: Backspace
               "KEY_INSERT          = 260,      // Key: Ins
               "KEY_DELETE          = 261,      // Key: Del
               "KEY_RIGHT           = 262,      // Key: Cursor right
               "KEY_LEFT            = 263,      // Key: Cursor left
               "KEY_DOWN            = 264,      // Key: Cursor down
               "KEY_UP              = 265,      // Key: Cursor up
               "KEY_PAGE_UP         = 266,      // Key: Page up
               "KEY_PAGE_DOWN       = 267,      // Key: Page down
               "KEY_HOME            = 268,      // Key: Home
               "KEY_END             = 269,      // Key: End
               "KEY_CAPS_LOCK       = 280,      // Key: Caps lock
               "KEY_SCROLL_LOCK     = 281,      // Key: Scroll down
               "KEY_NUM_LOCK        = 282,      // Key: Num lock
               "KEY_PRINT_SCREEN    = 283,      // Key: Print screen
               "KEY_PAUSE           = 284,      // Key: Pause
               "KEY_F1              = 290,      // Key: F1
               "KEY_F2              = 291,      // Key: F2
               "KEY_F3              = 292,      // Key: F3
               "KEY_F4              = 293,      // Key: F4
               "KEY_F5              = 294,      // Key: F5
               "KEY_F6              = 295,      // Key: F6
               "KEY_F7              = 296,      // Key: F7
               "KEY_F8              = 297,      // Key: F8
               "KEY_F9              = 298,      // Key: F9
               "KEY_F10             = 299,      // Key: F10
               "KEY_F11             = 300,      // Key: F11
               "KEY_F12             = 301,      // Key: F12
               "KEY_LEFT_SHIFT      = 340,      // Key: Shift left
               "KEY_LEFT_CONTROL    = 341,      // Key: Control left
               "KEY_LEFT_ALT        = 342,      // Key: Alt left
               "KEY_LEFT_SUPER      = 343,      // Key: Super left
               "KEY_RIGHT_SHIFT     = 344,      // Key: Shift right
               "KEY_RIGHT_CONTROL   = 345,      // Key: Control right
               "KEY_RIGHT_ALT       = 346,      // Key: Alt right
               "KEY_RIGHT_SUPER     = 347,      // Key: Super right
               "KEY_KB_MENU         = 348,      // Key: KB menu
               "KEY_KP_0            = 320,      // Key: num 0
               "KEY_KP_1            = 321,      // Key: num 1
               "KEY_KP_2            = 322,      // Key: num 2
               "KEY_KP_3            = 323,      // Key: num 3
               "KEY_KP_4            = 324,      // Key: num 4
               "KEY_KP_5            = 325,      // Key: num 5
               "KEY_KP_6            = 326,      // Key: num 6
               "KEY_KP_7            = 327,      // Key: num 7
               "KEY_KP_8            = 328,      // Key: num 8
               "KEY_KP_9            = 329,      // Key: num 9
               "KEY_KP_DECIMAL      = 330,      // Key: num .
               "KEY_KP_DIVIDE       = 331,      // Key: num /
               "KEY_KP_MULTIPLY     = 332,      // Key: num *
               "KEY_KP_SUBTRACT     = 333,      // Key: num -
               "KEY_KP_ADD          = 334,      // Key: num +
               "KEY_KP_ENTER        = 335,      // Key: num Enter
               "KEY_KP_EQUAL        = 336,      // Key: num =
               "KEY_BACK            = 4,        // Key: Android back button
               "KEY_MENU            = 5,        // Key: Android menu button
               "KEY_VOLUME_UP       = 24,       // Key: Android volume up button
               "KEY_VOLUME_DOWN     = 25        // Key: Android volume down button
           } KeyboardKey;
           */
#endif //RAYLIB_STG_KEYNAMEDICTIONARY_H