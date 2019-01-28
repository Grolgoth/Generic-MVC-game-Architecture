#include "mvcinstance.h"
#include "SDL.h"
#include "controller.h"
#include "model/model.h"
#include "view.h"

MvcInstance::MvcInstance(SDL* sdl, bool* quitref) : sdl(sdl), model(new Model())
{
	controller = new Controller(model, quitref);
	view = new View(sdl, model);
}

MvcInstance::~MvcInstance()
{
	delete controller;
	delete view;
	delete model;
}

void MvcInstance::render()
{
	view->render();
}

void MvcInstance::update()
{
	controller->process();
}
