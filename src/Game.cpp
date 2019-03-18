#include "Game.h"
#include <SDL2/SDL.h>
#include "Files/settingsmanager.h"
#include "Files/algorithmz.h"
#include "Files/encoder.h"
#include "Files/string.h"
#include "gamesettings.h"
#include "SDL.h"
#include "mvcinstance.h"
#include <vector>

Game::Game()
{
	quit = false;
	mTimer = Timer::getTimer();
	previousGameTick = 0;
	currentGameTick = 0;
	loopsWithTimeToSpare = 0;
	loadSettings();
	sdl = new SDL(settings.WINW, settings.WINH, SDL_INIT_AUDIO & SDL_INIT_EVENTS & SDL_INIT_TIMER & SDL_INIT_VIDEO);
	mvci = new MvcInstance(sdl, &quit);
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
	while(!quit)
		mainloop();
}

void Game::mainloop()
{
	bool noDelay = false;
	currentGameTick = mTimer->get_elt();

	mvci->update();
	if(currentGameTick - previousGameTick < settings.TICKS_PER_FRAME)
	{
		mvci->render();
	}
	else
	{
		//std::cerr << "Couln't render at this framerate because there was not enough time!" << std::endl;
		checkIfSlowdownRequired();
		noDelay = true;
		updateLoopsWithTimeToSpare(-2);
	}

	int elt = mTimer->get_elt() - previousGameTick;
	previousGameTick = currentGameTick;
	if(!noDelay && elt < settings.TICKS_PER_FRAME)
	{
		SDL_Delay(settings.TICKS_PER_FRAME - elt);
		previousGameTick += settings.TICKS_PER_FRAME - elt;
		if (settings.TICKS_PER_FRAME - elt > 1)
			checkIfSpeedupRequired();
		updateLoopsWithTimeToSpare(1);
	}
}

void Game::checkIfSlowdownRequired()
{
	if (settings.TICKS_PER_FRAME > 990)
		return;
	if (loopsWithTimeToSpare < -10)
	{
		//std::cout << "slowing down!" << std::endl;
		settings.changeTicksPerFrame(10);
		loopsWithTimeToSpare = 0;
	}
}

void Game::checkIfSpeedupRequired()
{
	if (settings.FPS > 300)
		return;
	if (loopsWithTimeToSpare == 20)
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
	if(settings.FPS < 20)
		settings.FPS = 20;
	if(settings.FPS > 300)
		settings.FPS = 300;
	settings.TICKS_PER_FRAME = 1000 / settings.FPS;
	if (!sdl->isHealthy())
		throw "An error occured when trying to initialize SDL. Aborting game.";
}

void Game::loadSettings()
{
	checkGameSettings();
	Encoder* encoder = new Encoder(Algorithm("x=2*x-4"), Algorithm("x=(x+4)/2"));
	Settings* settings = SettingsManager::getSettings("../../Settings/gamesettings", true, Settings::PLAIN, encoder);
	std::vector<std::string> settingsList = settings->get({"screen.winw", "screen.winh", "screen.fullscreen", "graphics.fps"});
	this->settings.WINW = String(settingsList[0]).toInt();
	this->settings.WINH = String(settingsList[1]).toInt();
	this->settings.FULLSCREEN = String(settingsList[2]).toBool();
	this->settings.FPS = String(settingsList[3]).toInt();
	this->settings.TICKS_PER_FRAME = 1000 / this->settings.FPS;
	//printSettings(this->settings);
	delete settings;
}

void GameSettings::changeFPS(int change)
{
	FPS += change;
	TICKS_PER_FRAME = 1000 / FPS;
}

void GameSettings::changeTicksPerFrame(int change)
{
	TICKS_PER_FRAME += change;
	FPS = 1000 / TICKS_PER_FRAME;
}
