// Scene.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <fstream>
#include <gl/glut.h>
#include "Scene.h"

using namespace GraphUtils;

Scene::Scene()
{
	button = -1;
	width = 0;
	height = 0;
	mouseX = 0;
	mouseY = 0;
	distZ = -6;
	angleX = 0;
	angleY = 30;

	level = new Level(0.0, -0.6, 0.0, 5.2, 1, 5.2, diffWhite, ambiWhite, specWhite);

	//start();

	state = -1;
}

Scene::~Scene()
{
	delete level;
	delete player;

	for (int i = 0; i < dementors.size(); i++)
	{
		delete dementors[i];
	}
	for (int i = 0; i < items.size(); i++)
	{
		delete items[i];
	}
}

void Scene::on_paint(void)
{
	char hint[128];
	char text[128];
	if (state == -1)
	{
		sprintf(hint, "F1 - start game, F3 - zoom in, F4 - zoom out, Esc - exit");
		sprintf(text, "Welcome to Wormman Game");
	}
	else if (state == 0)
	{
		sprintf(hint, "F1 - restart game, F3 - zoom in, F4 - zoom out, Arrows - control, Esc - exit");
		sprintf(text, "Time: %d sec.   Energy: %d   Size: %d", time, player->getEnergy(), player->getSegments().size());
	}
	else if (state == 1)
	{
		sprintf(hint, "F1 - restart game, F3 - zoom in, F4 - zoom out, Esc - exit");
		sprintf(text, "Game over. Score: %d   Time: %d sec.   Energy: %d   Size: %d", score, time, player->getEnergy(), player->getSegments().size());
	}
	else
	{
		sprintf(hint, "F1 - restart game, F3 - zoom in, F4 - zoom out, Esc - exit");
		sprintf(text, "You win! Score: %d   Time: %d sec.   Energy: %d   Size: %d", score, time, player->getEnergy(), player->getSegments().size());
	}
	// Встановлюємо область перегляду таку, щоб вона вміщувала все вікно:
	glViewport(0, 0, width, height);

	// Ініціалізуємо параметри матеріалів і джерела світла:
	float lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // колір фонового освітлення 
	float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // колір дифузного освітлення 
	float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// колір дзеркального відображення
	float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };// розташування джерела світла

	// Встановлюємо параметри джерела світла:
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	if (state == 0)
		glClearColor(0, 0, 0, 0);
	else if(state == -1)
		glClearColor(0.0, 0.0, 0.0, 0);
	else if(state == 1)
		glClearColor(0.1, 0.0, 0.0, 0);
	else
		glClearColor(0.0, 0.1, 0.0, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Для відображення тексту, краще використовувати ортографічну проекцію:
	glOrtho(0, 1, 0, 1, -1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 1, 1);
	drawString(GLUT_BITMAP_HELVETICA_12, hint, 0.01, 0.97);

	if (state == 0)
		glColor3f(1, 1, 0);
	else if (state == -1)
		glColor3f(1, 1, 0);
	else if (state == 1)
		glColor3f(1, 0, 0);
	else
		glColor3f(0, 1, 0);

	drawString(GLUT_BITMAP_HELVETICA_18, text, 0.01, 0.93);
	glPopMatrix();

	// Включаємо режим роботи з матрицею проекцій:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Задаємо усічений конус видимості в лівосторонній системі координат, 
	// 60 - кут видимості в градусах по осі у,
	// width/height - кут видимості уздовж осі x,
	// 1 и 100 - відстань від спостерігача до площин відсікання по глибині:
	gluPerspective(60, width / height, 1, 100);

	// Включаємо режим роботи з видовою матрицею:
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, -0.5, distZ);	// камера з початку координат зсувається на distZ, 

	glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // потім обертається по осі Oy
	glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // потім обертається по осі Ox
	glEnable(GL_DEPTH_TEST);	// включаємо буфер глибини (для відсікання невидимих частин зображення)

								// Включаємо режим для установки освітлення:
	glEnable(GL_LIGHTING);

	// Додаємо джерело світла № 0 (їх може бути до 8), зараз воно світить з "очей":
	glEnable(GL_LIGHT0);

	if (level != nullptr)
		level->draw();

	if (player != nullptr)
		player->draw();

	for (int i = 0; i < dementors.size(); i++)
	{
		dementors[i]->draw();
	}

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->draw();
	}

	// Вимикаємо все, що включили:
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glFlush();
	// показуємо вікно:
	glutSwapBuffers(); // перемикання буферів
}

void Scene::on_size(int width, int height)
{
	this->width = width;
	if (height == 0)
		height = 1;
	this->height = height;
}

void Scene::on_mouse(int button, int state, int x, int y)
{
	// Зберігаємо поточні координати миші:
	mouseX = x;
	mouseY = y;
	if ((state == GLUT_UP)) // кнопка віджата
	{

	}
	this->button = button;  // зберігаємо інформацію про кнопки
	if (state)
	{
		return;
	}
}

void Scene::on_motion(int x, int y)
{
	// view by moving the right mouse button
	if (button == 2)
	{
		angleX += (x - mouseX) * 0.5;
		angleY += (y - mouseY) * 0.5;
		if (angleX > 70)
			angleX = 70;
		else if (angleX < -70)
			angleX = -70;

		if (angleY > 70)
			angleY = 70;
		else if (angleY < 10)
			angleY = 10;

		mouseX = x;
		mouseY = y;
	}
}

