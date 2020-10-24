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
		std::cout << "Entropy "  << Entropy(100000, 12, 0.4, 'R') << std::endl;
	
	
	Scene::setMaxX(12);
	Scene::setMinX(-5);
	Scene::setStepX(1);

	Scene::setMaxY(0.2);
	Scene::setMinY(-0.7);
	Scene::setStepY(0.1);

	Scene::setMaxZ(1000000);
	Scene::setMinZ(100000);

	
	double p[5] = {100000, 200000, 500000, 800000, 1000000};
	double R[5] = { 0.1, 0.2, 0.3, 0.4, 1.0};
	Point pt;
	double ent = 0;
	Surface::SurfaceRow* sr;
	SurfaceSeries ss;
	Surface* surf;
	for (auto _R : R)
	{
		surf = new Surface;
		for (double _p : p)
		{
			sr = new Surface::SurfaceRow;
			for (int t = -5; t <= 12; t++)
			{
				ent = Entropy(_p, t, _R, 'R');
				std::cout << "ENT " << ent << std::endl;
				Point pt(t, ent, _p);
				sr->push_back(pt);
			}
			surf->push_back(sr);
		}
		ss.push_back(surf);
	}

	PointSeries ps;
	Point pt1(1, 0.1, 100000);

	ps.push_back(pt1);


	Scene::showXAxis(true);
	Scene::showYAxis(true);
	Scene::showZAxis(true);
	Scene::showXYZPlate(true);
	std::thread t([] {
		s = new Scene(100, 100);	
	});
	
	s->push_PointSeries(ps);
	s->push_SurfaceSeries(ss);
	t.join();
	}
	return 0;
}