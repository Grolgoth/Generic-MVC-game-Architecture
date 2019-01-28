#ifndef VIEW_H
#define VIEW_H

class Model;
class SDL;

class View
{
	public:
		View(SDL* sdl, Model* model);
		~View();

		void render();

	protected:

	private:
		SDL* sdl;
		Model* model;
};

#endif // VIEW_H
