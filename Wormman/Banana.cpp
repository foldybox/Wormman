// Banana.cpp

#include "Banana.h"


void Banana::on_eat(Entity* e)
{
	e->addEnergy(50);
	setIsEaten(true);
}
