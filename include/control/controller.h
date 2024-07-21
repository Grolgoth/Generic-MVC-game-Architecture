#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "input.h"

class SDL;
class Model;

class Controller
{
	public:
		Controller(Model* model, bool* quitref, SDL* sdl);
		~Controller();

	void process();

	private:
		void checkFullscreen();

		Input input;
		Model* model;
		SDL* sdl;
		bool recentFullscreen = false;
};

#endif // CONTROLLER_H
