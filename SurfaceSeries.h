#pragma once
#include <vector>
#include "Surface.h"
/**
 * @brief Класс для создания объекта SurfaceSeries - серия поверхностей
 * Объект класса SurfaceSeries состоит из следующих параметров 
 * @param m_vector_surfaces указатель на вектор поверхностей 
 * @param m_points_count суммарное количество точек всех поверхностей
 * @param NORMALIZED_POINTS_ARRAY список нормализованных точек
 */
class SurfaceSeries
{
public:
	/**
	 * @brief Конструктор по умолчанию создает объект SurfaceSeries с количеством поверхностей равным нулю
	 * 
	 */
	SurfaceSeries();
	/**
	 * @brief Деструктор для освобождение памяти
	 * 
	 */
	~SurfaceSeries();
	/**
	 * @brief Добавление поверхности в SurfaceSeries
	 * 
	 * @param s добавляемая поверхность
	 */
	void add_surface(Surface* s);
	/**
	 * @brief 
	 * 
	 * @param index 
	 * @return Surface* 
	 */
	Surface* operator[](int index);
	/**
	 * @brief Метод для определения количества поверхностей
	 * 
	 * @return std::size_t  
	 */
	std::size_t get_size();							
	/**
	 * @brief Метод для определения суммарного количества точек поверхностей
	 * 
	 * @return std::size_t 
	 */
	std::size_t get_points_count();
private:
	std::vector<Surface*>* m_vector_surfaces;
	int m_points_count = 0;						
	//double* NORMALIZED_POINTS_ARRAY;
	
};

