#include "gamesettings.h"
#include "Files/file.h"
#include "Files/algorithmz.h"
#include <iostream>
#include "Game.h"

void checkGameSettings()
{
	File global("../../Settings/gamesettings");
	if (!global.exists())
	{
		global.create();
		global.open();
		global.write("[screen]\nwinw=800\nwinh=600\nfullscreen=false\n\n[graphics]\nfps=100");
		global.encode(Algorithm("x=2*x-4"));
		global.close();
	}
}

void printSettings(GameSettings settings)
{
	std::cout << "Settings loaded:\n"
		<< "WINW: " << settings.WINW << "WINH: " << settings.WINH
		<< "\nFullscreen: " << settings.FULLSCREEN << "\n"
		<< "\nFPS: " << settings.FPS << std::endl;
}
