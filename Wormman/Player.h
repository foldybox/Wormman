// Player.h

#ifndef Player_h
#define Player_h

#include "Entity.h"
class Player : public Entity
{
public:
	Player(float xCenter, float yCenter, float zCenter,
		float xSize, float ySize, float zSize,
		vector3 startPosition, int startLength)
		: Entity(xCenter, yCenter, zCenter,
			xSize, ySize, zSize,
			startPosition, startLength)
	{

	}
	virtual void control(int direction);
	virtual void on_self_collision(int i);
};

#endif

