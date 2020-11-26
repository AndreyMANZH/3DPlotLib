#include "Axes.h"
#include <GL/glut.h>
#include "TextLabel.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "Scene.h"
#include "Tools.h"





Axes::Axes()
{
	glColor3f(0.24, 0.24, 0.24);
	//this->paintAxes();
}

Axes::~Axes()
{
	//
}

void Axes::showXAxisGrid()
{
	glColor3f(0.24, 0.24, 0.24);
	//Переместить в другое место (что бы не считать каждый раз при перерисовке....)
	double normStepX = (Scene::getStepX() * 2) / ((Scene::getMaxX() - Scene::getMinX()));
	double normStepY = (Scene::getStepY() * 2) / ((Scene::getMaxY() - Scene::getMinY()));
	glLineWidth(1);
	glBegin(GL_LINES);
	if (cos(GRAD(Scene::stheta)) >= -1.0 && cos(GRAD(Scene::stheta)) <= -0.35)
	{
		glBegin(GL_LINES);
			for (double i = -1; ; i += normStepX)
			{
				glVertex3f(i, -1, 1);
				glVertex3f(i, 1, 1);
				if (isClose(i, 1.0))
					break;
			}
			for (double i = -1;; i += normStepY)
			{
				glVertex3f(-1, i, 1);
				glVertex3f(1, i, 1);
				if (isClose(i, 1.0))
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
				if (isClose(i, 1.0))
					break;
			}
			for (double i = -1;; i += normStepY)
			{
				glVertex3f(-1, i, -1);
				glVertex3f(1, i, -1);
				if (isClose(i, 1.0))
					break;
			}
		glEnd();	
	}

}
void Axes::showYAxisGrid()
{
	double normStepX = (Scene::getStepX() * 2) / ((Scene::getMaxX() - Scene::getMinX()));
	double normStepZ = (Scene::getStepZ() * 2) / ((Scene::getMaxZ() - Scene::getMinZ()));
	glColor3f(0.24, 0.24, 0.24);
	if ((cos(GRAD(Scene::sphi)) <= 0.1 && (cos(GRAD(Scene::sphi)) >= -1.0)))
	{
		glBegin(GL_LINES);

			for (double i = -1;; i += normStepZ)
			{
				glVertex3f(-1, -1, i);
				glVertex3f(1, -1, i);
				if (isClose(i, 1.0))
					break;
			}
			for (double i = -1;; i += normStepX)
			{
				glVertex3f(i, -1, 1);
				glVertex3f(i, -1, -1);
				if (isClose(i, 1.0))
					break;
			}
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);

			for (double i = -1;; i += normStepZ)
			{
				glVertex3f(-1, 1, i);
				glVertex3f(1, 1, i);
				if (isClose(i, 1.0))
					break;
			}
			for (double i = -1;; i += normStepX)
			{
				glVertex3f(i, 1, 1);
				glVertex3f(i, 1, -1);
				if (isClose(i, 1.0))
					break;
			}
		glEnd();
	}

	

}
void Axes::showZAxisGrid()
{
	double normStepY = (Scene::getStepY() * 2) / ((Scene::getMaxY() - Scene::getMinY()));
	double normStepZ = (Scene::getStepZ() * 2) / ((Scene::getMaxZ() - Scene::getMinZ()));
	if ((sin(GRAD(Scene::sphi)) <= -0.15 && (sin(GRAD(Scene::sphi)) >= -1.0)))
	{
		glBegin(GL_LINES);
			for (double i = -1;; i += normStepZ)
			{
				glVertex3f(-1, 1, i);
				glVertex3f(-1, -1, i);
				if (isClose(i, 1.0))
					break;
			}
			for (double i = -1;; i += normStepY)
			{
				glVertex3f(-1, i, 1);
				glVertex3f(-1, i, -1);
				if (isClose(i, 1.0))
					break;
			}
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);
			for (double i = -1;; i += normStepZ)
			{
				glVertex3f(1, 1, i);
				glVertex3f(1, -1, i);
				if (isClose(i, 1.0))
					break;
			}
			for (double i = -1;; i += normStepY)
			{
				glVertex3f(1, i, 1);
				glVertex3f(1, i, -1);
				if (isClose(i, 1.0))
					break;
			}
		glEnd();
	}
}

void Axes::showXYZPlate()
{
	glColor3f(0.92, 0.92, 0.92);
	if ((sin(GRAD(Scene::sphi)) <= -0.15 && (sin(GRAD(Scene::sphi)) >= -1.0)))
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
	if ((cos(GRAD(Scene::sphi)) <= 0.1 && (cos(GRAD(Scene::sphi)) >= -1.0)))
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
	if (cos(GRAD(Scene::stheta)) >= -1.0 && cos(GRAD(Scene::stheta)) <= -0.35)
	{
		glBegin(GL_QUADS);
			glVertex3f(-1.005, -1.005, 1.005);
			glVertex3f(-1.005, 1.005, 1.005);
			glVertex3f(1.005, 1.005, 1.005);
			glVertex3f(1.005, -1.005, 1.005);
		glEnd();
	}
	else 
	{
		glBegin(GL_QUADS);
			glVertex3f(-1.005, -1.005, -1.005);
			glVertex3f(-1.005, 1.005, -1.005);
			glVertex3f(1.005, 1.005, -1.005);
			glVertex3f(1.005, -1.005, -1.005);
		glEnd();
	}
	
}

