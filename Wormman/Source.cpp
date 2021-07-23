void Snake::DrawSnake()
{
	for (int i = 0; i < num; i++)
	{
		if (i == 0)
			glColor3f(0.0, 0.7, 1);
		else
			glColor3f(0.0, 0.0, 1);

		//1
		glBegin(GL_QUADS);
		glVertex3f(s[i].x * Scale, s[i].y * Scale, 0);
		glVertex3f((s[i].x + 1) * Scale, s[i].y * Scale, 0);
		glVertex3f((s[i].x + 1) * Scale, (s[i].y + 1) * Scale, 0);
		glVertex3f(s[i].x * Scale, (s[i].y + 1) * Scale, 0);
		glEnd();
		//2
		glBegin(GL_QUADS);
		glVertex3f(s[i].x * Scale, s[i].y * Scale, 2);
		glVertex3f((s[i].x + 1) * Scale, s[i].y * Scale, 2);
		glVertex3f((s[i].x + 1) * Scale, (s[i].y + 1) * Scale, 2);
		glVertex3f(s[i].x * Scale, (s[i].y + 1) * Scale, 2);
		glEnd();
		//3
		glBegin(GL_QUADS);
		glVertex3f((s[i].x + 1) * Scale, s[i].y * Scale, 0);
		glVertex3f(s[i].x * Scale, s[i].y * Scale, 0);
		glVertex3f(s[i].x * Scale, s[i].y * Scale, 2);
		glVertex3f((s[i].x + 1) * Scale, s[i].y * Scale, 2);
		glEnd();
		//4
		glBegin(GL_QUADS);
		glVertex3f(s[i].x * Scale, (s[i].y + 1) * Scale, 0);
		glVertex3f((s[i].x + 1) * Scale, (s[i].y + 1) * Scale, 0);
		glVertex3f((s[i].x + 1) * Scale, (s[i].y + 1) * 2, Scale);
		glVertex3f(s[i].x * Scale, (s[i].y + 1) * Scale, 2);
		glEnd();
		//5
		glBegin(GL_QUADS);
		glVertex3f((s[i].x + 1) * Scale, (s[i].y + 1) * Scale, 0);
		glVertex3f((s[i].x + 1) * Scale, s[i].y * Scale, 0);
		glVertex3f((s[i].x + 1) * Scale, s[i].y * Scale, 2);
		glVertex3f((s[i].x + 1) * Scale, (s[i].y + 1) * Scale, 2);
		glEnd();
		//6
		glBegin(GL_QUADS);
		glVertex3f((s[i].x + 1) * Scale, s[i].y * Scale, 0);
		glVertex3f(s[i].x * Scale, s[i].y * Scale, 0);
		glVertex3f(s[i].x * Scale, s[i].y * Scale, 2);
		glVertex3f(s[i].x * Scale, s[i].y * Scale, 2);
		glEnd();
	}
}

void Snake::Step()
{
	int dir = sceneS.get_dir();
	//move body
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	//move head
	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;

	if (s[0].x < 0) s[0].x = 24;
	if (s[0].x > 24) s[0].x = 0;
	if (s[0].y < 0) s[0].y = 24;
	if (s[0].y > 24) s[0].y = 0;

	for (int i = 0; i < 5; i++)
		if ((s[0].x == apple[i].getX()) && (s[0].y == apple[i].getY()))
		{
			num++; apple[i].New();
		}

	for (int j = 0; j < 5; j++)
		for (int i = 0; i < num; i++)
			if ((apple[j].getX() == s[i].x) && (apple[j].getY() == s[i].y))
				apple[j].New();

	for (int i = 1; i < num; i++)
		if (s[0].x == s[i].x && s[0].y == s[i].y)  num = i;
}