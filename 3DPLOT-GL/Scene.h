#pragma once
#include "PointSeries.h"
#include "Axes.h"
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
	double max;															// Переменная для нормализации данных в диапазон (-1...1)
	int width;															// Ширина рабочей области
	int	height;															// Высота рабочей области
	float red;															// Красный цвет рабочей области
	float green;														// Зеленый цвет рабочей области
	float blue;															// Синий цвет рабочей области
	float alpha;														// Альфа канал рабочей области
	
	static PointSeries pointSeries;										// Список точек
	static Axes* axes;													// Оси координат
	static void DisplayCallback();										// Обработка отрисовки
	static void ReshapeCallback(int width, int height);					// Обработка отрисовки во время изменения размера рабочей области
	static void MouseCallback(int button, int state, int x, int y);		// Обработка отрисовки по нажатию кнопки мыши
	static void MotionCallback(int x, int y);							// Обработка отрисовки при перемещении
	static void DrawPointSeries();

	void GLinit();														// Инициализация OpenGL
	
public:
	void push_PointSeries(PointSeries& pointSeries);
	static void scene_glutInit(int arg, char** argv);					// Инициализация OpenGL
					
	
	static void showXAxis(bool show);									// Отображение плоскости X
	void showYAxis(bool show);											// Отображение плоскости Y
	void showZAxis(bool show);											// Отображение плоскости Z
	void showXYZPlate(bool state);										// Отображение плоскости XYZ

	static bool isXAxis();												// Отображается ли плоскость X
	static bool isYAxis();												// Отображается ли плоскость Y
	static bool isZAxis();												// Отображается ли плоскость Z
	static bool isshowXYZPlate();										// Отображается ли плоскость XYZ

	Scene(int width, int height);										// Конструктор сцены
	Scene(int width, int height, Scene::Color colour);					// Конструктор сцены 
	~Scene();															// Деструктор сцены

};