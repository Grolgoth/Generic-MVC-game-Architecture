#include "view.h"

View::View(SDL* sdl, Model* model) : sdl(sdl), model(model)
{
	//ctor
}

View::~View()
{
	//no need to delete our sdl instance, it should happen in a destructer higher up in the hierarchy
}

void View::render()
{

}
