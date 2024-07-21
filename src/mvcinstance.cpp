#include "mvcinstance.h"
#include <SDLObj.h>
#include "controller.h"
#include "model/model.h"
#include "view.h"
#include "game.h"

MvcInstance::MvcInstance(SDL* sdl, bool* quitref, int* fps) : sdl(sdl), model(new Model())
{
	controller = new Controller(model, quitref, sdl);
	view = new View(sdl, model);
}

MvcInstance::~MvcInstance()
{
	delete controller;
	view->cleanUp();
	delete view;
	model->cleanUp();
	delete model;
}

void MvcInstance::applyResolutionChangeToWindow()
{
	GameSettings* settings = Game::getGameSettings();
	sdl->changeWindowSize(settings->WINW, settings->WINH);
}

void MvcInstance::render(int framerate, bool* resolutionChanged)
{
	if (*resolutionChanged)
	{
		applyResolutionChangeToWindow();
		*resolutionChanged = false;
	}
	SDL_RenderClear(sdl->getRenderer());
	view->render(framerate);
	sdl->render();
	SDL_Delay(5);
}

void MvcInstance::update()
{
	controller->process();
}
