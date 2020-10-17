#include "Scene.h"
#include <GL/glut.h>
#include "Axes.h"


static float sphi = -155, stheta = 60;
static float sdepth = 5;
static float zNear = 1.0, zFar = 100.0;
static float aspect = 5.0 / 4.0;
static float xcam = 0, ycam = 0;
static long xsize, ysize;
static int downX, downY;
static bool leftButton = false, middleButton = false;

	static 	bool _isXAxis;
	static bool _isYAxis;
	static bool _isZAxis = true;
	static bool _isshowXYZPlate = true;

Axes* axes;
Scene::Scene(int width, int height)
{
	this->width = width;
	this->height = height;
	this->width = 500;
	this->height = 500;
	this->red = 1;
	this->green = 1;
	this->blue = 1;
	this->alpha = 1;
	axes = new Axes;
	
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
	axes->showXYZPlate(isshowXYZPlate());
	


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