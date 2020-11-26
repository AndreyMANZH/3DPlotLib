#pragma once

#include "Axes.h"
#include "PointSeries.h"
#include "LineSeries.h"
#include "SurfaceSeries.h"
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

	static bool _isXAxis;
	static bool _isYAxis;
	static bool _isZAxis;

	static bool _isXAxisGrid;
	static bool _isYAxisGrid;
	static bool _isZAxisGrid;
	
	static bool _isshowXYZPlate;
	
	static bool _isXAxisText;
	static bool _isYAxisText;
	static bool _isZAxisText;

	static double max_x;												// ������������ �������� ��� X
	static double mid_x;												// ������� �������� ��� X
	static double min_x;												// ����������� �������� ��� X
	static double step_x;												// ��� �� ��� X

	static double max_y;												// ������������ �������� ��� Y
	static double mid_y;												// ������� �������� ��� Y
	static double min_y;												// ����������� �������� ��� Y
	static double step_y;												// ��� �� ��� Y

	static double max_z;												// ������������ �������� ��� Z
	static double mid_z;												// ������� �������� ��� Z
	static double min_z;												// ����������� �������� ��� Z
	static double step_z;												// ��� �� ��� Z

	int width;															// ������ ������� �������
	int	height;															// ������ ������� �������
	float red;															// ������� ���� ������� �������
	float green;														// ������� ���� ������� �������
	float blue;															// ����� ���� ������� �������
	float alpha;														// ����� ����� ������� �������
	//
	static double selectX, selectY, selectZ;							// ������� �������� �����
	static void DrawProjLine();
	//
	static PointSeries pointSeries;										// ������ �����
	static LineSeries lineSeries;										// ������ �����
	static SurfaceSeries surfaceSeries;									// ������ �����

	static double* pointSeriesArray;									// ������ ��������������� ����� ������������ �� pointSeries - ��� ��������� �����
	static double* lineSeriesArray;										// ������ ��������������� ����� ������������ �� lineSeries - ��� ��������� �����
	static double* surfaceSeriesArray;									// ������ ��������������� ����� ������������ �� surfaceSeries - ��� ��������� ������������

	static Axes* axes;													// ��� ���������
	static void DisplayCallback();										// ��������� ���������
	static void ReshapeCallback(int width, int height);					// ��������� ��������� �� ����� ��������� ������� ������� �������
	static void MouseCallback(int button, int state, int x, int y);		// ��������� ��������� �� ������� ������ ����
	static void MotionCallback(int x, int y);							// ��������� ��������� ��� �����������
	static void PassiveMotionFunc(int x, int y);						// ���������� ������� ����� ��������� ������� ��������, �� ������� ���� �� ������.
	static void DrawPointSeries();										// ��������� �����
	static void DrawLineSeries();										// ��������� �����
	static void DrawSurfaceSeries();									// ��������� ������������
	
	void GLinit();														// ������������� OpenGL
	static void ClientToOpenGL(int x, int y, double* ox, double* oy, double* oz);

public:
	void push_PointSeries(PointSeries& pointSeries);
	void push_LineSeries(LineSeries& lineSeries);
	void push_SurfaceSeries(SurfaceSeries& surfaceSeries);
	static void scene_glutInit(int arg, char** argv);					// ������������� OpenGL
					
	
	static float sphi;
	static float stheta;
	static float sdepth;
	static float zNear;
	static float zFar;
	static float aspect;
	static float xcam;
	static float ycam;
	static long xsize;
	static long ysize;
	static int downX;
	static int downY;
	static bool leftButton;
	static bool middleButton;

	static void showXAxis(bool show);									// ����������� ��� X
	static void showYAxis(bool show);									// ����������� ��� Y
	static void showZAxis(bool show);									// ����������� ��� Z

	static void showXAxisGrid(bool show);								// ����������� ��������� X
	static void showYAxisGrid(bool show);								// ����������� ��������� Y
	static void showZAxisGrid(bool show);								// ����������� ��������� Z

	static void showXYZPlate(bool state);								// ����������� ��������� XYZ
	
	static void showXAxisText(bool show);								// ����������� ������� ������� ��� X
	static void showYAxisText(bool show);								// ����������� ������� ������� ��� X
	static void showZAxisText(bool show);								// ����������� ������� ������� ��� X

	static bool isXAxis();												// ������������ �� ��� X
	static bool isYAxis();												// ������������ �� ��� Y
	static bool isZAxis();												// ������������ �� ��� Z

	static bool isXAxisGrid();											// ������������ �� ��������� X
	static bool isYAxisGrid();											// ������������ �� ��������� Y
	static bool isZAxisGrid();											// ������������ �� ��������� Z
	static bool isshowXYZPlate();										// ������������ �� ��������� XYZ
	
	static bool isXAxisText();											// ������������ �� ������� ������� ��� X
	static bool isYAxisText();											// ������������ �� ������� ������� ��� Y
	static bool isZAxisText();											// ������������ �� ������� ������� ��� Z

	static double getMaxX();											// ������������ �������� ��� X
	static double getMinX();											// ����������� �������� ��� X
	static double getMidX();											// ������� �������� ��� X
	static double getStepX();											// ��� ��� X

	static void setMaxX(double max_x);									// ���������� ������������ �������� ��� X
	static void setMinX(double min_x);									// ���������� ����������� �������� ��� X
	static void setStepX(double step_x);								// ���������� �������� ���� ��� X

	static double getMaxY();											// ������������ �������� ��� Y
	static double getMinY();											// ����������� �������� ��� Y
	static double getMidY();											// ������� �������� ��� Y
	static double getStepY();											// ��� ��� Y
	
	static void setMaxY(double max_y);									// ���������� ������������ �������� ��� Y
	static void setMinY(double min_y);									// ���������� ����������� �������� ��� Y
	static void setStepY(double step_x);								// ���������� �������� ���� ��� Y

	static double getMaxZ();											// ������������ �������� ��� Z
	static double getMinZ();											// ����������� �������� ��� Z
	static double getMidZ();											// ������� �������� ��� Z
	static double getStepZ();											// ��� ��� Z
	
	static void setMaxZ(double max_z);									// ���������� ������������ �������� ��� Z
	static void setMinZ(double min_z);									// ���������� ����������� �������� ��� Z
	static void setStepZ(double min_z);									// ���������� �������� ���� ��� Z

	Scene(int width, int height);										// ����������� �����
	Scene(int width, int height, Scene::Color colour);					// ����������� ����� 
	~Scene();															// ���������� �����

};