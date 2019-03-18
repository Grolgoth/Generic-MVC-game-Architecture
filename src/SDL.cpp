#include "SDL.h"

SDL::SDL(int winW, int winH, Uint32 initFlags) : target(nullptr)
{
	WINW = winW;
	WINH = winH;
	if(!init(initFlags))
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	else
		healthy = true;
}

SDL::~SDL()
{
	if (target != nullptr)
		SDL_FreeSurface(target);
	SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    TTF_Quit();
    SDL_Quit();
}

void SDL::render()
{
	SDL_RenderClear(m_renderer);
    SDL_Texture* screen = SDL_CreateTextureFromSurface(m_renderer, target);
    SDL_RenderCopy(m_renderer, screen, NULL, NULL);
    SDL_RenderPresent(m_renderer);
    SDL_DestroyTexture(screen);
    SDL_FreeSurface(target);
	target = SDL_CreateRGBSurface(SDL_SWSURFACE,WINW,WINH,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
}

bool SDL::init(Uint32 flags)
{
	if(SDL_Init(flags))
		return false;
	if(TTF_Init())
		return false;
	if(SDL_CreateWindowAndRenderer( WINW, WINH, SDL_WINDOW_SHOWN, &m_window, &m_renderer)) //possibly use settings for fullscreen, resizable window etc
		return false;
	if (m_window == nullptr || m_renderer == nullptr)
		return false;
	return true;
}

SDL_Surface* load_image(std::string filename)
{
    SDL_Surface* loadedImage = SDL_LoadBMP(filename.c_str());
    if(loadedImage != nullptr)
	{
		// map the colorkey
		Uint32 colorkey = SDL_MapRGB( loadedImage->format, 0, 0xFF, 0xFF );
        // make it transparent
        SDL_SetColorKey( loadedImage, SDL_TRUE, colorkey );
	}
    else
		std::cerr << "Error loading image with SDL: " << SDL_GetError() << std::endl;
    return loadedImage;
}

SDL_Surface* fontToSurface(TTF_Font* font, std::string text, SDL_Color C)
{
    return TTF_RenderText_Solid(font, text.c_str(), C);
}

SDL_Color createColor(int r, int g, int b, int a)
{
    SDL_Color C;
    C.r = r;
    C.b = b;
    C.g = g;
    C.a = a;
    return C;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Make a temporary rectangle to hold the offsets on the screen
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, clip, destination, &offset );
}
