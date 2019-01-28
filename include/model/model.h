#ifndef MODEL_H
#define MODEL_H
#include "Files/vector.h"
#include "input.h"


class Model
{
	public:
		Model();
		~Model();

		void update(Vector<int> keysDown, Input::Mouse mouse);

	private:
};

#endif // MODEL_H
