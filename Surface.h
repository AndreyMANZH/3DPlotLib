#pragma once

#include <vector>
#include "Point.h"
/**
 * @brief Класс для создания базового объекта Surface - поверхность
 * Объект класса Surface состоит из следующих параметров 
 * @param m_vector_surface указатель на вектор каждый элемент которого, является указателем на вектор из SurfaceRow
 * @param m_point_count суммарное количество точек поверхности земли
 * @param SurfaceRow служебный объект представляющий из себя один ряд точек поверхности
 * пример:
 * 			....
 * 			....
 * 			....
 * 			Поверхность состоит из 3 рядов каждый из которых, состоит из 4 точек
 */
class Surface
{
public:
	class SurfaceRow;
	/**
	 * @brief Конструктор по умолчанию создает объект поверхность которая не содержит точек
	 * 
	 */
	Surface();
	/**
	 * @brief Деструктор для освобождения памяти 
	 * 
	 */
	~Surface();
	/**
	 * @brief метод для добавления ряда точек для последующего ее построения
	 * 
	 * @param row указатель на класс SurfaceRow - ряд точек
	 */
	void add_surface_row(Surface::SurfaceRow* row);
	/**
	 * @brief Перегруженый оператор для обращения по индексу к ряду точек поверхности (к указателю на класс SurfaceRow)
	 * 
	 * @param index индекс по которому получаем необходимый элемент
	 * @return SurfaceRow* 
	 */
	Surface::SurfaceRow* operator[](const std::size_t index);
	/**
	 * @brief Метод для определения количества рядов поверхности т.е. сколько элементов указателей класса SurfaceRow
	 * 
	 * @return std::size_t 
	 */
	std::size_t get_size() const;		
	/**
	 * @brief Метод для определения суммарного количества точек 
	 * 
	 * @return std::size_t 
	 */
	std::size_t get_points_count() const;
	/**
	 * @brief служебный объект представляющий из себя один ряд точек поверхности
	 * Объект класса SurfaceRow состоит из следующих параметров 
	 * m_vector_row указатель на вектор элементов класса Point
	 */
	class SurfaceRow
	{
		public:
			std::vector<Point*>* m_vector_row;
			/**
			 * @brief Конструктор по умолчанию создает объект ряд поверхности который не содержит точек
			 * 
			 */
			SurfaceRow();
			/**
			 * @brief Деструктор для освобождение памяти 
			 * 
			 */
			~SurfaceRow();
			/**
			 * @brief метод для добавления точек в ряд поверхности
			 * 
			 * @param point указатель на класс Point
			 */
			void add_point(Point* point);
			/**
			 * @brief Количество точек в ряде поверхности
			 * 
			 * @return std::size_t 
			 */
			std::size_t get_size() const;							
			/**
			 * @brief Перегруженый оператор для обращения по индексу к точке ряда поверхности (к класcу Point)
			 * 
			 * @param index индекс по которому получаем необходимый элемент
			 * @return Point&
			 */
			Point* operator[](std::size_t index);
	};
private:

	std::vector<SurfaceRow*>* m_vector_surface;
	std::size_t m_point_count;								
};

