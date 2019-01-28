#ifndef SDLKEYS_H
#define SDLKEYS_H
#include <string>
#include "Files/vector.h"
#include <SDL2/SDL.h>

class Input
{
	public:
		struct Mouse
		{
			bool leftPressed;
			bool rightPressed;
			int x;
			int y;
		};

		Input();

		void input();
		inline bool isDown(int key) {return keysDown.contains(key);}
		inline bool wasPressedFirst(int source, int compare) {return keysDown.getIndex(source) < keysDown.getIndex(compare);}

		inline Mouse getMouse() {return mouse;}
		inline Vector<int> getKeysDown() {return keysDown;}
		inline void setQuitRef(bool* address) {quit = address;}

	private:
		Vector<int> keysDown;
		Mouse mouse;

		void handleMouseButton(SDL_Event event, bool down = true);
		void handleMouseMotion(SDL_Event event);
		void handleKey(SDL_Event event, bool down = true);
		bool* quit;
};

#endif // SDLKEYS_H
