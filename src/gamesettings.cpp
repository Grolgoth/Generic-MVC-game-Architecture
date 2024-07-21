#include "gamesettings.h"
#include <file.h>
#include <algorithmz.h>
#include <iostream>
#include "Game.h"
#include <settingsmanager.h>

void checkGameSettings(bool forceNew)
{
	File global("../data/settings/gamesettings", false);
	if (!global.exists())
	{
		global.create();
		global.open();
		global.write("[screen]\nwinw=800\nwinh=600\n\n[graphics]\nfps=30");
		global.close();
		global.open();
		global.encode(Algorithm("x=2*x-4"));
		global.close();
	}
	else if (forceNew)
	{
		global.open();
		global.clear();
		global.write("[screen]\nwinw=800\nwinh=600\n\n[graphics]\nfps=30");
		global.close();
		global.open();
		global.encode(Algorithm("x=2*x-4"));
		global.close();
	}
}

void writeGameSetting(std::string name, std::string value)
{
	checkGameSettings();
	Encoder* encoder = new Encoder(Algorithm("x=2*x-4"), Algorithm("x=(x+4)/2"));
	Settings* settings = SettingsManager::getSettings("../data/settings/gamesettings", true, Settings::PLAIN, encoder);
	settings->write(name, value);
	delete settings;
}

std::vector<std::string> getGameSettings(std::vector<std::string> keys)
{
	checkGameSettings();
	Encoder* encoder = new Encoder(Algorithm("x=2*x-4"), Algorithm("x=(x+4)/2"));
	Settings* settings = SettingsManager::getSettings("../data/settings/gamesettings", true, Settings::PLAIN, encoder);
	std::vector<std::string> settingsList = settings->get(keys);
	delete settings;
	return settingsList;
}

void printSettings()
{
	File file("../data/settings/gamesettings");
	file.open();
	file.decode(Algorithm("x=2*x-4"), Algorithm("x=(x+4)/2"));
	file.close();
	file.open();
	std::cout << file.getFromFile() << std::endl;
	file.encode(Algorithm("x=2*x-4"));
	file.close();
}
