#pragma once
#include "Point.h"
#include "Line.h"
#include <vector>
#include <cmath>
/**
 * @brief Класс для создания объекта LineSeries - серия линий
 * Объект класса LineSeries состоит из следующих параметров 
 * @param m_vector_lines указатель на вектор линий 
 */
class LineSeries
{
private:
	std::vector<Line*>* m_vector_lines;
public:
	/**
	 * @brief Конструктор по умолчанию создает объект LineSeries с количеством линий равным нулю
	 * 
	 */
	LineSeries();
	/**
	 * @brief Деструктор для освобождение памяти
	 * 
	 */
	~LineSeries();
	/**
	 * @brief Добавление линии в LineSeries
	 * 
	 * @param l добавляемая линия
	 */
	void add_line(Line  *l);
	/**
	 * @brief Оператор доступа по индексу
	 * 
	 * @param index индекс
	 * @return Line* указатель
	 */
	Line* operator[](const std::size_t index);
	/**
	 * @brief Размер вектора линий
	 * 
	 * @return std::size_t 
	 */
	std::size_t get_size() const;
};

