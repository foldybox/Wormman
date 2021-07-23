//Entity.cpp

#include <gl/glut.h>
#include "Utils.h"
#include "Entity.h"

using namespace GraphUtils;


void Entity::setColor(float* headDiff, float* headAmbi, float* headSpec, float* bodyDiff, float* bodyAmbi, float* bodySpec)
{
	this->headDiff = headDiff;
	this->headAmbi = headAmbi;
	this->headSpec = headSpec;

	this->bodyDiff = bodyDiff;
	this->bodyAmbi = bodyAmbi;
	this->bodySpec = bodySpec;
}

void Entity::setHeadColor(float* diff, float* ambi, float* spec)
{
	this->headDiff = diff;
	this->headAmbi = ambi;
	this->headSpec = spec;
}

void Entity::setBodyColor(float* diff, float* ambi, float* spec)
{
	this->bodyDiff = diff;
	this->bodyAmbi = ambi;
	this->bodySpec = spec;
}

void Entity::step()
{
	vector3 lastSegmentPos = segments[segments.size() - 1];

	//move body
	for (int i = segments.size() - 1; i > 0; i--)
	{
		segments[i].x = segments[i - 1].x;
		segments[i].z = segments[i - 1].z;
	}

	//don't allow to move head back
	if (((direction == 0) && (lastDirection != 3)) || ((direction == 1) && (lastDirection != 2)) || ((direction == 2) && (lastDirection != 1)) || ((direction == 3) && (lastDirection != 0)))
		lastDirection = direction;

	//move head
	if (lastDirection == 0) segments[0].z += 1;
	if (lastDirection == 1) segments[0].x -= 1;
	if (lastDirection == 2) segments[0].x += 1;
	if (lastDirection == 3) segments[0].z -= 1;

	//self-collision check
	for (size_t i = 1; i < segments.size(); i++)
	{
		if (segments[0] == segments[i])
		{
			on_self_collision(i);
		}
	}

	//wall collision check
	if (segments[0].x < 0) segments[0].x = 25;
	if (segments[0].x > 25) segments[0].x = 0;
	if (segments[0].z < 0) segments[0].z = 25;
	if (segments[0].z > 25) segments[0].z = 0;

	//enough energy check
	if (energy >= 100)
	{
		segments.push_back(lastSegmentPos);
		energy -= 100;
	}
}

void Entity::draw()
{
	glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);

	for (int i = 0; i < segments.size(); i++)
	{
		if (i == 0)
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, headAmbi);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, headDiff);
			glMaterialfv(GL_FRONT, GL_SPECULAR, headSpec);
		}
		else
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, bodyAmbi);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyDiff);
			glMaterialfv(GL_FRONT, GL_SPECULAR, bodySpec);
		}
		glPushMatrix();
		glTranslatef(getXCenter() + segments[i].x * getXSize(), getYCenter() + segments[i].y * getYSize(), getZCenter() + segments[i].z * getZSize());
		GraphUtils::parallelepiped(getXSize(), getYSize(), getZSize());
		glPopMatrix();
	}
}
