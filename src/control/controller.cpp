#include "controller.h"
#include "model/model.h"

Controller::Controller(Model* model, bool* quitref) : model(model)
{
	input.setQuitRef(quitref);
}

Controller::~Controller()
{
	//dtor
}

void Controller::process()
{
	input.input();
	model->update(input.getKeysDown(), input.getMouse());
}