void Scene::on_special(int key, int x, int y)
{
	switch (key)
	{
	// new game button - F1
	case GLUT_KEY_F1:
		start();
		break;

	// zoom in button - F3
	case GLUT_KEY_F3:
		if (distZ > -3) break;
		distZ += 0.1;
		break;

	// zoom out button - F4
	case GLUT_KEY_F4:
		if (distZ < -9) break;
		distZ -= 0.1;
		break;

	// move down button - DOWN
	case GLUT_KEY_DOWN:
		player->control(0);
		break;

	// move left button - LEFT
	case GLUT_KEY_LEFT:
		player->control(1);
		break;

	// move up button - UP
	case GLUT_KEY_UP:
		player->control(3);
		break;

	// move right button - RIGHT
	case GLUT_KEY_RIGHT:
		player->control(2);
		break;
	}
}


int sTick = 0;
int pTick = 0;

// Main timer function. It's ticks control main game timer and steps
void Scene::on_timer(int value)
{
	sTick++;
	pTick++;
	if (sTick >= 40) // 1 second counter
	{
		if (state == 0) time++;
		sTick = 0;
	}
	if (pTick >= 2) // 0.200 second counter
	{
		step(value); // call global game step
		pTick = 0;
	}
	on_paint(); // call redraw
}


void Scene::start()
{
	time = 1;
	state = 0;
	score = -1;
	isStat = false;

	player = new Player(-2.5, 0.0, -2.5, 0.2, 0.2, 0.2, vector3(13, 0, 13), 3);

	player->setDirection(0);
	player->setColor(diffBlue, ambiBlue, specBlue, diffLightBlue, ambiLightBlue, specLightBlue);

	dementors.clear();
	items.clear();

	for (size_t i = 0; i < 5; i++)
	{
		srand(std::time(0) * i);

		dementors.push_back(new Dementor(-2.5, 0.0, -2.5, 0.2, 0.2, 0.2, vector3((rand() * (i + 1)) % 26, 0, (rand() * (i + 2)) % 26), 3));
		dementors[i]->setDirection((rand() * (i + 3)) % 4 );
		dementors[i]->setColor(diffRed, ambiRed, specRed, diffGray, ambiGray, specGray);
		dementors[i]->setIndex(i);
	}
}

//Main step function. It control calling of entities steps and main checks
void Scene::step(int value)
{
	if (state == 0)
	{
		player->step(); // call player step

		// call dementors step
		for (int i = 0; i < dementors.size(); i++)
		{
			dementors[i]->control(0);
			dementors[i]->step();
		}

		// entity collision check
		for (size_t i = 0; i < dementors.size(); i++)
		{
			for (size_t j = 1; j < player->getSegments().size(); j++)
				if (player->getSegments().at(j) == dementors[i]->getSegments().at(0)) dementors.erase(dementors.cbegin() + i);

			for (size_t j = 0; j < dementors[i]->getSegments().size(); j++)
				if (player->getSegments().at(0) == dementors[i]->getSegments().at(j)) player->setIsDead(true);

			for (size_t j = 0; j < items.size(); j++)
				if (dementors[i]->getSegments().at(0) == items[j]->getPosition())
					items[j]->on_eat(dementors[i]);
		}
		for (size_t i = 0; i < items.size(); i++)
			if (player->getSegments().at(0) == items[i]->getPosition())
				items[i]->on_eat(player);

		// eaten items check 
		for (size_t i = 0; i < items.size(); i++)
			if (items[i]->getIsEaten())
				items.erase(items.cbegin() + i);
		
		// spawn items
		srand(std::time(0) * 3);
		int spawnRand = (rand() * 4) % 100;
		int spawnChance = 10 * items.size();
		if (spawnRand > spawnChance)
		{
			int spawnTypeRand = (rand() * 5) % 100;
			vector3 spawnPosition;
			bool isUnique = true;
			int it = 0;
			do
			{
				isUnique = true;
				spawnPosition = vector3(((rand() + it) * 6) % 26, 0, ((rand() + it) * 6) % 26);
				for (size_t i = 0; i < items.size(); i++)
					if (spawnPosition == items[i]->getPosition())
					{
						isUnique = false;
						it = i;
						break;
					}
			}
			while (!isUnique);
			
			if (spawnTypeRand < 20) items.push_back(new Orange(-2.5, 0.0, -2.5, 0.2, 0.2, 0.2, spawnPosition));

			else if (spawnTypeRand < 50) items.push_back(new Banana(-2.5, 0.0, -2.5, 0.2, 0.2, 0.2, spawnPosition));

			else items.push_back(new Apple(-2.5, 0.0, -2.5, 0.2, 0.2, 0.2, spawnPosition));
		}

		// player dead check
		if (player->getIsDead()) state = 1;

		if (dementors.size() == 0) state = 2;


		score = (((player->getEnergy() + player->getSegments().size() * 100) * 10) / time);
		if (dementors.size() > 0) score /= dementors.size();
	}

	if ((state> 0) && isStat == false)
	{
		std::ofstream inFile("statistics.txt", std::ios_base::app);
		inFile << time << " " << player->getEnergy() + player->getSegments().size() * 100 << " " << dementors.size() << " " << score << std::endl;
		inFile.close();
		isStat = true;
	}
}
