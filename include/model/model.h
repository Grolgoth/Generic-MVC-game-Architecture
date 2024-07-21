#ifndef MODEL_H
#define MODEL_H
#include <vector.h>
#include "input.h"


class Model
{
	public:
		Model();
		~Model();

		void update(Vector<Input::Key> keysDown, Input::Mouse mouse);
		void cleanUp();

	private:
};

#endif // MODEL_H
