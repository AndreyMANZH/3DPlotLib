#pragma once


#include <GL/GLUT.h>
/**
 * @brief Класс предназначен для вывода текстовой информации в области построения трехмерной диаграммы 
 * @param line текстовая строка С-стиль (указатель на char)
 * @param x координата
 * @param y координата
 * @param z координата
 * 
 */
class TextLabel
{
public:
	/**
	 * @brief Конструктор по умолчанию отсутствует
	 * 
	 */
	TextLabel() = delete;
	/**
	 * @brief Конструктор для создания класса TextLabel
	 * 
	 * @param line текстовая строка С-стиль (указатель на char) 
	 * @param x координата
	 * @param y координата 
	 * @param z координата
	 */
	TextLabel(char* line, double x, double y, double z);
private:
	char *m_line;
};

