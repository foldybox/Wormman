// Item.cpp

#include "Item.h"

void Item::draw()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
	glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());
	glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);

	glPushMatrix();

	glTranslatef(getXCenter() + position.x * getXSize(), getYCenter() + position.y * getYSize(), getZCenter() + position.z * getZSize());
	GraphUtils::parallelepiped(getXSize(), getYSize(), getZSize());

	glPopMatrix();
}