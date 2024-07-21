#include "controller.h"
#include "model/model.h"
#include <SDLObj.h>
#include <Timer.h>
#include <File.h>

Controller::Controller(Model* model, bool* quitref, SDL* sdl) : model(model), sdl(sdl)
{
	input.setQuitRef(quitref);
}

Controller::~Controller()
{

}

void Controller::checkFullscreen()
{
	int hits = 0;
	if (input.getKeysDown().size() > 1)
	{
		if (recentFullscreen)
			return;
		for (Input::Key index : input.getKeysDown().toStdVector())
		{
			if ((SDL_GetKeyFromScancode(index.key) == SDLK_RALT || SDL_GetKeyFromScancode(index.key) == SDLK_LALT) && hits == 0)
				hits ++;
			else if (SDL_GetKeyFromScancode(index.key) == SDLK_f && hits == 1)
			{
				hits = 2;
				recentFullscreen = true;
				break;
			}
			else
				hits = 0;

		}
	}
	else
		recentFullscreen = false;
	if (hits == 2)
		sdl->fullscreen();
}

void Controller::process()
{
	input.input();
	checkFullscreen();
    model->update(input.getKeysDown(), input.getMouse());
}
