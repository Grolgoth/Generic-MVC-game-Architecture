#ifndef GAME_H
#define GAME_H
#include "Timelib/Timer.h"

class MvcInstance;
class SDL;

struct GameSettings
{
	int WINW;
	int WINH;
	int FPS;
	bool FULLSCREEN;
	int TICKS_PER_FRAME;

	void changeFPS(int change);
	void changeTicksPerFrame(int change);
};

class Game
{
	public:
		Game();
		~Game();
		void start();

	private:
		bool quit;
		int currentGameTick;
		int previousGameTick;
		int loopsWithTimeToSpare;
		Timer* mTimer;
		SDL* sdl;
		MvcInstance* mvci;

		void mainloop();
		void healthCheck();
		void loadSettings();
		void checkIfSlowdownRequired();
		void checkIfSpeedupRequired();
		void updateLoopsWithTimeToSpare(int change);
		GameSettings settings;
};

#endif // GAME_H
