// Banana.h

#ifndef Banana_h
#define Banana_h

#include "Item.h"
class Banana : public Item
{
public:
	Banana(float xCenter, float yCenter, float zCenter,
		float xSize, float ySize, float zSize,
		vector3 position)
		: Item(xCenter, yCenter, zCenter,
			xSize, ySize, zSize,
			position)
	{
		setColors(diffYellow, ambiYellow, specYellow);
	}
	virtual void on_eat(Entity* e);
};

#endif

