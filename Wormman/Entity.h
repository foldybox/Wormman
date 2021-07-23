// Entity.h

#ifndef Entity_h
#define Entity_h

#include <vector>
#include "Utils.h"
#include "Object.h"

using namespace GraphUtils;

class Entity : public Object
{
	std::vector<vector3> segments;
	int direction;
	int lastDirection;
	bool isDead;
	int lifes;
	int energy;

	float* headDiff;
	float* headAmbi;
	float* headSpec;

	float* bodyDiff;
	float* bodyAmbi;
	float* bodySpec;
public:
	Entity(float xCenter, float yCenter, float zCenter,
		float xSize, float ySize, float zSize,
		vector3 startPosition, int startLength)
		: Object(xCenter, yCenter, zCenter,
			xSize, ySize, zSize)
	{
		headDiff = diffGray;
		headAmbi = ambiGray;
		headSpec = specGray;

		bodyDiff = diffWhite;
		bodyAmbi = ambiWhite;
		bodySpec = specWhite;

		getSegments().push_back(startPosition);

		for (size_t i = 0; i < startLength; i++)
		{
			addSegment(segments[0]);
		}

		isDead = false;
		energy = 0;
		lifes = 1;
		direction = 0;
		lastDirection = 0;
	}

	std::vector<vector3>& getSegments() { return segments; };
	void addSegment(vector3 v) { segments.push_back(v); };

	int  getDirection() { return direction; };
	void setDirection(int direction) { this->direction = direction; };

	int  getLastDirection() { return direction; };
	void setLastDirection(int direction) { this->direction = direction; };

	void setColor(float* headDiff, float* headAmbi, float* headSpec, float* bodyDiff, float* bodyAmbi, float* bodySpec);
	void setHeadColor(float* diff, float* ambi, float* spec);
	void setBodyColor(float* diff, float* ambi, float* spec);

	void setIsDead(bool isDead) { this->isDead = isDead; };
	bool getIsDead() { return this->isDead; };

	void addEnergy(int energy) { this->energy += energy; };
	void removeEnergy(int energy) { this->energy -= energy; };
	void setEnergy(int energy) { this->energy = energy; };
	int  getEnergy() { return energy; };

	void addLifes(int lifes) { this->lifes += lifes; };
	void removeLifes(int lifes) { this->lifes -= lifes; };
	void setLifes(int lifes) { this->lifes = lifes; };
	int  getLifes() { return lifes; };

	void step();
	void draw();
	virtual void control(int direction) = 0;
	virtual void on_self_collision(int i) = 0;
};

#endif

