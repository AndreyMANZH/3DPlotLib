#pragma once
/*
* Нормализация данных в придел [-1; 1]
* data - значение которое подвергается нормализации
* min - минимальное знаение для диапазона в котором находится data
* mid - среднее значение  для диапазона в котором находится data
* max - максимальное значение  для диапазона в котором находится data
*/
#define GRAD(X) X*3.14159265/180

double dataNormalize(double data, double min, double mid, double max);
/*
* Функция isClose предназначена для сравнения данных
*/
template <typename T>
bool isClose(T data1, T data2, double absTolerance=0.0001)
{
	return abs(data1 - data2) <= absTolerance;
}
/*
* Функция round предназначена для округления данных
* data - значение которое подвергается округлению
* rest - остаток после точки
*/
double round(double data, int rest);

/*
* Вектор нормаль к поверхности треугольника
*/
void norm_vector(double A[3], double B[3], double C[3], double N[3]);