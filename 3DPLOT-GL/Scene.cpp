#include "Scene.h"
#include "PointSeries.h"
#include "LineSeries.h"
#include "TextLabel.h"
#include "Tools.h"
#include <iostream>
#include <GL/glut.h>

// Определение статических переменных
double Scene::selectX = -1000;
double Scene::selectY = -1000;
double Scene::selectZ = -1000;

Axes* Scene::axes = new Axes;
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
double Scene::step_z = 0.1;

float Scene::sphi = -20;
float Scene::stheta = 60;
float Scene::sdepth = 5;
float Scene::zNear = 1;
float Scene::zFar = 100;
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

bool Scene::_isXAxisGrid = true;
bool Scene::_isYAxisGrid = true;
bool Scene::_isZAxisGrid = true;
bool Scene::_isshowXYZPlate = true;
bool Scene::_isXAxisText = true;
bool Scene::_isYAxisText = true;
bool Scene::_isZAxisText = true;

double* Scene::pointSeriesArray;
double* Scene::lineSeriesArray;
double* Scene::surfaceSeriesArray;

int array_size = 0;									// Здесь хранится размер массива (surfaceSeriesArray) для отрисовки поверхностей
Scene::Scene(int width, int height)
{
	this->width = width;
	this->height = height;
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
	//Очистка массива точек
	delete[] pointSeriesArray;
	delete[] lineSeriesArray;
	delete[] surfaceSeriesArray;
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

	// Обратобка ввод/вывод
	glutDisplayFunc(Scene::DisplayCallback);
	glutReshapeFunc(Scene::ReshapeCallback);
	glutMouseFunc(Scene::MouseCallback);
	glutMotionFunc(Scene::MotionCallback);
	//glutPassiveMotionFunc(Scene::PassiveMotionFunc);
	glutMainLoop();
}
void Scene::ClientToOpenGL(int x, int y, double* ox, double* oy, double* oz)
{
	int vp[4];
	double mMatrix[16], pMatrix[16];
	float z;

	glGetIntegerv(GL_VIEWPORT, vp);
	y = vp[3] - y - 1;

	glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, pMatrix);
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(x, y, z, mMatrix, pMatrix, vp, ox, oy, oz);
	
}
void Scene::DisplayCallback()
{
	if (sphi < -360 || sphi > 360)
		sphi = 0;

	if (stheta < -360 || stheta > 360)
		stheta = 0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(64, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -sdepth);
	glRotatef(-stheta, 1.0, 0.0, 0.0);
	glRotatef(sphi, 0.0, 0.0, 1.0);

	

	// Отображение осей координат и плоскостей
	axes->paintAxes();
	DrawPointSeries();
	DrawLineSeries();
	DrawSurfaceSeries();

	if (selectX > -2 && selectY > -2 && selectX > -2)
		DrawProjLine();

	glutSwapBuffers();
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

void Scene::PassiveMotionFunc(int x, int y)
{
	double _x, _y, _z;
	ClientToOpenGL(x, y, &_x, &_y, &_z);
	double x_, y_, z_ = 0;
	if (pointSeries.getSize() > 0)
	{
		
		for (int i = 0; i < pointSeries.getSize(); ++i)
		{

			x_ = dataNormalize(pointSeries[i].getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
			y_ = dataNormalize(pointSeries[i].getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
			z_ = dataNormalize(pointSeries[i].getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());

			// Если нашли совпадение по точке то полностью делаем перерисовку и полностью выходим из функции поиска
			if (isClose(_x, x_, 0.02) && isClose(_y, y_, 0.02) && isClose(_z, z_, 0.02))
			{
				Scene::selectX = x_;
				Scene::selectY = y_;
				Scene::selectZ = z_;
				std::cout << " точка " << "x_ " << x_ << " y_ " << y_ << " z_ " << z_ << std::endl;
				std::cout << " точка " << "x " << pointSeries[i].getX() << " y " << pointSeries[i].getY() << " z " << pointSeries[i].getZ() << std::endl;
				std::cout << " ---------------------------\n";
				glutPostRedisplay();
				return; 
			}
			else
			{
				Scene::selectX = -1000;
				Scene::selectY = -1000;
				Scene::selectZ = -1000;
				glutPostRedisplay();
			}

			
		}
		
	}
	//std::cout << "x_ " << _x << " y_ " << _x << " z_ " << _x << std::endl;
	for (int i = 0; i < Scene::surfaceSeries.getSize(); ++i)
	{
		// Идем по рядам поверхности i
		for (int j = 0; j < Scene::surfaceSeries[i]->getSize(); ++j)
		{
			for (int k = 0; k < (*Scene::surfaceSeries[i])[j]->size(); ++k)
			{
				x_ = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
				y_ = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
				z_ = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
				// Если нашли совпадение по точке то полностью делаем перерисовку и полностью выходим из функции поиска
				if (isClose(_x, x_, 0.02) && isClose(_y, y_, 0.02) && isClose(_z, z_, 0.02))
				{
					Scene::selectX = x_;
					Scene::selectY = y_;
					Scene::selectZ = z_;
					std::cout << "x_ " << (*Scene::surfaceSeries[i])[j]->at(k).getX() << " y_ " << (*Scene::surfaceSeries[i])[j]->at(k).getY() << " z_ " << (*Scene::surfaceSeries[i])[j]->at(k).getZ() << std::endl;
					glutPostRedisplay();
					return;
				}
				else
				{
					Scene::selectX = -1000;
					Scene::selectY = -1000;
					Scene::selectZ = -1000;
				}
			}

		}

	}
}
void Scene::scene_glutInit(int arg, char** argv)
{
	glutInit(&arg, argv);
	
}

void Scene::showXAxis(bool show)
{
	axes->setShowXAxis(show);
}
void Scene::showYAxis(bool show)
{
	axes->setShowYAxis(show);
}
void Scene::showZAxis(bool show)
{
	axes->setShowZAxis(show);
}

void Scene::showXAxisGrid(bool show)
{
	axes->setShowXAxisGrid(show);
}

void Scene::showYAxisGrid(bool show)
{
	axes->setShowYAxisGrid(show);
}

void Scene::showZAxisGrid(bool show)
{
	axes->setShowZAxisGrid(show);
}

bool Scene::isXAxis()
{
	return Scene::_isXAxis;
}
bool Scene::isYAxis()
{
	return Scene::_isYAxis;
}
bool Scene::isZAxis()
{
	return Scene::_isZAxis;
}

bool Scene::isXAxisGrid()
{
	return _isXAxisGrid;
}
bool Scene::isYAxisGrid()
{
	return _isYAxisGrid;
}
bool Scene::isZAxisGrid()
{
	return _isZAxisGrid;
}

void Scene::showXYZPlate(bool state)
{
	axes->setShowXYZAxisPlate(state);
}

bool Scene::isshowXYZPlate()
{
	return _isshowXYZPlate;
}

void Scene::push_PointSeries(PointSeries& pointSeries)
{
	Scene::pointSeries = pointSeries;
	if (Scene::pointSeries.getSize() > 0)
	{	
		// Размер определяется из следующего соображения количество точек * на количество координат
		Scene::pointSeriesArray = new double[Scene::pointSeries.getSize()*3];
		// Переменные для нормализвции
		double x, y, z = 0;
		// Цикл для перевода из структуры PointSeries в которой данные 
		// хранятся как вектор Point в одномерный массив данные в котором именют
		// структуру [x0, y0, z0, x1, y1, z1, x2, y2, z2 ...]
		for (int i = 0, j = 0; i < Scene::pointSeries.getSize(); ++i)
		{	
			// Нормализация данных из pointSeries
			x = dataNormalize(Scene::pointSeries[i].getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
			y = dataNormalize(Scene::pointSeries[i].getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
			z = dataNormalize(Scene::pointSeries[i].getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
			//занесение данные в массив по j-му индексу
			Scene::pointSeriesArray[j+0] = x;
			Scene::pointSeriesArray[j+1] = y;
			Scene::pointSeriesArray[j+2] = z;
			// увеличение на 3 с учетом 3-х координат
			j += 3;
		}

	}
}

void Scene::push_LineSeries(LineSeries& lineSeries)
{
	Scene::lineSeries = lineSeries;
	if (lineSeries.getSize() > 0)
	{
		// Размер определяется из следующего соображения количество линий * на количество точек
		// для одной линии * на количество координат одной точки
		lineSeriesArray = new double[Scene::lineSeries.getSize() * 2 * 3];
		// Переменные для нормализвции
		double x, y, z = 0;
		// Цикл для перевода из структуры PointSeries в которой данные 
		// хранятся как вектор Point в одномерный массив данные в котором именют
		// структуру [x0, y0, z0, x1, y1, z1, x2, y2, z2 ...]
		for (int i = 0, j = 0; i < Scene::lineSeries.getSize(); ++i)
		{
			// Нормализация данных из lineSeries для i-й линии и её первой точки
			x = dataNormalize(Scene::lineSeries[i].p1.getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
			y = dataNormalize(Scene::lineSeries[i].p1.getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
			z = dataNormalize(Scene::lineSeries[i].p1.getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
			//занесение данные в массив по j-му индексу
			Scene::lineSeriesArray[j + 0] = x;
			Scene::lineSeriesArray[j + 1] = y;
			Scene::lineSeriesArray[j + 2] = z;
			// Нормализация данных из lineSeries для i-й линии и её второй точки
			x = dataNormalize(Scene::lineSeries[i].p2.getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
			y = dataNormalize(Scene::lineSeries[i].p2.getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
			z = dataNormalize(Scene::lineSeries[i].p2.getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
			//занесение данные в массив по j-му индексу
			Scene::lineSeriesArray[j + 3] = x;
			Scene::lineSeriesArray[j + 4] = y;
			Scene::lineSeriesArray[j + 5] = z;
			//занесение данные в массив по j-му индексу
			j += 6;
		}
	}
}
void Scene::push_SurfaceSeries(SurfaceSeries& surfaceSeries)
{

	Scene::surfaceSeries = surfaceSeries;
	if (Scene::surfaceSeries.getSize() > 0)
	{
		double x1, y1, z1 = 0;
		double x2, y2, z2 = 0;
		double x3, y3, z3 = 0;
		double r, g, b = 0;
		int fff = 0;
		// Размер массива рассчитывается следующим образом
		// количество поверхностей умножаем на количество рядов
		// в одной поверхности (исходя из z - координаты) за вычетом
		// единицы умножаем на количество точек в одном ряде умножив
		// на два (так как разбивается все на треугольник) и умножить на девять
		// так как на один треугольник требуется 9 координат
		
		// Требует анализа так как при большем количестве
		// возможны задержки на пересчет

		for (int i = 0, l = 0; i < Scene::surfaceSeries.getSize(); ++i)
		{
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
						r = 1;
						break;
					case 1:
						r = 0;
						++k;
						break;
					}
					array_size += 9;
				}
			}
		}

		Scene::surfaceSeriesArray = new double[array_size];

		//Идем по поверхностям
		for (int i = 0, l = 0; i < Scene::surfaceSeries.getSize(); ++i)
		{
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
						x1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
						y1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
						z1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());

						x2 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
						y2 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
						z2 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());

						x3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
						y3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
						z3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
						Scene::surfaceSeriesArray[l + 0] = x1;
						Scene::surfaceSeriesArray[l + 1] = y1;
						Scene::surfaceSeriesArray[l + 2] = z1;
						
						Scene::surfaceSeriesArray[l + 3] = x2;
						Scene::surfaceSeriesArray[l + 4] = y2;
						Scene::surfaceSeriesArray[l + 5] = z2;

						Scene::surfaceSeriesArray[l + 6] = x3;
						Scene::surfaceSeriesArray[l + 7] = y3;
						Scene::surfaceSeriesArray[l + 8] = z3;
						r = 1;
						break;
					case 1:
						x1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
						y1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
						z1 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());

						x2 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k + 1).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
						y2 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k + 1).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
						z2 = dataNormalize((*Scene::surfaceSeries[i])[j]->at(k + 1).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());

						x3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getX(), Scene::getMinX(), Scene::getMidX(), Scene::getMaxX());
						y3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getY(), Scene::getMinY(), Scene::getMidY(), Scene::getMaxY());
						z3 = dataNormalize((*Scene::surfaceSeries[i])[j + 1]->at(k + 1).getZ(), Scene::getMinZ(), Scene::getMidZ(), Scene::getMaxZ());
						
						Scene::surfaceSeriesArray[l + 0] = x1;
						Scene::surfaceSeriesArray[l + 1] = y1;
						Scene::surfaceSeriesArray[l + 2] = z1;

						Scene::surfaceSeriesArray[l + 3] = x2;
						Scene::surfaceSeriesArray[l + 4] = y2;
						Scene::surfaceSeriesArray[l + 5] = z2;

						Scene::surfaceSeriesArray[l + 6] = x3;
						Scene::surfaceSeriesArray[l + 7] = y3;
						Scene::surfaceSeriesArray[l + 8] = z3;

						r = 0;
						++k;
						break;
					}
					// увеличение на 9 с учетом 9-х записаных координат
					l += 9;
				}
			}
		}

	}

}

