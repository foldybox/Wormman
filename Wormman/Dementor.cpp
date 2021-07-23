// Dementor.cpp

#include <ctime>
#include "Dementor.h"

void Dementor::control(int direction)
{
	srand((time(0) + index) * 5 + index * 3);
	int r = rand() % 100;

	if (r <= 60)
		setDirection(rand() % 4);
}
