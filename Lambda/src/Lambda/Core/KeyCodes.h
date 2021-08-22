#pragma once

namespace Lambda
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define LM_KEY_SPACE           ::Lambda::Key::Space
#define LM_KEY_APOSTROPHE      ::Lambda::Key::Apostrophe    /* ' */
#define LM_KEY_COMMA           ::Lambda::Key::Comma         /* , */
#define LM_KEY_MINUS           ::Lambda::Key::Minus         /* - */
#define LM_KEY_PERIOD          ::Lambda::Key::Period        /* . */
#define LM_KEY_SLASH           ::Lambda::Key::Slash         /* / */
#define LM_KEY_0               ::Lambda::Key::D0
#define LM_KEY_1               ::Lambda::Key::D1
#define LM_KEY_2               ::Lambda::Key::D2
#define LM_KEY_3               ::Lambda::Key::D3
#define LM_KEY_4               ::Lambda::Key::D4
#define LM_KEY_5               ::Lambda::Key::D5
#define LM_KEY_6               ::Lambda::Key::D6
#define LM_KEY_7               ::Lambda::Key::D7
#define LM_KEY_8               ::Lambda::Key::D8
#define LM_KEY_9               ::Lambda::Key::D9
#define LM_KEY_SEMICOLON       ::Lambda::Key::Semicolon     /* ; */
#define LM_KEY_EQUAL           ::Lambda::Key::Equal         /* = */
#define LM_KEY_A               ::Lambda::Key::A
#define LM_KEY_B               ::Lambda::Key::B
#define LM_KEY_C               ::Lambda::Key::C
#define LM_KEY_D               ::Lambda::Key::D
#define LM_KEY_E               ::Lambda::Key::E
#define LM_KEY_F               ::Lambda::Key::F
#define LM_KEY_G               ::Lambda::Key::G
#define LM_KEY_H               ::Lambda::Key::H
#define LM_KEY_I               ::Lambda::Key::I
#define LM_KEY_J               ::Lambda::Key::J
#define LM_KEY_K               ::Lambda::Key::K
#define LM_KEY_L               ::Lambda::Key::L
#define LM_KEY_M               ::Lambda::Key::M
#define LM_KEY_N               ::Lambda::Key::N
#define LM_KEY_O               ::Lambda::Key::O
#define LM_KEY_P               ::Lambda::Key::P
#define LM_KEY_Q               ::Lambda::Key::Q
#define LM_KEY_R               ::Lambda::Key::R
#define LM_KEY_S               ::Lambda::Key::S
#define LM_KEY_T               ::Lambda::Key::T
#define LM_KEY_U               ::Lambda::Key::U
#define LM_KEY_V               ::Lambda::Key::V
#define LM_KEY_W               ::Lambda::Key::W
#define LM_KEY_X               ::Lambda::Key::X
#define LM_KEY_Y               ::Lambda::Key::Y
#define LM_KEY_Z               ::Lambda::Key::Z
#define LM_KEY_LEFT_BRACKET    ::Lambda::Key::LeftBracket   /* [ */
#define LM_KEY_BACKSLASH       ::Lambda::Key::Backslash     /* \ */
#define LM_KEY_RIGHT_BRACKET   ::Lambda::Key::RightBracket  /* ] */
#define LM_KEY_GRAVE_ACCENT    ::Lambda::Key::GraveAccent   /* ` */
#define LM_KEY_WORLD_1         ::Lambda::Key::World1        /* non-US #1 */
#define LM_KEY_WORLD_2         ::Lambda::Key::World2        /* non-US #2 */

