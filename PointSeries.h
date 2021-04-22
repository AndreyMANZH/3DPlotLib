#pragma once
#include "Point.h"
#include "PointSeries.h"
#include <cmath>

#include <vector>
/**
 * @brief Класс для создания объекта PointSeries - серия точек
 * Объект класса PointSeries состоит из следующих параметров 
 * @param m_vector_points указатель на вектор точек 
 */
class PointSeries
{
private:
	std::vector<Point*>* m_vector_points;
public:
	/**
	 * @brief Конструктор по умолчанию создает объект PointSeries с количеством точек равным нулю
	 * 
	 */
	PointSeries();
	/**
	 * @brief Деструктор для освобождение памяти
	 * 
	 */
	~PointSeries();
	/**
	 * @brief Добавление точки в PointSeries
	 * 
	 * @param p добавляемая точка
	 */
	void add_point(Point* p);
	/**
	 * @brief operator[] перегруженный оператор для доступа к точке и работы с ней по индексу
	 * 
	 * @param index индекс
	 * @return Point& точка по индексу 
	 */
	Point* operator[](std::size_t index);

	 /** @brief  get_size() метод для определения количества точек хранящихся в PointSeries
	 * 
	 * @return std::size_t - количество точек в PointSeries
	 */
	std::size_t get_size() const;					
};

