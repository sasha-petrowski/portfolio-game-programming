#include "Input.h"

namespace SpidersEngine
{
	int Input::mouseX;
	int Input::mouseY;
	int Input::relativeX;
	int Input::relativeY;

	bool Input::keyPressed[KEYBOARD_SIZE];
	bool Input::keyDown[KEYBOARD_SIZE];

	bool Input::mousePressed[MOUSE_SIZE];  // 322 is the number of SDLK_DOWN events
	bool Input::mouseDown[MOUSE_SIZE];  // 322 is the number of SDLK_DOWN events

	std::queue<int> mCleanKeyboard;
	std::queue<int> mCleanMouse;

	void Input::initInputs()
	{
		mCleanKeyboard = *new std::queue<int>();
		mCleanMouse = *new std::queue<int>();

		for (int i = 0; i < KEYBOARD_SIZE; i++) { // init all keys to false
			keyPressed[i] = false;
			keyDown[i] = false;
		}

		for (int i = 0; i < MOUSE_SIZE; i++) { // init them all mouse to false
			mousePressed[i] = false;
			mouseDown[i] = false;
		}
	}

	bool Input::handleEvents()
	{
#pragma region Clean keys pressed last frame
		while (!mCleanKeyboard.empty()) // Clean keys pressed last frame
		{
			int key = mCleanKeyboard.front();
			mCleanKeyboard.pop();
			keyPressed[key] = false;
		}
		while (!mCleanMouse.empty()) // Clean keys pressed last frame
		{
			int button = mCleanMouse.front();
			mCleanMouse.pop();
			mousePressed[button] = false;
		}
#pragma endregion

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				return false;

			case SDL_KEYDOWN:
				#pragma region Key down
				if (e.key.keysym.sym >= KEYBOARD_SIZE)
				{
					std::cout << "Key pressed outside range : " << (char)(e.key.keysym.sym) << '\n';
					break;
				}

				if (!keyDown[e.key.keysym.sym])
				{
					std::cout << "Key pressed : " << (char)(e.key.keysym.sym) << '\n';

					keyPressed[e.key.keysym.sym] = true;
					mCleanKeyboard.push(e.key.keysym.sym);
				}
				keyDown[e.key.keysym.sym] = true;
				#pragma endregion
				break;

			case SDL_KEYUP:
				#pragma region Key up
				if (e.key.keysym.sym >= KEYBOARD_SIZE) break;
				keyDown[e.key.keysym.sym] = false;
				#pragma endregion
				break;

			case SDL_MOUSEBUTTONDOWN:
				#pragma region Mouse down
				if (e.button.button >= MOUSE_SIZE)
				{
					std::cout << "Mouse pressed outside range : " << (int)(e.button.button) << '\n';
					break;
				}

				if (!keyDown[e.button.button])
				{
					std::cout << "Mouse pressed : " << (int)(e.button.button) << '\n';

					mousePressed[e.button.button] = true;
					mCleanMouse.push(e.button.button);
				}
				mouseDown[e.button.button] = true;
				#pragma endregion
				break;

			case SDL_MOUSEBUTTONUP:
				#pragma region Mouse up
				if (e.button.button >= MOUSE_SIZE) break;

				mouseDown[e.button.button] = false;
				#pragma endregion
				break;
			}
		}

		#pragma region Mouse Motion
		int newMouseX, newMouseY;
		Uint32 mouseState = SDL_GetMouseState(&newMouseX, &newMouseY);

		newMouseX /= Game::PIXEL_SIZE;
		newMouseY /= Game::PIXEL_SIZE;

		if (newMouseX != mouseX || newMouseY != mouseY)
		{
			relativeX = newMouseX - mouseX;
			relativeY = newMouseY - mouseY;

			mouseX = newMouseX;
			mouseY = newMouseY;
		}
		else
		{
			relativeX = 0;
			relativeY = 0;
		}
		#pragma endregion

		return true;
	}
}