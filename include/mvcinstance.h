#ifndef MVCINSTANCE_H
#define MVCINSTANCE_H

class SDL;
class Controller;
class Model;
class View;

class MvcInstance
{
	public:
		MvcInstance(SDL* sdl, bool* quitref, int* fps);
		~MvcInstance();
		void update();
		void render(int framerate, bool* resolutionChanged);

	private:
		void applyResolutionChangeToWindow();

		MvcInstance(MvcInstance& other);
		SDL* sdl;
		Controller* controller;
		Model* model;
		View* view;
};

#endif // MVCINSTANCE_H
