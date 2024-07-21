#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <string>
#include <vector>

struct GameSettings;

void checkGameSettings(bool forceNew = false);
void printSettings();
void writeGameSetting(std::string key, std::string value);
std::vector<std::string> getGameSettings(std::vector<std::string> keys);

#endif // GAMESETTINGS_H
