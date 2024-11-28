#pragma once
#include <SDL.h>
#include "MathHelper.h"
#include <string>
#include <iostream>
#include <array>

namespace SDLFramework {

	class InputManager {
	public:
		const std::array<SDL_Scancode, 14> keysToCheck = {
		SDL_SCANCODE_W,
		SDL_SCANCODE_S,
		SDL_SCANCODE_A,
		SDL_SCANCODE_D,
		SDL_SCANCODE_I,
		SDL_SCANCODE_J,
		SDL_SCANCODE_K,
		SDL_SCANCODE_L,
		SDL_SCANCODE_Q,
		SDL_SCANCODE_E,
		SDL_SCANCODE_Z,
		SDL_SCANCODE_C,
		SDL_SCANCODE_ESCAPE,
		SDL_SCANCODE_SPACE
		};

		static InputManager* Instance();
		static void Release();

		void HandleInput();

		bool KeyDown(SDL_Scancode scancode);
		bool KeyPressed(SDL_Scancode scancode);
		bool KeyReleased(SDL_Scancode scancode);

		enum MouseButton { LEFT = 0, RIGHT, MIDDLE, BACK, FORWARD };

		bool MouseButtonDown(MouseButton button);
		bool MouseButtonPressed(MouseButton button);
		bool MouseButtonReleased(MouseButton button);

		Vector2 MousePosition();

		void Update();
		void UpdatePrevInput();

	private:
		InputManager();
		~InputManager();

		static InputManager* sInstance;
		const Uint8* mKeyboardState;
		Uint8* mPrevKeyboardState;
		int mKeyLength;

		Uint32 mPrevMouseState;	
		Uint32 mMouseState;

		int mMouseXPos;
		int mMouseYPos;
	};

}