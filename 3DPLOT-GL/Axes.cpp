#include "Axes.h"
#include <GL/glut.h>

Axes::Axes()
{
	glColor3f(1.0, 0.0, 0.0);
}

Axes::~Axes()
{
	//
}

void Axes::showXAxis(bool show)
{
	this->XAxis = show;
	if (show)
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (double i = -1; i <= 1; i += 0.2)
		{
			glVertex3f(i, -1, 0);
			glVertex3f(i, 1, 0);
		}
		for (double i = -1; i <= 1; i += 0.2)
		{
			glVertex3f(-1, i, 0);
			glVertex3f(1, i, 0);

		}
		glEnd();
	}
}
void Axes::showYAxis(bool show)
{
	this->YAxis = show;
	if (show)
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (double i = -1; i <= 1; i += 0.2)
		{
			glVertex3f(-1, 0, i);
			glVertex3f(1, 0, i);


		}
		for (double i = -1; i <= 1; i += 0.2)
		{
			glVertex3f(i, 0, 1);
			glVertex3f(i, 0, -1);

		}
		glEnd();
	}
}
void Axes::showZAxis(bool show)
{
	this->ZAxis = show;
	if (show)
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (double i = -1; i <= 1; i += 0.2)
		{
			glVertex3f(0, 1, i);
			glVertex3f(0, -1, i);

		}
		for (double i = -1; i <= 1; i += 0.2)
		{
			glVertex3f(0, i, 1);
			glVertex3f(0, i, -1);

		}
	
		glEnd();
	}
}

void Axes::showXYZPlate(bool state)
{
	if (state)
	{
		glColor3f(0.941, 0.878, 0.808);
		glBegin(GL_QUADS);
		glVertex3f(-1.005, -1.005, -1.005);
		glVertex3f(-1.005, 1.005, -1.005);
		glVertex3f(1.005, 1.005, -1.005);
		glVertex3f(1.005, -1.005, -1.005);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-1.005, -1.005, 1.005);
		glVertex3f(-1.005, 1.005, 1.005);
		glVertex3f(-1.005, 1.005, -1.005);
		glVertex3f(-1.005, -1.005, -1.005);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-1.005, -1.005, 1.005);
		glVertex3f(-1.005, -1.005, -1.005);
		glVertex3f(1.005, -1.005, -1.005);
		glVertex3f(1.005, -1.005, 1.005);
		glEnd();
	}
}

