#ifndef SDL_H
#define SDL_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Surface* load_image(std::string filename);
SDL_Surface* fontToSurface(TTF_Font* font, std::string text, SDL_Color C);
SDL_Color createColor(int r, int g, int b, int a);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = nullptr);

class SDL
{
	public:
		SDL(int winW, int winH, Uint32 initFlags = 0);
		~SDL();
		void render();
		inline void addSurfaceToTarget(int x, int y, SDL_Surface* source, SDL_Rect* clip = nullptr) {apply_surface(x, y, source, target, clip);}
		inline SDL_Surface* getTarget() {return target;}
		inline bool isHealthy() {return healthy;}

	private:
		bool init(Uint32 flags);
		bool healthy = false;
		int WINW;
		int WINH;
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Surface* target;
};

#endif // SDL_H
