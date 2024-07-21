#include "game.h"
#include <SDL.h>
#include <settingsmanager.h>
#include <algorithmz.h>
#include <encoder.h>
#include <fstring.h>
#include "gamesettings.h"
#include <SDLObj.h>
#include "mvcinstance.h"
#include <vector.h>

GameSettings Game::settings;

Game::Game()
{
	mTimer = Timer::getTimer();
	previousGameTick = 0;
	currentGameTick = 0;
	loopsWithTimeToSpare = 0;
	loadSettings();
	sdl = new SDL(800, 600, SDL_INIT_AUDIO & SDL_INIT_EVENTS & SDL_INIT_TIMER & SDL_INIT_VIDEO);
	mvci = new MvcInstance(sdl, &quit, &settings.FPS);
	healthCheck();
}

Game::~Game()
{
	delete mTimer;
	delete sdl;
	delete mvci;
}

void Game::start()
{
	while(quit > 0)
		mainloop();
}

void Game::mainloop()
{
	bool skipFrame = false;
	currentGameTick = mTimer->get_elt();
	mvci->update();

	if (!quit)
	{
		if (currentGameTick - previousGameTick >= settings.TICKS_PER_FRAME)
			skipFrame = true;

		timeSinceLastRenderFrame += currentGameTick - previousGameTick;
		if(!skipFrame && (settings.TICKS_PER_RENDER_FRAME >= settings.TICKS_PER_FRAME || timeSinceLastRenderFrame >= settings.TICKS_PER_RENDER_FRAME))
		{
			timeSinceLastRenderFrame = 0;
			mvci->render(settings.FPS, &settings.changed);
			if (mTimer->get_elt() - previousGameTick < settings.TICKS_PER_FRAME / 3)
				updateLoopsWithTimeToSpare(1);
		}
		else if (currentGameTick - previousGameTick >= settings.TICKS_PER_RENDER_FRAME || skipFrame)
		{
			//std::cerr << "Couln't render at this framerate because there was not enough time!" << std::endl;
			checkIfSlowdownRequired();
			skipFrame = true;
			updateLoopsWithTimeToSpare(-2);
		}

		int elt = mTimer->get_elt() - currentGameTick;
		previousGameTick = currentGameTick;
		if(!skipFrame && elt < settings.TICKS_PER_FRAME)
		{
			SDL_Delay(settings.TICKS_PER_FRAME - elt);
			previousGameTick += settings.TICKS_PER_FRAME - elt;
		}
	}
}

void Game::checkIfSlowdownRequired()
{
	if (settings.TICKS_PER_RENDER_FRAME > 30)
		return;
	if (loopsWithTimeToSpare <= -10)
	{
		//std::cout << "slowing down!" << std::endl;
		settings.changeTicksPerFrame(10);
		loopsWithTimeToSpare = 0;
	}
}

void Game::checkIfSpeedupRequired()
{
	if (settings.FPS > 200)
		return;
	if (loopsWithTimeToSpare >= 20)
	{
		//std::cout << "fps " << settings.FPS << std::endl;
		settings.changeFPS(10);
		loopsWithTimeToSpare = 0;
	}
}

void Game::updateLoopsWithTimeToSpare(int change)
{
	if (loopsWithTimeToSpare < 21 && loopsWithTimeToSpare > -10)
		loopsWithTimeToSpare += change;
}

void Game::healthCheck()
{
	if(mTimer == nullptr)
		throw "Error: could not initialize a timer. Aborting game.";
	if(settings.FPS < 30)
		settings.FPS = 30;
	if(settings.FPS > 200)
		settings.FPS = 200;
	settings.TICKS_PER_RENDER_FRAME = 1000 / settings.FPS;
	if (!sdl->isHealthy())
		throw "An error occured when trying to initialize SDL. Aborting game.";
	if (settings.WINH != 600 || settings.WINW != 800)
		sdl->changeWindowSize(settings.WINW, settings.WINH);
}

void Game::loadSettings()
{
	checkGameSettings();
	Encoder* encoder = new Encoder(Algorithm("x=2*x-4"), Algorithm("x=(x+4)/2"));
	Settings* settings = SettingsManager::getSettings("../data/settings/gamesettings", true, Settings::PLAIN, encoder);
	std::vector<std::string> settingsList = settings->get({"screen.winw", "screen.winh", "graphics.fps"});
	this->settings.WINW = FString(settingsList[0]).toInt();
	this->settings.WINH = FString(settingsList[1]).toInt();
	this->settings.FPS = FString(settingsList[2]).toInt();
	//printSettings(this->settings);
	delete settings;
}

void GameSettings::changeFPS(int change)
{
	FPS += change;
	TICKS_PER_RENDER_FRAME = 1000 / FPS;
}

void GameSettings::changeTicksPerFrame(int change)
{
	TICKS_PER_RENDER_FRAME += change;
	FPS = 1000 / TICKS_PER_RENDER_FRAME;
}
