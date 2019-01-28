#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "input.h"

class Model;


class Controller
{
	public:
		Controller(Model* model, bool* quitref);
		~Controller();

	void process();

	private:
		Input input;
		Model* model;
};

#endif // CONTROLLER_H