void Scene::DrawPointSeries()
{
	glColor3f(1, 0, 1);
	glPointSize(10);
	glVertexPointer(3, GL_DOUBLE, 0, Scene::pointSeriesArray);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POINTS, 0, Scene::pointSeries.getSize());
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Scene::DrawLineSeries()
{
	glColor3f(1, 1, 0);
	glVertexPointer(3, GL_DOUBLE, 0, Scene::lineSeriesArray);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_LINES, 0, Scene::lineSeries.getSize()*2);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Scene::DrawSurfaceSeries()
{
	if (array_size != 0)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex3f(1, 1, 1);
		glEnd();
		glPointSize(1);
		float light_pos[4] = { 1, 1, -1, 0.1 };
		//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		GLfloat light1_diffuse[] = { 1, 1, 1 };

		GLfloat light1_position[] = { 0.0, 1.0, 1.0, 1.0 };

		glEnable(GL_LIGHT1);

		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


		glColor3f(0, 1, 1);
		glVertexPointer(3, GL_DOUBLE, 0, Scene::surfaceSeriesArray);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_TRIANGLES, 0, array_size/3);
		glDisableClientState(GL_VERTEX_ARRAY);

		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}
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
double Scene::getStepY()
{
	return Scene::step_y;
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
double Scene::getMidZ()
{
	return 0.5 * (Scene::getMinZ() + Scene::getMaxZ());
}
double Scene::getStepZ()
{
	return Scene::step_z;
}
void Scene::setMaxZ(double max_z)
{
	Scene::max_z = max_z;
}
void Scene::setMinZ(double min_z)
{
	Scene::min_z = min_z;
}
void Scene::setStepZ(double step_z)
{
	Scene::step_z = step_z;
}

void Scene::showXAxisText(bool show)
{
	axes->setShowXAxisText(show);
}
void Scene::showYAxisText(bool show)
{
	axes->setShowYAxisText(show);
}
void Scene::showZAxisText(bool show)
{
	axes->setShowZAxisText(show);
}

bool Scene::isXAxisText()
{
	return Scene::_isXAxisText;
}
bool Scene::isYAxisText()
{
	return Scene::_isYAxisText;
}
bool Scene::isZAxisText()
{
	return Scene::_isZAxisText;
}

void Scene::DrawProjLine()
{
	glColor3f(0, 0, 0);
	glLineWidth(1.5);
	glBegin(GL_LINES);
	double x, y, z;
	
	if ((sin(GRAD(Scene::sphi)) <= -0.15 && (sin(GRAD(Scene::sphi)) >= -1.0)))
		x = -1;
	else
		x = 1;
		
	if ((cos(GRAD(Scene::sphi)) <= 0.1 && (cos(GRAD(Scene::sphi)) >= -1.0)))
		y = -1;
	else
		y = 1;
	if (cos(GRAD(Scene::stheta)) >= -1.0 && cos(GRAD(Scene::stheta)) <= -0.35)
		z = 1;
	else
		z = -1;

	glVertex3f(Scene::selectX, Scene::selectY, Scene::selectZ);
	glVertex3f(Scene::selectX, Scene::selectY, z);

	glVertex3f(Scene::selectX, Scene::selectY, Scene::selectZ);
	glVertex3f(Scene::selectX, y, Scene::selectZ);

	glVertex3f(Scene::selectX, Scene::selectY, Scene::selectZ);
	glVertex3f(x, Scene::selectY, Scene::selectZ);
	glEnd();
	glLineWidth(1);
}