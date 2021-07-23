// Level.h

#ifndef Level_h
#define Level_h

#include "Object.h"

class Level : public Object
{
public:
	Level(float xCenter, float yCenter, float zCenter,
		float xSize, float ySize, float zSize,
		float* diffColor, float* ambiColor, float* specColor)
		: Object(xCenter, yCenter, zCenter,
			xSize, ySize, zSize,
			specColor, diffColor, ambiColor) { }
	virtual void draw();
};

#endif
