// Object.cpp

#include "Object.h"


// Конструктор:

Object::Object(float xCenter, float yCenter, float zCenter,
	float xSize, float ySize, float zSize,
	float* diffColor, float* ambiColor, float* specColor)
{
	setCoords(xCenter, yCenter, zCenter);
	setSize(xSize, ySize, zSize);
	setColors(diffColor, ambiColor, specColor);
}

Object::Object(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	setCoords(xCenter, yCenter, zCenter);
	setSize(xSize, ySize, zSize);
}

// Функції доступу:

void Object::setCoords(float xCenter, float yCenter, float zCenter)
{
	this->xCenter = xCenter;
	this->yCenter = yCenter;
	this->zCenter = zCenter;
}

void Object::setSize(float xSize, float ySize, float zSize)
{
	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;
}

void Object::setColors(float* diffColor, float* ambiColor, float* specColor)
{
	this->diffColor = diffColor;
	this->ambiColor = ambiColor;
	this->specColor = specColor;
}