/* Function keys */
#define LM_KEY_ESCAPE          ::Lambda::Key::Escape
#define LM_KEY_ENTER           ::Lambda::Key::Enter
#define LM_KEY_TAB             ::Lambda::Key::Tab
#define LM_KEY_BACKSPACE       ::Lambda::Key::Backspace
#define LM_KEY_INSERT          ::Lambda::Key::Insert
#define LM_KEY_DELETE          ::Lambda::Key::Delete
#define LM_KEY_RIGHT           ::Lambda::Key::Right
#define LM_KEY_LEFT            ::Lambda::Key::Left
#define LM_KEY_DOWN            ::Lambda::Key::Down
#define LM_KEY_UP              ::Lambda::Key::Up
#define LM_KEY_PAGE_UP         ::Lambda::Key::PageUp
#define LM_KEY_PAGE_DOWN       ::Lambda::Key::PageDown
#define LM_KEY_HOME            ::Lambda::Key::Home
#define LM_KEY_END             ::Lambda::Key::End
#define LM_KEY_CAPS_LOCK       ::Lambda::Key::CapsLock
#define LM_KEY_SCROLL_LOCK     ::Lambda::Key::ScrollLock
#define LM_KEY_NUM_LOCK        ::Lambda::Key::NumLock
#define LM_KEY_PRINT_SCREEN    ::Lambda::Key::PrintScreen
#define LM_KEY_PAUSE           ::Lambda::Key::Pause
#define LM_KEY_F1              ::Lambda::Key::F1
#define LM_KEY_F2              ::Lambda::Key::F2
#define LM_KEY_F3              ::Lambda::Key::F3
#define LM_KEY_F4              ::Lambda::Key::F4
#define LM_KEY_F5              ::Lambda::Key::F5
#define LM_KEY_F6              ::Lambda::Key::F6
#define LM_KEY_F7              ::Lambda::Key::F7
#define LM_KEY_F8              ::Lambda::Key::F8
#define LM_KEY_F9              ::Lambda::Key::F9
#define LM_KEY_F10             ::Lambda::Key::F10
#define LM_KEY_F11             ::Lambda::Key::F11
#define LM_KEY_F12             ::Lambda::Key::F12
#define LM_KEY_F13             ::Lambda::Key::F13
#define LM_KEY_F14             ::Lambda::Key::F14
#define LM_KEY_F15             ::Lambda::Key::F15
#define LM_KEY_F16             ::Lambda::Key::F16
#define LM_KEY_F17             ::Lambda::Key::F17
#define LM_KEY_F18             ::Lambda::Key::F18
#define LM_KEY_F19             ::Lambda::Key::F19
#define LM_KEY_F20             ::Lambda::Key::F20
#define LM_KEY_F21             ::Lambda::Key::F21
#define LM_KEY_F22             ::Lambda::Key::F22
#define LM_KEY_F23             ::Lambda::Key::F23
#define LM_KEY_F24             ::Lambda::Key::F24
#define LM_KEY_F25             ::Lambda::Key::F25

/* Keypad */
#define LM_KEY_KP_0            ::Lambda::Key::KP0
#define LM_KEY_KP_1            ::Lambda::Key::KP1
#define LM_KEY_KP_2            ::Lambda::Key::KP2
#define LM_KEY_KP_3            ::Lambda::Key::KP3
#define LM_KEY_KP_4            ::Lambda::Key::KP4
#define LM_KEY_KP_5            ::Lambda::Key::KP5
#define LM_KEY_KP_6            ::Lambda::Key::KP6
#define LM_KEY_KP_7            ::Lambda::Key::KP7
#define LM_KEY_KP_8            ::Lambda::Key::KP8
#define LM_KEY_KP_9            ::Lambda::Key::KP9
#define LM_KEY_KP_DECIMAL      ::Lambda::Key::KPDecimal
#define LM_KEY_KP_DIVIDE       ::Lambda::Key::KPDivide
#define LM_KEY_KP_MULTIPLY     ::Lambda::Key::KPMultiply
#define LM_KEY_KP_SUBTRACT     ::Lambda::Key::KPSubtract
#define LM_KEY_KP_ADD          ::Lambda::Key::KPAdd
#define LM_KEY_KP_ENTER        ::Lambda::Key::KPEnter
#define LM_KEY_KP_EQUAL        ::Lambda::Key::KPEqual

#define LM_KEY_LEFT_SHIFT      ::Lambda::Key::LeftShift
#define LM_KEY_LEFT_CONTROL    ::Lambda::Key::LeftControl
#define LM_KEY_LEFT_ALT        ::Lambda::Key::LeftAlt
#define LM_KEY_LEFT_SUPER      ::Lambda::Key::LeftSuper
#define LM_KEY_RIGHT_SHIFT     ::Lambda::Key::RightShift
#define LM_KEY_RIGHT_CONTROL   ::Lambda::Key::RightControl
#define LM_KEY_RIGHT_ALT       ::Lambda::Key::RightAlt
#define LM_KEY_RIGHT_SUPER     ::Lambda::Key::RightSuper
#define LM_KEY_MENU            ::Lambda::Key::Menu