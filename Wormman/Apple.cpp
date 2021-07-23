// Apple.cpp

#include <gl/glut.h>
#include "Utils.h"
#include "Apple.h"


void Apple::on_eat(Entity* e)
{
	e->addEnergy(20);
	setIsEaten(true);
}
