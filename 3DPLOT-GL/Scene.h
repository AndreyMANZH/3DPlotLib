#pragma once
#include "PointSeries.h"
#include "Axes.h"
class Scene
{
private:
	struct Color
	{
		Color(float red, float green, float blue, float alpha)
		{
			this->red = red;
			this->green = green;
			this->blue = blue;
			this->alpha = alpha;
		}
	private:
		float red;
		float green;
		float blue;
		float alpha;
	};
	double max;															// ���������� ��� ������������ ������ � �������� (-1...1)
	int width;															// ������ ������� �������
	int	height;															// ������ ������� �������
	float red;															// ������� ���� ������� �������
	float green;														// ������� ���� ������� �������
	float blue;															// ����� ���� ������� �������
	float alpha;														// ����� ����� ������� �������
	
	static PointSeries pointSeries;										// ������ �����
	static Axes* axes;													// ��� ���������
	static void DisplayCallback();										// ��������� ���������
	static void ReshapeCallback(int width, int height);					// ��������� ��������� �� ����� ��������� ������� ������� �������
	static void MouseCallback(int button, int state, int x, int y);		// ��������� ��������� �� ������� ������ ����
	static void MotionCallback(int x, int y);							// ��������� ��������� ��� �����������
	static void DrawPointSeries();

	void GLinit();														// ������������� OpenGL
	
public:
	void push_PointSeries(PointSeries& pointSeries);
	static void scene_glutInit(int arg, char** argv);					// ������������� OpenGL
					
	
	static void showXAxis(bool show);									// ����������� ��������� X
	void showYAxis(bool show);											// ����������� ��������� Y
	void showZAxis(bool show);											// ����������� ��������� Z
	void showXYZPlate(bool state);										// ����������� ��������� XYZ

	static bool isXAxis();												// ������������ �� ��������� X
	static bool isYAxis();												// ������������ �� ��������� Y
	static bool isZAxis();												// ������������ �� ��������� Z
	static bool isshowXYZPlate();										// ������������ �� ��������� XYZ

	Scene(int width, int height);										// ����������� �����
	Scene(int width, int height, Scene::Color colour);					// ����������� ����� 
	~Scene();															// ���������� �����

};