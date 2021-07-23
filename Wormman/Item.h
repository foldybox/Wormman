// Item.h

#ifndef Item_h
#define Item_h

#include <gl/glut.h>
#include "Utils.h"
#include "Object.h"
#include "Entity.h"

using namespace GraphUtils;

class Item : public Object
{
	vector3 position;
	bool isEaten;
public:
	Item(float xCenter, float yCenter, float zCenter,
		float xSize, float ySize, float zSize, vector3 position)
		: Object(xCenter, yCenter, zCenter,
			xSize, ySize, zSize)
	{
		this->position = position;
		this->isEaten = false;
		setColors(diffGreen, ambiGreen, specGreen);
	}
	vector3 getPosition() { return this->position; };

	void setIsEaten(bool isEaten) { this->isEaten = isEaten; }
	bool getIsEaten() { return isEaten; }

	virtual void draw();
	virtual void on_eat(Entity* e) = 0;
};

#endif

