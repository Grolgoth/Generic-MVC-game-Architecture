#ifndef MVCINSTANCE_H
#define MVCINSTANCE_H

class SDL;
class Controller;
class Model;
class View;

class MvcInstance
{
	public:
		MvcInstance(SDL* sdl, bool* quitref);
		~MvcInstance();
		void update();
		void render();

	private:
		SDL* sdl;
		Controller* controller;
		Model* model;
		View* view;
};

#endif // MVCINSTANCE_H
