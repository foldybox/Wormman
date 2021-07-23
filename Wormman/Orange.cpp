// Orange.cpp

#include "Orange.h"


void Orange::on_eat(Entity* e)
{
	e->addEnergy(70);
	setIsEaten(true);
}

