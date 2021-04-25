#pragma once
#include <cmath>
#include "Point.h"
#include <GL/glut.h>

/**
 * @brief Пространство имён для работы с математическими функциями
 * 
 */
namespace math_tools{
	/**
	* @brief Функция предназначена для нормализации данных в интервал [-1; 1]
	* @param data - значение которое подвергается нормализации
	* @param min - минимальное знаение для диапазона в котором находится data
	* @param mid - среднее значение  для диапазона в котором находится data
	* @param max - максимальное значение  для диапазона в котором находится data
	* */
	double data_normalize(double data, double min, double mid, double max);

	/**
	* @brief Функция is_close предназначена для сравнения данных
	* @param a  значение для сравнения
	* @param b  значение для сравнения
	* @param  abs_tolerance  0.0001 - минимальное расхождение можду параметром  a и  b (default : a - b <= 0.0001)
	*/

	template <typename T>
	bool is_close(T a, T b, double abs_tolerance=0.0001);
	
	/**
	 * @brief Функция для перевода градусы в радианты
	 * 
	 */
	double grad_to_rad(double grad);
	/**
	* @brief Функция round предназначена для округления данных
	* @param data значение которое подвергается округлению
	* @param rest количество знаков после запятой (default : 100 => 1.5555 = 1.56)
	*/
	double round(double data, int rest = 100);
}

/**
 * @brief Пространство имён для работы с графическими функциями
 * 
 */
namespace paint_tools
{
	/**
	 * @brief Функция paint_line предназначена рисования линии в пространстве OpenGL
	 * 
	 * @param p1 первая точка линии
	 * @param p2 вторая точка линии 
	 * @param line_w толщина линии default: 1
	 */
	void paint_line(Point &&p1, Point &&p2, double line_w = 1);
	/**
	 * @brief Функция paint_square предназначена рисования четырехугольника в пространстве OpenGL 
	 * 
	 * @param p1 первая точка 
	 * @param p2 вторая точка 
	 * @param p3 третья точкаа 
	 * @param p4 четвертая точка 
	 */
	void paint_square(Point &&p1, Point &&p2, Point &&p3, Point &&p4);
}

template <typename T>
bool math_tools::is_close(T a, T b, double abs_tolerance)
{
    return std::abs(a - b) <= abs_tolerance;
}
