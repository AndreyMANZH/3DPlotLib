#pragma once

#include <GL/glut.h>
#include "TextLabel.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "Tools.h"
/**
 * @brief Класс представляет собой 3-х координатную систему, которая позволяет отрисовывать координатные плоскости, линии деления и подписи осей.
 * @param m_x_axis_grid_visible предназначен для определения отображается ли сетка оси x
 * @param m_y_axis_grid_visible предназначен для определения отображается ли сетка оси y
 * @param m_z_axis_grid_visible предназначен для определения отображается ли сетка оси z
 *
 * @param m_xyz_plate_visible предназначен для определения отображается ли координатные плоскости 
 *
 * @param m_x_axis_visible предназначен для определения отображается ли ось x
 * @param m_y_axis_visible предназначен для определения отображается ли ось y
 * @param m_z_axis_visible предназначен для определения отображается ли ось z
 *
 * @param m_x_text_visible предназначен для определени отображаеются ли подписи для каждого деления оси x
 * @param m_y_text_visible предназначен для определени отображаеются ли подписи для каждого деления оси y
 * @param m_z_text_visible предназначен для определени отображаеются ли подписи для каждого деления оси z
 */
class Axes
{
public:
    /**
     * @brief Конструктор по умолчанию устанавливает цвет серый для всех координатных плоскостей, черный для осей и сетки.
	 * Устанавливает видимость для всех объектов
     * 
     */
	Axes();
	/**
     * @brief Деструктор класса Axes без реализации
     * 
     */
	~Axes();

	/**
	 * @brief Метод предназначен для отрисовки всех элементов класса Axes
	 * 
	 */
	void paint_axes() const;			
	/**
	 * @brief Метод предназначен для отрисовки сетки деления для x
	 * 
	 */
	void paint_x_grid() const;
	/**
	 * @brief Метод предназначен для отрисовки сетки деления для y
	 * 
	 */
	void paint_y_grid() const;
	/**
	 * @brief Метод предназначен для отрисовки сетки деления для z
	 * 
	 */
	void paint_z_grid() const;
	/**
	 * @brief Метод предназначен для отрисовки оси деления для x
	 * 
	 */
	void paint_x_axis() const;
	/**
	 * @brief Метод предназначен для отрисовки оси деления для y
	 * 
	 */
	void paint_y_axis() const;
	/**
	 * @brief Метод предназначен для отрисовки оси деления для z
	 * 
	 */
	void paint_z_axis() const;
	/**
	 * @brief Метод предназначен для отрисовки подписи для каждого деления оси x
	 * 
	 */
	void paint_x_axis_text() const;
	/**
	 * @brief Метод предназначен для отрисовки подписи для каждого деления оси y
	 * 
	 */
	void paint_y_axis_text() const;
	/**
	 * @brief Метод предназначен для отрисовки подписи для каждого деления оси z
	 * 
	 */
	void paint_z_axis_text() const;
	/**
	 * @brief Метод предназначен для отрисовки координатных плоскостей
	 * 
	 */
	void paint_xyz_plate() const;
	/**
	 * @brief Метод предназначен для указания будет ли отрисовываться ось x
	 * 
	 */
	void set_visible_x_axis(bool show);
	/**
	 * @brief Метод предназначен для указания будет ли отрисовываться ось y
	 * 
	 */								
	void set_visible_y_axis(bool show);	
	/**
	 * @brief Метод предназначен для указания будет ли отрисовываться ось z
	 * 
	 */							
	void set_visible_z_axis(bool show);							
	/**
	 * @brief Метод предназначен для указания будет ли отрисовываться сетка оси x
	 * 
	 */	
	void set_visible_x_grid(bool show);
	/**
	 * @brief Метод предназначен для указания будет ли отрисовываться сетка оси y
	 * 
	 */						
	void set_visible_y_grid(bool show);
	/**
	 * @brief Метод предназначен для указания будет ли отрисовываться сетка оси z
	 * 
	 */						
	void set_visible_z_grid(bool show);							
	/**
	 * @brief Метод предназначен для указания будет ли отрисовываться координатные плоскости
	 * 
	 */		
	void set_visible_xyz_plate(bool show);						
	/**
	 * @brief Метод предназначен для указания будут ли отрисовываться подписи для каждого деления оси x
	 * 
	 */
	void set_visible_x_axis_text(bool show);
	/**
	 * @brief Метод предназначен для указания будут ли отрисовываться подписи для каждого деления оси y
	 * 
	 */
	void set_visible_y_axis_text(bool show);
	/**
	 * @brief Метод предназначен для указания будут ли отрисовываться подписи для каждого деления оси z
	 * 
	 */
	void set_visible_z_axis_text(bool show);
	/**
	 * @brief Метод предназначен для определения отображается ли ось x
	 * 
	 * @return true ось x отображается
	 * @return false ось x не отображается
	 */
	bool is_x_axis_visible() const;												
	/**
	 * @brief Метод предназначен для определения отображается ли ось y
	 * 
	 * @return true ось y отображается
	 * @return false ось y не отображается
	 */
	bool is_y_axis_visible() const;
	/**
	 * @brief Метод предназначен для определения отображается ли ось z
	 * 
	 * @return true ось z отображается
	 * @return false ось z не отображается
	 */											
	bool is_z_axis_visible() const;												
	/**
	 * @brief Метод предназначен для определения отображается ли сетка оси x
	 * 
	 * @return true сетка оси x отображается
	 * @return false сетка оси x не отображается
	 */														
	bool is_x_grid_visible() const;										
	/**
	 * @brief Метод предназначен для определения отображается ли сетка оси y
	 * 
	 * @return true сетка оси y отображается
	 * @return false сетка оси y не отображается
	 */	
	bool is_y_grid_visible() const;											
	/**
	 * @brief Метод предназначен для определения отображается ли сетка оси z
	 * 
	 * @return true сетка оси z отображается
	 * @return false сетка оси z не отображается
	 */	
	bool is_z_grid_visible() const;										
	/**
	 * @brief Метод предназначен для определения отображаеются ли координатные плоскости
	 * 
	 * @return true координатные плоскости отображается
	 * @return false координатные плоскости не отображается
	 */	
	bool is_xyz_plate_visible() const;									
	/**
	 * @brief Метод предназначен для определения отображаеются ли подписи для каждого деления оси x
	 * 
	 * @return true подписи для каждого деления оси x отображается
	 * @return false подписи для каждого деления оси x не отображается
	 */	
	bool is_x_axis_text_visible() const;	
	/**
	 * @brief Метод предназначен для определения отображаеются ли подписи для каждого деления оси y
	 * 
	 * @return true подписи для каждого деления оси y отображается
	 * @return false подписи для каждого деления оси y не отображается
	 */										
	bool is_y_axis_text_visible() const;										
	/**
	 * @brief Метод предназначен для определения отображаеются ли подписи для каждого деления оси z
	 * 
	 * @return true подписи для каждого деления оси z отображается
	 * @return false подписи для каждого деления оси z не отображается
	 */	
	bool is_z_axis_text_visible() const;	

private:
	bool m_x_axis_grid_visible; 
	bool m_y_axis_grid_visible;
	bool m_z_axis_grid_visible;

	bool m_xyz_plate_visible;

	bool m_x_axis_visible;
	bool m_y_axis_visible;
	bool m_z_axis_visible;

	bool m_x_text_visible;
	bool m_y_text_visible;
	bool m_z_text_visible;
	
};

