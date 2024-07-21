#ifndef SDLKEYS_H
#define SDLKEYS_H
#include <string>
#include <vector.h>
#include <SDL.h>

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

		struct Key
		{
			SDL_Scancode key;
			int framesDown;
			bool operator==(Key& other)
			{
				return other.key == key && other.framesDown == framesDown;
			}
		};

		Input();

		void input(); //return true if game was paused / unpaused.
		bool isDown(SDL_Scancode key);
		//inline bool wasPressedFirst(SDL_Scancode source, SDL_Scancode compare) {return keysDown.getIndex(source) < keysDown.getIndex(compare);}

		inline bool getPause() {return pause;}
		inline Mouse getMouse() {return mouse;}
		inline Vector<Key> getKeysDown() {return keysDown;}
		inline Vector<SDL_Scancode> getNewKeysDown() {return newKeysDown;}
		inline void setQuitRef(bool* address) {quit = address;}

	private:
		Vector<Key> keysDown;
		Vector<SDL_Scancode> newKeysDown;
		Mouse mouse;

		void handleMouseButton(SDL_Event event, bool down = true);
		void mousePos();
		void handleKey(SDL_Event event, bool down = true);
		void updateFramesDown();
		bool* quit;
		bool pause = false;
};

#endif // SDLKEYS_H
