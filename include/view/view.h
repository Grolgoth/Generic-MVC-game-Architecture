#ifndef VIEW_H
#define VIEW_H

class Model;
class SDL;

class View
{
	public:
		View(SDL* sdl, Model* model);
		~View();

		void render(int framerate);
		void cleanUp();

	protected:

	private:
		SDL* sdl;
		Model* model;
};

#endif // VIEW_H
