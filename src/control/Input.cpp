#include "input.h"

Input::Input() : keysDown(true), newKeysDown(true)
{
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
}

void Input::input()
{
	mousePos();
	newKeysDown.clear();
	SDL_Event event;
    while (SDL_PollEvent(&event))
    {
    	switch(event.type)
    	{
		case SDL_KEYDOWN:
			handleKey(event);
			break;
		case SDL_KEYUP:
			handleKey(event, false);
			break;
		case SDL_MOUSEBUTTONDOWN:
			handleMouseButton(event);
			break;
		case SDL_MOUSEBUTTONUP:
			handleMouseButton(event, false);
			break;
		case SDL_QUIT:
			*quit = true;
			return;
    	}
    }
    updateFramesDown();
}

bool Input::isDown(SDL_Scancode key)
{
	for (int i = 0; i < keysDown.size(); i++)
		if (keysDown.get(i).key == key)
			return true;
	return false;
}

void Input::handleMouseButton(SDL_Event event, bool down)
{
	if (event.button.button == SDL_BUTTON_LEFT && !mouse.leftPressed)
		mouse.leftPressed = down;
	if (event.button.button == SDL_BUTTON_RIGHT && !mouse.rightPressed)
		mouse.rightPressed = down;
}

void Input::mousePos()
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
}

void Input::handleKey(SDL_Event event, bool down)
{
	SDL_Scancode scancode = event.key.keysym.scancode;
	bool found = false;
	if (down)
	{
		for (int i = 0; i < keysDown.size(); i++)
		{
			if (keysDown.get(i).key == scancode)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			keysDown.add(Key {scancode, 0});
			newKeysDown.add(scancode);
			if (SDL_GetKeyFromScancode(scancode) == SDLK_p)
			{
				if (*quit == 2)
					*quit = 1;
				else
					*quit = 2;
			}
		}
	}
	//We don't need to free this, SDL's got our back.
	const Uint8 *state = SDL_GetKeyboardState(nullptr);
	for (int i = 0; i < keysDown.size(); i++)
	{
		if (!state[keysDown.get(i).key])
		{
			keysDown.remove(i);
			i--;
		}
	}
}

void Input::updateFramesDown()
{
	for (int i = 0; i < keysDown.size(); i++)
		keysDown.getptr(i)->framesDown ++;
}
