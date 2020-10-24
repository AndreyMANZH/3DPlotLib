#pragma once
/*
* Функция dataNormalize предназначена для 
* приведения значение data которое входит в диапазон [min;max]
* в диапазон [-1;1]
* результат работы функции data в диапазоне [-1;1]
*/
double dataNormalize(double data, double min, double mid, double max);
/*
* Функция isClose предназначена для сравнения данных
*/
bool isClose(double data1, double data2, double absTolerance = 0.0001);