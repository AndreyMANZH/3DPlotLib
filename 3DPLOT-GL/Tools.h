#pragma once
/*
* ������� dataNormalize ������������� ��� 
* ���������� �������� data ������� ������ � �������� [min;max]
* � �������� [-1;1]
* ��������� ������ ������� data � ��������� [-1;1]
*/
double dataNormalize(double data, double min, double mid, double max);
/*
* ������� isClose ������������� ��� ��������� ������
*/
bool isClose(double data1, double data2, double absTolerance = 0.0001);