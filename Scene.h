#pragma once

#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include "Axes.h"
#include "PointSeries.h"
#include "LineSeries.h"
#include "SurfaceSeries.h"
#include "TextLabel.h"




/**
 * @brief Класс для создания объекта Scene - сцена.
 * В созданой области отрисовываються все объекты 
 * диаграммы: оси, точки, поверхности, координатные 
 * плоскости, подписки к осям координат 
 */
class Scene
{
private:
	/**
	 * @brief Блок статических переменных для работы с 
	 * 		  системой координат (расчет делений)
	 * 
	 * @param m_max_x максимальное значение оси x
	 * @param m_mid_x среднее значение оси x
	 * @param m_min_x минимальное значение оси x
	 * @param m_step_x шаг по оси x
	 * @param m_max_y максимальное значение оси y
	 * @param m_mid_y среднее значение оси y
	 * @param m_min_y минимальное значение оси y
	 * @param m_step_y шаг по оси y
	 * @param m_max_z максимальное значение оси z
	 * @param m_mid_z среднее значение оси z
	 * @param m_min_z минимальное значение оси z
	 * @param m_step_z шаг по оси z
	 * @param m_axes объект системы координат
	 */
	static double m_max_x;												
	static double m_mid_x;												
	static double m_min_x;												
	static double m_step_x;												

	static double m_max_y;												
	static double m_mid_y;												
	static double m_min_y;												
	static double m_step_y;												

	static double m_max_z;												
	static double m_mid_z;												
	static double m_min_z;												
	static double m_step_z;	
	static Axes* m_axes;												
	/**
	 * @brief Блок переменных для определения размеров рабочей области 
	 *  	  и ее цвета.
	 * 
	 * @param m_width ширина рабочей области
	 * @param m_height высота рабочей области
	 * @param m_red уровень красного цвет рабочей области
	 * @param m_green уровень зеленого цвет рабочей области
	 * @param m_blue уровень синего цвет рабочей области
	 * @param m_alpha уровень прозрачности цвет рабочей области
	 */
	int m_width;															
	int	m_height;															
	float m_red;															
	float m_green;														
	float m_blue;															
	float m_alpha;														
	/**
	 * @brief Блок переменных для определения координат точки находящейся
	 * 		  под курсором.
	 * 
	 * @param m_select_x координата x точки находящейся под курсором
	 * @param m_select_y координата y точки находящейся под курсором
	 * @param m_select_z координата z точки находящейся под курсором
	 * 
	 */
	static double m_select_x;
	static double m_select_y;
	static double m_select_z;			
	/**
	 * @brief Блок переменных для серии элементов.
	 * 
	 * @param m_point_series серия точек
	 * @param m_line_series серия линий
	 * @param m_surface_series серия поверхностей
	 * 
	 */
	static PointSeries m_point_series;										
	static LineSeries m_line_series;										
	static SurfaceSeries m_surface_series;									
	/**
	 * @brief Блок переменных в которых храняться нормализованные точки
	 * 		  необходимые для рисования точек, линий, поверхностей.
	 * @param m_point_series_array указатель на динамический массив точек
	 * @param m_line_series_array указатель на динамический массив точек линий
	 * @param m_surface_series_array указатель на динамический массив точек поверхностей
	 * @param m_surface_arr_size количество точек поверхностей
	 */
	static double* m_point_series_array;									
	static double* m_line_series_array;										
	static double* m_surface_series_array;
	
