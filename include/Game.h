#ifndef GAME_H
#define GAME_H
#include <Timer.h>

class MvcInstance;
class SDL;

struct GameSettings
{
	int WINW;
	int WINH;
	int FPS;
	int TICKS_PER_RENDER_FRAME;
	const int TICKS_PER_FRAME = 1000 / 30;

	bool changed = false;
	void changeFPS(int change);
	void changeTicksPerFrame(int change);
};

class Game
{
	public:
		Game();
		~Game();
		void start();
		static GameSettings* getGameSettings(){return &settings;}

	private:
		bool quit = 1;
		int currentGameTick;
		int previousGameTick;
		int timeSinceLastRenderFrame;
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
		static GameSettings settings;
};

#endif // GAME_H
