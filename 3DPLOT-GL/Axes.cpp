#include "Axes.h"
#include <GL/glut.h>
#include "TextLabel.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "Scene.h"
#include "Tools.h"

#define GRAD(X) X*3.14159265/180


Axes::Axes()
{
	glColor3f(0.24, 0.24, 0.24);
	
}

Axes::~Axes()
{
	//
}

void Axes::showXAxis(bool show)
{
	glColor3f(0.24, 0.24, 0.24);
	this->XAxis = show;
	//Переместить в другое место (что бы не считать каждый раз при перерисовке....)
	double normStepX = (Scene::getStepX() * 2) / ((Scene::getMaxX() - Scene::getMinX()));
	double normStepY = (Scene::getStepY() * 2) / ((Scene::getMaxY() - Scene::getMinY()));

	if (show)
	{	
		
		glColor3f(0.24, 0.24, 0.24);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex3f(-1, -1, -1);
		glVertex3f(-1, 1, -1);
		glEnd();
		std::stringstream ss;
		int xLabel = Scene::getMinX();
		
		for (double i = -1;  ; i += normStepX)
		{
			std::stringstream ss;
			ss << xLabel;
			TextLabel l((char*)ss.str().c_str(), i, 1.1, -1);
			xLabel += Scene::getStepX();
			if (isClose(i, 1))
				break;
		}
		glLineWidth(1);
		glBegin(GL_LINES);
		if (cos(GRAD(Scene::stheta)) >= -1.0 && cos(GRAD(Scene::stheta)) <= 0.2)
		{
			glBegin(GL_LINES);
			for (double i = -1; ; i += normStepX)
			{
				glVertex3f(i, -1, 1);
				glVertex3f(i, 1, 1);
				if (isClose(i, 1))
					break;
			}
			for (double i = -1;; i += normStepY)
			{
				glVertex3f(-1, i, 1);
				glVertex3f(1, i, 1);
				if (isClose(i, 1))
					break;
			}
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			for (double i = -1; ; i += normStepX)
			{
				glVertex3f(i, -1, -1);
				glVertex3f(i, 1, -1);
				if (isClose(i, 1))
					break;
			}
			for (double i = -1;; i += normStepY)
			{
				glVertex3f(-1, i, -1);
				glVertex3f(1, i, -1);
				if (isClose(i, 1))
					break;
			}
			glEnd();
		}
	}
}
void Axes::showYAxis(bool show)
{
	this->YAxis = show;
	if (show)
	{
		glColor3f(0.24, 0.24, 0.24);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex3f(1, 1, -1);
		glVertex3f(-1, 1, -1);
		glEnd();

		glLineWidth(1);
		
		
		glColor3f(0.24, 0.24, 0.24);
		if ((cos(GRAD(Scene::sphi)) <= 0.1 && (cos(GRAD(Scene::sphi)) >= -1.0)))
		{
			glBegin(GL_LINES);

			for (double i = -1; i <= 1; i += 0.2)
			{
				glVertex3f(-1, -1, i);
				glVertex3f(1, -1, i);
			}
			for (double i = -1; i <= 1; i += 0.2)
			{
				glVertex3f(i, -1, 1);
				glVertex3f(i, -1, -1);

			}
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);

			for (double i = -1; i <= 1; i += 0.2)
			{
				glVertex3f(-1, 1, i);
				glVertex3f(1, 1, i);
			}
			for (double i = -1; i <= 1; i += 0.2)
			{
				glVertex3f(i, 1, 1);
				glVertex3f(i, 1, -1);

			}
			glEnd();
		}

	
	}
}
void Axes::showZAxis(bool show)
{
	this->ZAxis = show;
	if (show)
	{
		glColor3f(0.24, 0.24, 0.24);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex3f(1, 1, -1);
		glVertex3f(1, 1, 1);
		glEnd();
		glLineWidth(1);
		if ((sin(GRAD(Scene::sphi)) <= -0.15 && (sin(GRAD(Scene::sphi)) >= -1.0)))
		{
			glBegin(GL_LINES);
			for (double i = -1; i <= 1; i += 0.2)
			{
				glVertex3f(-1, 1, i);
				glVertex3f(-1, -1, i);
			}
			for (double i = -1; i <= 1; i += 0.2)
			{
				glVertex3f(-1, i, 1);
				glVertex3f(-1, i, -1);
			}
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			for (double i = -1; i <= 1; i += 0.2)
			{
				glVertex3f(1, 1, i);
				glVertex3f(1, -1, i);
			}
			for (double i = -1; i <= 1; i += 0.2)
			{
				glVertex3f(1, i, 1);
				glVertex3f(1, i, -1);
			}
			glEnd();
		}

	
	}
}

void Axes::showXYZPlate(bool state, float& sphi, float& stheta)
{
	glColor3f(0.92, 0.92, 0.92);
	if (state)
	{
		if ((sin(GRAD(sphi)) <= -0.15 && (sin(GRAD(sphi)) >= -1.0)))
		{
			glBegin(GL_QUADS);
			glVertex3f(-1.005, -1.005, 1.005);
			glVertex3f(-1.005, 1.005, 1.005);
			glVertex3f(-1.005, 1.005, -1.005);
			glVertex3f(-1.005, -1.005, -1.005);
			glEnd();
		}else
		{
			glBegin(GL_QUADS);
			glVertex3f(1.005, -1.005, 1.005);
			glVertex3f(1.005, 1.005, 1.005);
			glVertex3f(1.005, 1.005, -1.005);
			glVertex3f(1.005, -1.005, -1.005);
			glEnd();
		}
		if ((cos(GRAD(sphi)) <= 0.1 && (cos(GRAD(sphi)) >= -1.0)))
		{
			glBegin(GL_QUADS);
			glVertex3f(1.005, -1.005, 1.005);
			glVertex3f(-1.005, -1.005, 1.005);
			glVertex3f(-1.005, -1.005, -1.005);
			glVertex3f(1.005, -1.005, -1.005);
			glEnd();
		}
		else
		{
			glBegin(GL_QUADS);
			glVertex3f(1.005, 1.005, 1.005);
			glVertex3f(-1.005, 1.005, 1.005);
			glVertex3f(-1.005, 1.005, -1.005);
			glVertex3f(1.005, 1.005, -1.005);
			glEnd();
		}

		if (cos(GRAD(stheta)) >= -1.0 && cos(GRAD(stheta)) <= 0.2)
		{
			glBegin(GL_QUADS);
			glVertex3f(-1.005, -1.005, 1.005);
			glVertex3f(-1.005, 1.005, 1.005);
			glVertex3f(1.005, 1.005, 1.005);
			glVertex3f(1.005, -1.005, 1.005);
			glEnd();
		}
		else{
		
	
		glBegin(GL_QUADS);
		glVertex3f(-1.005, -1.005, -1.005);
		glVertex3f(-1.005, 1.005, -1.005);
		glVertex3f(1.005, 1.005, -1.005);
		glVertex3f(1.005, -1.005, -1.005);
		glEnd();

		}

		std::cout << " sphi "  << cos(GRAD(sphi)) << std::endl;
	}
}

