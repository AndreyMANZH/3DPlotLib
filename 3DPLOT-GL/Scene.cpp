#include "Scene.h"
#include <GL/glut.h>
#include "PointSeries.h"
#include "LineSeries.h"
#include "TextLabel.h"
#include "Tools.h"
#include <iostream>

// Определение статических переменных
Axes* Scene::axes;
PointSeries Scene::pointSeries;
LineSeries Scene::lineSeries;
SurfaceSeries Scene::surfaceSeries;

double Scene::max_x = 1;
double Scene::mid_x = 0;
double Scene::min_x = -1;
double Scene::step_x = 0.1;

double Scene::max_y = 1;
double Scene::mid_y = 0;
double Scene::min_y = -1;
double Scene::step_y = 0.1;

double Scene::max_z = 1;
double Scene::mid_z = 0;
double Scene::min_z = -1;

float Scene::sphi = -215;
float Scene::stheta = 60;
float Scene::sdepth = 5;
float Scene::zNear = 1.0;
float Scene::zFar = 100.0;
float Scene::aspect = 5.0 / 4.0;
float Scene::xcam = 0;
float Scene::ycam = 0;
long Scene::xsize = 0;
long Scene::ysize = 0;
int Scene::downX = 0;
int Scene::downY = 0;
bool Scene::leftButton = false;
bool Scene::middleButton = false;

bool Scene::_isXAxis = true;
bool Scene::_isYAxis = true;
bool Scene::_isZAxis = true;
bool Scene::_isshowXYZPlate = true;

Scene::Scene(int width, int height)
{
	axes = new Axes;
	this->width = width;
	this->height = height;
	this->width = 500;
	this->height = 500;
	this->red = 1;
	this->green = 1;
	this->blue = 1;
	this->alpha = 1;
	
	
	GLinit();
}

Scene::Scene(int width, int height, Scene::Color colour) : Scene(width, height)
{
//
}

Scene::~Scene()
{
	delete axes;
}

void Scene::GLinit()
{
	// режим отображения 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// Размер окна
	glutInitWindowSize(width, height);
	// Создание окна
	glutCreateWindow("3D PLOT");
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// Цвет окна
	glClearColor(red, green, blue, alpha);
	// Смещение
	glPolygonOffset(1, 1);
	// Отключение режима учета граней
	glDisable(GL_CULL_FACE);
	// Сглаживание линий
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// выполнение растеризации примитивов           
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// Установка цвета материала
	glEnable(GL_COLOR_MATERIAL);
	// Свойство материала
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	// Включение освещения
	glEnable(GL_LIGHT0);
	float light_pos[4] = { 0, 1, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	// Обратобка ввод/вывод
	glutDisplayFunc(Scene::DisplayCallback);
	glutReshapeFunc(Scene::ReshapeCallback);
	glutMouseFunc(Scene::MouseCallback);
	glutMotionFunc(Scene::MotionCallback);
	glutMainLoop();
}

void Scene::DisplayCallback()
{
	if (sphi < -360 || sphi > 360)
		sphi = 0;

	if (stheta < -360 || stheta > 360)
		stheta = 0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(64, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -sdepth);
	glRotatef(-stheta, 1.0, 0.0, 0.0);
	glRotatef(sphi, 0.0, 0.0, 1.0);

	// Отображение осей координат и плоскостей
	axes->showXAxis(isXAxis());
	axes->showYAxis(isYAxis());
	axes->showZAxis(isZAxis());
	axes->showXYZPlate(isshowXYZPlate(), sphi, stheta);
	

	DrawPointSeries();
	DrawLineSeries();
	DrawSurfaceSeries();

	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::ReshapeCallback(int width, int height)
{
	xsize = width;
	ysize = height;
	aspect = (float)xsize / (float)ysize;
	glViewport(0, 0, xsize, ysize);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutPostRedisplay();
}
void Scene::MouseCallback(int button, int state, int x, int y)
{
	downX = x; 
	downY = y;
	leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
	middleButton = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));
	glutPostRedisplay();
}
void Scene::MotionCallback(int x, int y)
{
	// Поворот
	if (leftButton) {
		sphi += (float)(x - downX) / 4.0; stheta += (float)(downY - y) / 4.0;
	} 
	// Зум
	if (middleButton) {

		sdepth += (float)(downY - y) / 10.0;
	}

	downX = x;   downY = y;

	glutPostRedisplay();
}
void Scene::scene_glutInit(int arg, char** argv)
{
	glutInit(&arg, argv);
}

void Scene::showXAxis(bool show)
{
	_isXAxis = show;
}

void Scene::showYAxis(bool show)
{
	_isYAxis = show;
}

void Scene::showZAxis(bool show)
{
	_isZAxis = show;
}


bool Scene::isXAxis()
{
	return _isXAxis;
}
bool Scene::isYAxis()
{
	return _isYAxis;
}
bool Scene::isZAxis()
{
	return _isZAxis;
}

void Scene::showXYZPlate(bool state)
{
	_isshowXYZPlate = state;
}

bool Scene::isshowXYZPlate()
{
	return _isshowXYZPlate;
}

void Scene::push_PointSeries(PointSeries& pointSeries)
{
	Scene::pointSeries = pointSeries;
}

void Scene::push_LineSeries(LineSeries& lineSeries)
{
	Scene::lineSeries = lineSeries;
}
void Scene::push_SurfaceSeries(SurfaceSeries& surfaceSeries)
{
	Scene::surfaceSeries = surfaceSeries;
}

