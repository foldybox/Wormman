// Orange.h

#ifndef Orange_h
#define Orange_h

#include "Item.h"
class Orange : public Item
{
public:
	Orange(float xCenter, float yCenter, float zCenter,
		float xSize, float ySize, float zSize,
		vector3 position)
		: Item(xCenter, yCenter, zCenter,
			xSize, ySize, zSize,
			position)
	{
		setColors(diffOrange, ambiOrange, specOrange);
	}
	virtual void on_eat(Entity* e);
};

#endif

