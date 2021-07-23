// Apple.h

#ifndef Apple_h
#define Apple_h

#include "Item.h"

class Apple : public Item
{
public:
	Apple(float xCenter, float yCenter, float zCenter,
		float xSize, float ySize, float zSize,
		vector3 position)
		: Item(xCenter, yCenter, zCenter,
			xSize, ySize, zSize, 
			position)
	{
		setColors(diffGreen, ambiGreen, specGreen);
	};
	virtual void on_eat(Entity* e);
};

#endif