void Scene::DrawPointSeries()
{
	if (pointSeries.getSize() > 0)
	{
		glColor3f(0, 1, 0);
		glPointSize(10);
		glBegin(GL_POINTS);
		double x, y, z = 0;
		for (int i = 0; i < pointSeries.getSize(); ++i)
		{
			x = dataNormalize(pointSeries[i].getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
			y = dataNormalize(pointSeries[i].getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
			z = dataNormalize(pointSeries[i].getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());

			glPointSize(3);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void Scene::DrawLineSeries()
{
	if (lineSeries.getSize() > 0)
	{
		glColor3f(0, 0, 0);
		glLineWidth(4);
		glBegin(GL_LINES);
		double x, y, z = 0;
		for (int i = 0; i < lineSeries.getSize(); ++i)
		{
			x = dataNormalize(lineSeries[i].p1.getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
			y = dataNormalize(lineSeries[i].p1.getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
			z = dataNormalize(lineSeries[i].p1.getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
			
			glVertex3f(x, y, z);
			
			x = dataNormalize(lineSeries[i].p2.getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
			y = dataNormalize(lineSeries[i].p2.getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
			z = dataNormalize(lineSeries[i].p2.getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
			
			glVertex3f(x, y, z);
		}
		glEnd();
		glLineWidth(1);
	}
}

void Scene::DrawSurfaceSeries()
{

	double x1, y1, z1 = 0;
	double x2, y2, z2 = 0;
	double x3, y3, z3 = 0;
	double r, g, b = 0;
	//Идем по поверхностям
	for (int i = 0; i < Scene::surfaceSeries.getSize(); ++i)
	{
		glBegin(GL_TRIANGLES);
		// Идем по рядам поверхности i
		for (int j = 0; j < Scene::surfaceSeries[i]->getSize() - 1; ++j)
		{
			
			// Идем по элементам ряда j i-й поверхности
			int r = 0;
		
			for (int k = 0; k < (*Scene::surfaceSeries[i])[j]->size() - 1; )

			{
				switch (r)
				{
				case 0:
					glPointSize(3);
					glColor3f(1, 0, 0);
					x1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x1, y1, z1);
					x2 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k+1).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y2 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k+1).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z2 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k+1).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x2, y2, z2);
					x3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
				
					glVertex3f(x3, y3, z3);
					r = 1;
					break;
				case 1:
					x1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x1, y1, z1);
					x2 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k + 1).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y2 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k + 1).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z2 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k + 1).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x2, y2, z2);
					x3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x3, y3, z3);
					
					r = 0;
					++k;
					break;

				}
				
			}
			
		}
		glEnd();
	}
	glLineWidth(2);
	//Идем по поверхностям
	for (int i = 0; i < Scene::surfaceSeries.getSize(); ++i)
	{
		glBegin(GL_LINES);
		// Идем по рядам поверхности i
		for (int j = 0; j < Scene::surfaceSeries[i]->getSize() - 1; ++j)
		{

			// Идем по элементам ряда j i-й поверхности
			int r = 0;

			for (int k = 0; k < (*Scene::surfaceSeries[i])[j]->size() - 1; )

			{
				switch (r)
				{
				case 0:

					glColor3f(0, 0, 0);
					x1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x1, y1, z1);
					x2 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y2 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z2 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x2, y2, z2);
					x3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());

					glVertex3f(x3, y3, z3);
					r = 1;
					break;
				case 1:
					x1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x1, y1, z1);
					x2 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k + 1).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y2 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k + 1).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z2 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k + 1).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x2, y2, z2);
					x3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
					y3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
					z3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
					glVertex3f(x3, y3, z3);

					r = 0;
					++k;
					break;

				}

			}

		}
		glEnd();
	}
	glLineWidth(1);
}
double Scene::getMaxX()
{
	return Scene::max_x;
}
double Scene::getMinX()
{
	return Scene::min_x;
}
double Scene::getMidX()
{
	return 0.5 * (Scene::getMinX() + Scene::getMaxX());
}
double Scene::getStepX()
{
	return Scene::step_x;
}
void Scene::setMaxX(double max_x)
{
	Scene::max_x = max_x;
}
void Scene::setMinX(double min_x)
{
	Scene::min_x = min_x;
}
void Scene::setStepX(double step_x)
{
	Scene::step_x = step_x;
}


double Scene::getMaxY()
{
	return Scene::max_y;
}
double Scene::getMinY()
{
	return Scene::min_y;
}
double Scene::getMidY()
{
	return 0.5 * (Scene::getMinY() + Scene::getMaxY());
}
void Scene::setMaxY(double max_y)
{
	Scene::max_y = max_y;
}
void Scene::setMinY(double min_y)
{
	Scene::min_y = min_y;
}
void Scene::setStepY(double step_y)
{
	Scene::step_y = step_y;
}
double Scene::getMaxZ()
{
	return Scene::max_z;
}
double Scene::getMinZ()
{
	return Scene::min_z;
}
double Scene::getStepY()
{
	return Scene::step_y;
}

double Scene::getMidZ()
{
	return 0.5 * (Scene::getMinZ() + Scene::getMaxZ());
}
void Scene::setMaxZ(double max_z)
{
	Scene::max_z = max_z;
}
void Scene::setMinZ(double min_z)
{
	Scene::min_z = min_z;
}