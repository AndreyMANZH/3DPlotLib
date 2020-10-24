#pragma once

#include "Axes.h"
#include "PointSeries.h"
#include "LineSeries.h"
#include "SurfaceSeries.h"
class Scene
{
private:
	struct Color
	{
		Color(float red, float green, float blue, float alpha)
		{
			this->red = red;
			this->green = green;
			this->blue = blue;
			this->alpha = alpha;
		}
	private:
		float red;
		float green;
		float blue;
		float alpha;
	};

	static 	bool _isXAxis;
	static bool _isYAxis;
	static bool _isZAxis;
	static bool _isshowXYZPlate;

	static double max_x;												// Максимальное значение оси X
	static double mid_x;												// Среднее значение оси X
	static double min_x;												// Минимальное значение оси X
	static double step_x;												// Шаг по оси X

	static double max_y;												// Максимальное значение оси Y
	static double mid_y;												// Среднее значение оси Y
	static double min_y;												// Минимальное значение оси Y
	static double step_y;												// Шаг по оси Y

	static double max_z;												// Максимальное значение оси Z
	static double mid_z;												// Среднее значение оси Z
	static double min_z;												// Минимальное значение оси Z

	int width;															// Ширина рабочей области
	int	height;															// Высота рабочей области
	float red;															// Красный цвет рабочей области
	float green;														// Зеленый цвет рабочей области
	float blue;															// Синий цвет рабочей области
	float alpha;														// Альфа канал рабочей области
	
	static PointSeries pointSeries;										// Список точек
	static LineSeries lineSeries;										// Список линий
	static SurfaceSeries surfaceSeries;									// Список линий

	static Axes* axes;													// Оси координат
	static void DisplayCallback();										// Обработка отрисовки
	static void ReshapeCallback(int width, int height);					// Обработка отрисовки во время изменения размера рабочей области
	static void MouseCallback(int button, int state, int x, int y);		// Обработка отрисовки по нажатию кнопки мыши
	static void MotionCallback(int x, int y);							// Обработка отрисовки при перемещении
	static void DrawPointSeries();										// Отрисовка точек
	static void DrawLineSeries();										// Отрисовка линий
	static void DrawSurfaceSeries();									// Отрисовка поверхностей
	void GLinit();														// Инициализация OpenGL


public:
	void push_PointSeries(PointSeries& pointSeries);
	void push_LineSeries(LineSeries& lineSeries);
	void push_SurfaceSeries(SurfaceSeries& surfaceSeries);
	static void scene_glutInit(int arg, char** argv);					// Инициализация OpenGL
					
	
	static float sphi;
	static float stheta;
	static float sdepth;
	static float zNear;
	static float zFar;
	static float aspect;
	static float xcam;
	static float ycam;
	static long xsize;
	static long ysize;
	static int downX;
	static int downY;
	static bool leftButton;
	static bool middleButton;

	static void showXAxis(bool show);									// Отображение плоскости X
	static void showYAxis(bool show);											// Отображение плоскости Y
	static void showZAxis(bool show);											// Отображение плоскости Z
	static void showXYZPlate(bool state);										// Отображение плоскости XYZ

	static bool isXAxis();												// Отображается ли плоскость X
	static bool isYAxis();												// Отображается ли плоскость Y
	static bool isZAxis();												// Отображается ли плоскость Z
	static bool isshowXYZPlate();										// Отображается ли плоскость XYZ

	static double getMaxX();											// Максимальное значение оси X
	static double getMinX();											// Минимальное значение оси X
	static double getMidX();											// Среднее значение оси X
	static double getStepX();											// Шаг оси X

	static void setMaxX(double max_x);									// Установить максимальное значение оси X
	static void setMinX(double min_x);									// Установить минимальное значение оси X
	static void setStepX(double step_x);								// Установить значение шага оси X

	static double getMaxY();											// Максимальное значение оси Y
	static double getMinY();											// Минимальное значение оси Y
	static double getMidY();											// Среднее значение оси Y
	static double getStepY();											// Шаг оси Y
	
	static void setMaxY(double max_y);									// Установить максимальное значение оси Y
	static void setMinY(double min_y);									// Установить минимальное значение оси Y
	static void setStepY(double step_x);								// Установить значение шага оси Y

	static double getMaxZ();											// Максимальное значение оси Z
	static double getMinZ();											// Минимальное значение оси Z
	static double getMidZ();											// Среднее значение оси Z
	static void setMaxZ(double max_z);									// Установить максимальное значение оси Z
	static void setMinZ(double min_z);									// Установить минимальное значение оси Z

	Scene(int width, int height);										// Конструктор сцены
	Scene(int width, int height, Scene::Color colour);					// Конструктор сцены 
	~Scene();															// Деструктор сцены

};