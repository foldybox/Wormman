// Scene.h

#ifndef Scene_h
#define Scene_h

#include <vector>
#include <ctime>
#include "Utils.h"
#include "Level.h"
#include "Dementor.h"
#include "Player.h"
#include "Apple.h"
#include "Banana.h"
#include "Orange.h"



class Scene
{
	Level* level;
	Player* player;
	std::vector<Dementor*> dementors;
	std::vector<Item*> items;

	int button;           // кнопка миші (-1 - не натиснута, 0 - ліва, 2 - права)
	float angleX, angleY; // поточний кут повороту сцени 
	float mouseX, mouseY; // поточні координати
	float width, height;
	float distZ;
	int state;
	int time;
	int score;
	bool isStat;

public:
	Scene();
	~Scene();
	void on_paint(void);
	void on_size(int width, int height);
	void on_mouse(int button, int state, int x, int y);
	void on_motion(int x, int y);
	void on_special(int key, int x, int y);
	void on_timer(int value);

	void start();
	void step(int value);
};

#endif

