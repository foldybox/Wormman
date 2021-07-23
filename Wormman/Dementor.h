// Dementor.h

#ifndef Dementor_h
#define Dementor_h

#include "Entity.h"
class Dementor : public Entity
{
	int index;
public:
	Dementor(float xCenter, float yCenter, float zCenter,
		float xSize, float ySize, float zSize,
		vector3 startPosition, int startLength)
		: Entity(xCenter, yCenter, zCenter,
			xSize, ySize, zSize,
			startPosition, startLength)
	{
		index = 0;
	}
	virtual void control(int direction);
	void setIndex(int i) { this->index = i; };
	virtual void on_self_collision(int i) { };
};

#endif

