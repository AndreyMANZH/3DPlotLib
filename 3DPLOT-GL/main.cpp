#include <windows.h>
#include <iostream>
#include "Scene.h"
#include "Point.h"
#include "PointSeries.h"
#include "LineSeries.h"
#include "SurfaceSeries.h"
#include "Surface.h"
#include <thread>
#include "Tools.h"
Scene* s;

void test()
{
	std::cout << "POLL" << std::endl;
	s = new Scene(500, 500);
}
int main(int arg, char** argv)
{
	setlocale(LC_ALL, "ru");
	Scene::scene_glutInit(arg, argv);
	HMODULE HumidAir = LoadLibrary(L"HumidAir.dll");
	if (HumidAir != NULL)
	{

		std::cout << " Библиотека  загружена!" << std::endl;

		FARPROC addr = (GetProcAddress(HumidAir, "Enthalpy"));
		typedef double (*funcPtr)(double, double, double);
		funcPtr Enthalpy = (funcPtr)addr;

		FARPROC addr2 = (GetProcAddress(HumidAir, "Entropy"));
		typedef double (*funcPtr2)(double, double, double, char);
		funcPtr2 Entropy = (funcPtr2)addr2;
		
	
	
	Scene::setMaxX(30);
	Scene::setMinX(-20);
	Scene::setStepX(1);

	Scene::setMaxY(1);
	Scene::setMinY(-1);
	Scene::setStepY(0.1);

	Scene::setMaxZ(700000);
	Scene::setMinZ(50000);
	Scene::setStepZ(50000);
	
	double p[8] = {50000,100000, 200000, 300000, 400000, 500000, 600000, 700000};
	double R[6] = { 0.1, 0.2, 0.3, 0.6, 0.8, 1.0};
	/*Point pt;
	double ent = 0;
	Surface::SurfaceRow* sr;
	SurfaceSeries ss;
	Surface* surf = new Surface;
	int point = 0;
	PointSeries ps;
	for (auto _R : R)
	{
		surf = new Surface;
		for (double _p : p)
		{
			sr = new Surface::SurfaceRow;
			for (double t = -20; t <= 30; t+=10)
			{
				ent = Entropy(_p, t, _R, 'R');
				//std::cout << "p " << _p << " t " << t << " s " << ent << std::endl;
				Point pt(t, ent, _p);
				ps.push_back(pt);
				sr->push_back(pt);
				++point;
			}
			surf->push_back(sr);
		}
		ss.push_back(surf);
	}
	std::cout<< "POINTS COUNT : " << point << std::endl;
	LineSeries ls;
	
	
	Point pt2(-2, -0.2, 200000, 1, 0, 0);
	Point pt3(8, 0.0, 600000, 0, 0, 1);
	Point pt4(3.2, 0.1, 300000, 0, 0, 1);
	Point pt5(6, -0.05, 150000, 0, 0, 1);
	
	Point pt7(12, -1, 300000, 0, 0, 1);
	Point pt8(0, 1, 150000, 0, 0, 1);



	LineSeries::Line l0(pt2, pt3);
	LineSeries::Line l1(pt4, pt5);
	LineSeries::Line l2(pt7, pt8);

	ls.push_back(l0);
	ls.push_back(l1);
	ls.push_back(l2);

	ps.push_back(pt2);
	ps.push_back(pt3);
	ps.push_back(pt4);
	ps.push_back(pt5);
	ps.push_back(pt7);
	ps.push_back(pt8);*/
	
		Surface::SurfaceRow* sr;
		SurfaceSeries ss;
		Surface* surf;
		PointSeries ps;

		Scene::setMaxX(5);
		Scene::setMinX(-5);
		Scene::setStepX(0.5);

		Scene::setMaxY(5);
		Scene::setMinY(-5);
		Scene::setStepY(0.5);

		Scene::setMaxZ(1);
		Scene::setMinZ(-0.5);
		Scene::setStepZ(0.1)
			;

	
	double z = 0;
	surf = new Surface;
	for (double i = -5; i <= 5; i += 0.01)
	{
		sr = new Surface::SurfaceRow;
		for (double j = -5; j <= 5; j += 0.01)
		{
			z = sin((i * i + j * j)) / (i * i + j * j);
			Point pt(i, j, z);
			sr->push_back(pt);
			ps.push_back(pt);
		}
		surf->push_back(sr);
	}
	
	std::thread t(test);
	ss.push_back(surf);
	s->push_PointSeries(ps);
	//s->push_LineSeries(ls);
	s->push_SurfaceSeries(ss);

	std::cout << "-----POINTS COUNT : " << ss.get_points_count() << std::endl;
	t.join();
	
	}
	return 0;
}