#ifndef QUANTVERSO_KEYBOARD_H
#define QUANTVERSO_KEYBOARD_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>
#include <bitset>

//--------------------------------------------------------------------------------------------------

class Keyboard
{
public:
	enum Key
	{
		Unknown		 = SDL_SCANCODE_UNKNOWN,
		A			 = SDL_SCANCODE_A,
		B			 = SDL_SCANCODE_B,
		C			 = SDL_SCANCODE_C,
		D			 = SDL_SCANCODE_D,
		E			 = SDL_SCANCODE_E,
		F			 = SDL_SCANCODE_F,
		G			 = SDL_SCANCODE_G,
		H			 = SDL_SCANCODE_H,
		I			 = SDL_SCANCODE_I,
		J			 = SDL_SCANCODE_J,
		K			 = SDL_SCANCODE_K,
		L			 = SDL_SCANCODE_L,
		M			 = SDL_SCANCODE_M,
		N			 = SDL_SCANCODE_N,
		O			 = SDL_SCANCODE_O,
		P			 = SDL_SCANCODE_P,
		Q			 = SDL_SCANCODE_Q,
		R			 = SDL_SCANCODE_R,
		S			 = SDL_SCANCODE_S,
		T			 = SDL_SCANCODE_T,
		U			 = SDL_SCANCODE_U,
		V			 = SDL_SCANCODE_V,
		W			 = SDL_SCANCODE_W,
		X			 = SDL_SCANCODE_X,
		Y			 = SDL_SCANCODE_Y,
		Z			 = SDL_SCANCODE_Z,
		Num1		 = SDL_SCANCODE_1,
		Num2		 = SDL_SCANCODE_2,
		Num3		 = SDL_SCANCODE_3,
		Num4		 = SDL_SCANCODE_4,
		Num5		 = SDL_SCANCODE_5,
		Num6		 = SDL_SCANCODE_6,
		Num7		 = SDL_SCANCODE_7,
		Num8		 = SDL_SCANCODE_8,
		Num9		 = SDL_SCANCODE_9,
		Num0		 = SDL_SCANCODE_0,
		Return		 = SDL_SCANCODE_RETURN,
		Escape		 = SDL_SCANCODE_ESCAPE,
		Backspace	 = SDL_SCANCODE_BACKSPACE,
		Tab			 = SDL_SCANCODE_TAB,
		Space		 = SDL_SCANCODE_SPACE,
		Minus		 = SDL_SCANCODE_MINUS,
		Equals		 = SDL_SCANCODE_EQUALS,
		LeftBracket  = SDL_SCANCODE_LEFTBRACKET,
		RightBracket = SDL_SCANCODE_RIGHTBRACKET,
		Backslash	 = SDL_SCANCODE_BACKSLASH,
		NonUSHash	 = SDL_SCANCODE_NONUSHASH,
		Semicolon	 = SDL_SCANCODE_SEMICOLON,
		Apostrophe	 = SDL_SCANCODE_APOSTROPHE,
		Grave		 = SDL_SCANCODE_GRAVE,
		Comma		 = SDL_SCANCODE_COMMA,
		Period		 = SDL_SCANCODE_PERIOD,
		Slash		 = SDL_SCANCODE_SLASH,
		CapsLock	 = SDL_SCANCODE_CAPSLOCK,
		F1			 = SDL_SCANCODE_F1,
		F2			 = SDL_SCANCODE_F2,
		F3			 = SDL_SCANCODE_F3,
		F4			 = SDL_SCANCODE_F4,
		F5			 = SDL_SCANCODE_F5,
		F6			 = SDL_SCANCODE_F6,
		F7			 = SDL_SCANCODE_F7,
		F8			 = SDL_SCANCODE_F8,
		F9			 = SDL_SCANCODE_F9,
		F10			 = SDL_SCANCODE_F10,
		F11			 = SDL_SCANCODE_F11,
		F12			 = SDL_SCANCODE_F12,
		PrintScreen  = SDL_SCANCODE_PRINTSCREEN,
		ScrollLock   = SDL_SCANCODE_SCROLLLOCK,
		Pause		 = SDL_SCANCODE_PAUSE,
		Insert		 = SDL_SCANCODE_INSERT,
		Home		 = SDL_SCANCODE_HOME,
		PageUp		 = SDL_SCANCODE_PAGEUP,
		Delete		 = SDL_SCANCODE_DELETE,
		End			 = SDL_SCANCODE_END,
		PageDown	 = SDL_SCANCODE_PAGEDOWN,
		Right		 = SDL_SCANCODE_RIGHT,
		Left		 = SDL_SCANCODE_LEFT,
		Down		 = SDL_SCANCODE_DOWN,
		Up			 = SDL_SCANCODE_UP,
		LControl	 = SDL_SCANCODE_LCTRL,
		LShift		 = SDL_SCANCODE_LSHIFT,
		LAlt		 = SDL_SCANCODE_LALT,
		LGUI		 = SDL_SCANCODE_LGUI,
		RControl	 = SDL_SCANCODE_RCTRL,
		RShift		 = SDL_SCANCODE_RSHIFT,
		RAlt		 = SDL_SCANCODE_RALT,
		RGUI		 = SDL_SCANCODE_RGUI
	};

	static bool KeyPressed(Key key);
	static bool KeyDown(Key key);

private:
	inline static std::bitset<RGUI + 1> wasPressed;
};

//--------------------------------------------------------------------------------------------------

inline bool Keyboard::KeyPressed(Key key)
{
	return SDL_GetKeyboardState(NULL)[key] ? true : wasPressed[key] = false;
}

//--------------------------------------------------------------------------------------------------

inline bool Keyboard::KeyDown(Key key)
{
	if (KeyPressed(key) && !wasPressed[key])
		return wasPressed[key] = true;

	return false;
}

//--------------------------------------------------------------------------------------------------

#endif
