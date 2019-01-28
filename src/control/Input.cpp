#include "input.h"

Input::Input() : keysDown(true) {}

void Input::input()
{
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
		case SDL_MOUSEMOTION:
			handleMouseMotion(event);
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
}

void Input::handleMouseButton(SDL_Event event, bool down)
{
	if (event.button.button == SDL_BUTTON_LEFT && !mouse.leftPressed)
		mouse.leftPressed = down;
	if (event.button.button == SDL_BUTTON_RIGHT && !mouse.rightPressed)
		mouse.rightPressed = down;
}

void Input::handleMouseMotion(SDL_Event event)
{
	mouse.x = event.motion.x;
	mouse.y = event.motion.y;
}

void Input::handleKey(SDL_Event event, bool down)
{
	if (down)
		keysDown.add(event.key.keysym.scancode);
	//We don't need to free this, SDL's got our back.
	const Uint8 *state = SDL_GetKeyboardState(nullptr);
	for (unsigned int i = 0; i < keysDown.size(); i++)
	{
		if (!state[keysDown.get(i)])
		{
			keysDown.remove(i);
			i--;
		}
	}
}
