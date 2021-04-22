#pragma once

#include "Point.h"
/**
 * @brief Класс для создания базового объекта Line - линия
 * Объект класса Line состоит из следующих параметров 
 * @param m_p1 первая точка линии
 * @param m_p2 вторая точка линии
 **/
class Line
{
private:
    Point *m_p1;
    Point *m_p2;
public:
    /**
     * @brief Конструктор по умолчанию отсутствует для создания линии необходимо использовать конструктор Line(const Point& p1, const Point& p2);
     * 
     */
    Line() = delete;
     /**
     * @brief Конструктор для создания линии проходящей через точки p1 и p2
     * 
     */
    Line(Point* p1, Point* p2);
    /**
     * @brief Деструктор для освобождение памяти
     * 
     */
    ~Line();
    /**
     * @brief Возвращает первую точку линии
     * 
     * @return Point 
     */
    Point* get_first() const;
    /**
     * @brief Возвращает вторую точку линии
     * 
     * @return Point 
     */
    Point* get_second() const;
};