	static std::size_t m_point_arr_size;
	static std::size_t m_line_arr_size;
	static std::size_t m_surface_arr_size;								
	/**
	 * @brief Статический метод для рисования линий проекций точки на плоскости координат
	 *
	 */
	static void paint_project_line();
	/**
	 * @brief Функция для рисования всех объектов
	 * 
	 */
	static void display_callback();										
	/**
	 * @brief Статический метод для рисования во время изменения размера рабочей области
	 * 
	 * @param width ширина рабочей области
	 * @param height высота рабочей области
	 * 
	 */
	static void reshape_callback(int width, int height);					
	/**
	 * @brief Статический метод для обработки взаимодействия с мышкой
	 * 
	 * @param button id кнопки
	 * @param state вид взаимодействия
	 * @param x координата
	 * @param y координата
	 */
	static void mouse_callback(int button, int state, int x, int y);		
	/**
	 * @brief Статический метод для обработки передвижения мышки (одна из кнопок нажата)
	 * 
	 * @param x координата
	 * @param y координата
	 */
	static void motion_callback(int x, int y);							
	/**
	 * @brief Статический метод для обработки передвижения мышки (одна из не нажата)
	 * 
	 * @param x координата
	 * @param y координата
	 */
	static void passive_motion_func(int x, int y);						
	/**
	 * @brief Статический метод для рисования точек
	 * 
	 */
	static void draw_point_series();										
	/**
	 * @brief Статический метод для рисования линий
	 * 
	 */
	static void draw_line_series();	
	/**
	 * @brief  Статический метод для рисования поверхностей
	 * 
	 */
	static void draw_surface_series();								
	/**
	 * @brief Инициализация OpenGL
	 * 
	 */
	void gl_init();	
	/**
	 * @brief  Статический метод для преобразования 2D области 
	 * 		   в 3D проекцию OpenGL
	 * 
	 * @param x координата x рабочей области
	 * @param y координата у рабочей области
	 * @param ox преобразованная координата x OpenGL
	 * @param oy преобразованная координата y OpenGL
	 * @param oz преобразованная координата z OpenGL
	 */
	static void client_to_opengl(int x, int y, double* ox, double* oy, double* oz);

public:
	/**
	 * @brief Блок статический переменных для работы с камерой и мышью
	 * @param m_sphi вращение вокруг оси z
	 * @param m_stheta вращение вокруг оси x, y
	 */
	static float m_sphi;
	static float m_stheta;
	static float m_sdepth;
	static float m_z_near;
	static float m_z_far;
	static float m_aspect;
	static float m_xcam;
	static float m_ycam;
	static long m_xsize;
	static long m_ysize;
	static int m_down_x;
	static int m_down_y;
	static bool m_left_btn;
	static bool m_middle_btn;
	/**
	 * @brief Конструктор по умолчанию создает объект Scene для отрисовки объектов
	 * 
	 * @param width ширина окна
	 * @param height высота окна
	 */
	Scene(int width, int height);		
	/**
	 * @brief Деструктор для освобождения памяти 
	 * 
	 */
	~Scene();	
	/**
	 * @brief Метод для добавления серии точек
	 * 
	 * @param points_series серия точек
	 */
	void add_points_series(PointSeries& points_series);
	/**
	 * @brief Метод для добавления серии линий
	 * 
	 * @param lines_series серия линий
	 */
	void add_lines_series(LineSeries& lines_series);
	/**
	 * @brief Метод для добавления серии поверхностей
	 * 
	 * @param surfaces_series серия поверхностей
	 */
	void add_surfaces_series(SurfaceSeries* surfaces_series);
	/**
	 * @brief Инициализация библиотеки glut вызывая метод glutInit
	 * 
	 * @param arg количество параметров
	 * @param argv параметры
	 */
	static void scene_glut_init(int arg, char** argv);					
	/**
	 * @brief Статический метод для определения максимального значения для оси x
	 * 
	 * @return double 
	 */
	static double get_max_x();											
	/**
	 * @brief Статический метод для определения минимального значения для оси x
	 * 
	 * @return double 
	 */
	static double get_min_x();											
	/**
	 * @brief Статический метод для определения среднего значения для оси x
	 * 
	 * @return double 
	 */
	static double get_mid_x();											
	/**
	 * @brief Статический метод для определения шага оси x
	 * 
	 * @return double 
	 */
	static double get_step_x();											
	/**
	 * @brief Статический метод присвоения максимального значения для оси x
	 * 
	 * @param max_x присваемое новое значение для m_max_x
	 */
	static void set_max_x(double max_x);									
	/**
	 * @brief Статический метод присвоения минимального значения для оси x
	 * 
	 * @param min_x присваемое новое значение для m_min_x
	 */
	static void set_min_x(double min_x);									
	/**
	 * @brief Статический метод присвоения шага оси x
	 * 
	 * @param step_x присваемое новое значение для m_step_x
	 */
	static void set_step_x(double step_x);								
	/**
	 * @brief Статический метод для определения максимального значения для оси y
	 * 
	 * @return double 
	 */
	static double get_max_y();											
	/**
	 * @brief Статический метод для определения минимального значения для оси y
	 * 
	 * @return double 
	 */
	static double get_min_y();											
	/**
	 * @brief Статический метод для определения среднего значения для оси y
	 * 
	 * @return double 
	 */
	static double get_mid_y();										
	/**
	 * @brief Статический метод для определения шага оси y
	 * 
	 * @return double 
	 */
	static double get_step_y();											
	/**
	 * @brief Статический метод присвоения максимального значения для оси y
	 * 
	 * @param max_y присваемое новое значение для m_max_y
	 */
	static void set_max_y(double max_y);									
	/**
	 * @brief Статический метод присвоения минимального значения для оси y
	 * 
	 * @param min_y присваемое новое значение для m_min_y
	 */
	static void set_min_y(double min_y);									
	/**
	 * @brief Статический метод присвоения шага оси y
	 * 
	 * @param step_y присваемое новое значение для m_step_y
	 */
	static void set_step_y(double step_y);								
	/**
	 * @brief Статический метод для определения максимального значения для оси z
	 * 
	 * @return double 
	 */
	static double get_max_z();	
	/**
	 * @brief Статический метод для определения минимального значения для оси z
	 * 
	 * @return double 
	 */										
	static double get_min_z();	
	/**
	 * @brief Статический метод для определения среднего значения для оси z
	 * 
	 * @return double 
	 */										
	static double get_mid_z();	
	/**
	 * @brief Статический метод для определения шага оси z
	 * 
	 * @return double 
	 */										
	static double get_step_z();											
	/**
	 * @brief Статический метод присвоения максимального значения для оси z
	 * 
	 * @param max_z присваемое новое значение для m_max_z
	 */
	static void set_max_z(double max_z);
	/**
	 * @brief Статический метод присвоения минимального значения для оси z
	 * 
	 * @param min_z присваемое новое значение для m_min_z
	 */									
	static void set_min_z(double min_z);	
	/**
	 * @brief Статический метод присвоения шага оси z
	 * 
	 * @param step_z присваемое новое значение для m_step_z
	 */								
	static void set_step_z(double step_z);									
														

};