void Axes::showXAxisText()
{		
		//Переместить в другое место (что бы не считать каждый раз при перерисовке....)
		double normStepX = (Scene::getStepX() * 2) / ((Scene::getMaxX() - Scene::getMinX()));
		double normStepY = (Scene::getStepY() * 2) / ((Scene::getMaxY() - Scene::getMinY()));
		double z = 0;
		double y = 0;
		double xLabel = Scene::getMinX();

		if (cos(GRAD(Scene::stheta)) >= -1.0 && cos(GRAD(Scene::stheta)) <= -0.35)
			z = 1.0;
		else
			z = -1.0;

		if ((cos(GRAD(Scene::sphi)) <= 0.1 && (cos(GRAD(Scene::sphi)) >= -1.0)))
			y = 1.1;
		else
			y = -1.1;
			
		glColor3f(0.2, 0.2, 0.2);
		for (double i = -1; ; i += normStepX)
		{
			std::stringstream ss;
			ss << round(xLabel, 100);
			TextLabel l((char*)ss.str().c_str(), i, y, z);
			xLabel += Scene::getStepX();
			if (isClose(i, 1.0))
				break;
			
		}
}

void Axes::showYAxisText()
{
		//Переместить в другое место (что бы не считать каждый раз при перерисовке....)
		double normStepY = (Scene::getStepY() * 2) / ((Scene::getMaxY() - Scene::getMinY()));
		double z = 0;
		double x = 0;
		if (cos(GRAD(Scene::stheta)) >= -1.0 && cos(GRAD(Scene::stheta)) <= -0.35)
			z = 1.0;
		else
			z = -1.0;

		if ((sin(GRAD(Scene::sphi)) <= -0.15 && (sin(GRAD(Scene::sphi)) >= -1.0)))
			x = 1.1;
		else
			x = -1.1;

		glColor3f(0.2, 0.2, 0.2);
		double xLabel = Scene::getMinY();
		for (double i = -1; ; i += normStepY)
		{
			std::stringstream ss;
			ss << round(xLabel, 100);
			TextLabel l((char*)ss.str().c_str(), x, i, z);
			xLabel += Scene::getStepY();
			if (isClose(i, 1.0))
				break;

		}
}

void Axes::showZAxisText()
{
		//Переместить в другое место (что бы не считать каждый раз при перерисовке....)
		double normStepZ = (Scene::getStepZ() * 2) / ((Scene::getMaxZ() - Scene::getMinZ()));
		double y = 1.2;
		double x = 0;

		if ((sin(GRAD(Scene::sphi)) <= -0.15 && (sin(GRAD(Scene::sphi)) >= -1.0)))
			x = -1.2;
		else
			x = 1.2;

		glColor3f(0.2, 0.2, 0.2);
		double xLabel = Scene::getMinZ();
		for (double i = -1; ; i += normStepZ)
		{
			std::stringstream ss;
			ss << round(xLabel, 100);
			TextLabel l((char*)ss.str().c_str(), x, y, i);
			xLabel += Scene::getStepZ();
			if (isClose(i, 1.0))
				break;

		}
}
void Axes::setShowXAxis(bool show)
{
	this->XAxis = show;
}
void Axes::setShowYAxis(bool show)
{
	this->YAxis = show;
}
void Axes::setShowZAxis(bool show)
{
	this->ZAxis = show;
}

void Axes::setShowXAxisGrid(bool show)
{
	this->XAxisGrid = show;
}
void Axes::setShowYAxisGrid(bool show)
{
	this->YAxisGrid = show;
}
void Axes::setShowZAxisGrid(bool show)
{
	this->ZAxisGrid = show;
}
void Axes::setShowXYZAxisPlate(bool show)
{
	this->XYZPlate = show;
}

void Axes::setShowXAxisText(bool show)
{
	this->XAxisText = show;
}
void Axes::setShowYAxisText(bool show)
{
	this->YAxisText = show;
}
void Axes::setShowZAxisText(bool show)
{
	this->ZAxisText = show;
}

void Axes::showXAxis()
{
	glColor3f(0.24, 0.24, 0.24);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glEnd();
	glLineWidth(1);
}
void Axes::showYAxis()
{
	glColor3f(0.24, 0.24, 0.24);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glEnd();
	glLineWidth(1);
}
void Axes::showZAxis()
{
	glColor3f(0.24, 0.24, 0.24);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glEnd();
	glLineWidth(1);
}
bool Axes::isXAxis()
{
	return this->XAxis;
}
bool Axes::isYAxis()
{
	return this->YAxis;
}
bool Axes::isZAxis()
{
	return this->ZAxis;
}

bool Axes::isXAxisGrid()
{
	return this->XAxisGrid;
}
bool Axes::isYAxisGrid()
{
	return this->YAxisGrid;
}
bool Axes::isZAxisGrid()
{
	return this->ZAxisGrid;
}
bool Axes::isshowXYZPlate()
{
	return this->XYZPlate;
}

bool Axes::isXAxisText()
{
	return this->XAxisText;
}
bool Axes::isYAxisText()
{
	return this->YAxisText;
}
bool Axes::isZAxisText()
{
	return this->ZAxisText;
}
void Axes::paintAxes()
{
	if (isXAxis())
		showXAxis();

	if (isYAxis())
		showYAxis();

	if (isZAxis())
		showZAxis();

	if (isXAxisGrid())
		showXAxisGrid();
	
	if (isYAxisGrid())
		showYAxisGrid();

	if (isZAxisGrid())
		showZAxisGrid();

	if (isshowXYZPlate())
		showXYZPlate();

	if (isXAxisText())
		showXAxisText();
	
	if (isYAxisText())
		showYAxisText();

	if (isZAxisText())
		showZAxisText();


}