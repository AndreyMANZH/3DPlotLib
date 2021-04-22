#pragma once
/**
 * @brief Класс для создания базового объекта Point - точки
 * Объект класса Point состоит из следующих параметров 
 * @param m_x координата x
 * @param m_y координата y
 * @param m_z координата z
 *
 * @param m_r красный цвет
 * @param m_g зеленый цвет
 * @param m_b синий цвет
 * 
 */
class Point
{

private:
	double m_x;
	double m_y;
	double m_z;

	double m_r;
	double m_g;
	double m_b;
public:
	/**
	 * @brief Конструктор по умолчанию создает точку с координатами (x=0, y=0, z=0) и цветом (r=0, g=0, b=0) 
	 * 
	 */
	Point();
	/**
	 * @brief Конструктор копирования создает точку с координатами (x=p.x, y=p.y, z=p.z) и цветом (r=p.r, g=p.g, b=p.b) 
	 * 
	 * @param p Объект класса Point, поля которого копируются  
	 */
	Point(const Point& p);
	/**
	 * @brief Конструктор  создает точку с координатами (x, y, z) и цветом (r, g, b)
	 * @param x координата
	 * @param y координата
	 * @param z координата
	 * @param r цвет красный: default = 0
	 * @param g цвет зеленый: default = 0
	 * @param b цвет синий: default = 0
	 */
	Point(double x, double y, double z, double r = 0.0, double g  = 0.0, double b = 0.0);
	/**
	 * @brief Конструктор 
	 * 
	 * @param p 
	 */
	Point(Point* p);
	/**
	 * @brief Деструктор класса Point без реализации
	 * 
	 */
	~Point(); 
	/**
	 * @brief Возвращает значение координаты x
	 * 
	 * @return double 
	 */
	double get_x() const;
	/**
	 * @brief Возвращает значение координаты y
	 * 
	 * @return double 
	 */
	double get_y() const;
	/**
	 * @brief Возвращает значение координаты z
	 * 
	 * @return double 
	 */
	double get_z() const;

	/**
	 * @brief Возвращает уровень красного цвета координаты принято от 0 до 1
	 * 
	 * @return double 
	 */
	double get_r() const;
	/**
	 * @brief Возвращает уровень зеленого цвета координаты принято от 0 до 1
	 * 
	 * @return double 
	 */
	double get_g() const;
	/**
	 * @brief Возвращает уровень синего цвета координаты принято от 0 до 1
	 * 
	 * @return double 
	 */
	double get_b() const;

	/**
	 * @brief функция для присвоения новой координаты x
	 * 
	 * @param x новое значение для m_x
	 */
	void set_x(double x);
	/**
	 * @brief функция для присвоения новой координаты y
	 * 
	 * @param y новое значение для m_y
	 */
	void set_y(double y);
	/**
	 * @brief функция для присвоения новой координаты z
	 * 
	 * @param z новое значение для m_z
	 */
	void set_z(double z);

};

