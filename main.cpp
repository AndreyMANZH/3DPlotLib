#include <windows.h>

#include <iostream>
#include "Scene.h"
#include "Point.h"
#include "Line.h"
#include "PointSeries.h"
#include "LineSeries.h"
#include "SurfaceSeries.h"
#include "Surface.h"
#include <thread>
#include "Tools.h"
#include <random>  



Scene* s;



int main(int arg, char** argv)
{


	setlocale(LC_ALL, "ru");
	std::string lib = "A:\\GIT\\3DPlotLib\\HumidAir.dll";

	HMODULE HumidAir =  LoadLibraryA("A:\\GIT\\3DPlotLib\\HumidAir.dll");
	 
	if (HumidAir)
		std::cout << "Библиотека влажного воздуха загружена" << std::endl;
	Scene::scene_glut_init(arg, argv);
	
	
	
	Scene::set_max_x(90);
	Scene::set_min_x(0);
	Scene::set_step_x(5);

	Scene::set_max_y(6);
	Scene::set_min_y(-2);
	Scene::set_step_y(0.2);

	Scene::set_max_z(1000000);
	Scene::set_min_z(100000);
	Scene::set_step_z(50000);

	std::vector<double> pressure;
	for(std::size_t p = 100000; p < 1000000;)
	{
		pressure.push_back(p);
		p += 1000;
	}

	double R[6] = { 0.1, 0.2, 0.3, 0.6, 0.8, 1.0};
	double d[6] = { 0.01, 0.015, 0.02, 0.025, 0.04, 0.1};
	
	FARPROC addr2 = (GetProcAddress(HumidAir, "Entropy"));
	
	typedef double (*funcPtr2)(double, double, double, char);
	funcPtr2 Entropy = (funcPtr2)addr2;

	FARPROC addr = (GetProcAddress(HumidAir, "Enthalpy"));
	typedef double (*funcPtr)(double, double, double);
	funcPtr Enthalpy = (funcPtr)addr;

	
	Surface* surf = nullptr;
	Surface::SurfaceRow* sr = nullptr;
	double ent = 0.0;
	int point = 0;
	
	SurfaceSeries* s_ser = new SurfaceSeries;
	for (auto _R : R)
	{
		surf = new Surface;
		for (double &p : pressure)
		{
			sr = new Surface::SurfaceRow;
			for (double t = 0; t <= 80; t+=1)
			{
				ent = Entropy(p, t, _R, 'R');
				sr->add_point(new Point(t, ent, p));
				++point;
			}
			surf->add_surface_row(sr);
		}
		s_ser->add_surface(surf);
	}

	for (auto _d : d)
	{
		surf = new Surface;
		for (double &p : pressure)
		{
			sr = new Surface::SurfaceRow;
			for (double t = 0; t <= 80; t+=1)
			{
				ent = Entropy(p, t, _d, 'd');
				sr->add_point(new Point(t, ent, p));
				++point;
			}
			surf->add_surface_row(sr);
		}
		s_ser->add_surface(surf);
	}


	PointSeries* ps = new PointSeries;
	ps->add_point(new Point(30, 0.251, 101325));
	ps->add_point(new Point(331, 0.343, 970230));
	ps->add_point(new Point(750.7, 1.057, 921718));
	ps->add_point(new Point(1200, 1.614, 875632));
	ps->add_point(new Point(756, 1.699, 106400));
	ps->add_point(new Point(30, 1.036, 101080));
	
	LineSeries *ls = new LineSeries;
	ls->add_line(new Line(new Point(30, 0.251, 101325), new Point(331, 0.343, 970230)));
	ls->add_line(new Line(new Point(331, 0.343, 970230), new Point(750.7, 1.057, 921718)));
	ls->add_line(new Line(new Point(750.7, 1.057, 921718), new Point(1200, 1.614, 875632)));
	ls->add_line(new Line(new Point(1200, 1.614, 875632), new Point(756, 1.699, 106400)));
	ls->add_line(new Line(new Point(756, 1.699, 106400), new Point(30, 1.036, 101080)));

	//s->add_lines_series(*ls);
	//s->add_points_series(*ps);
	s->add_surfaces_series(s_ser);
	std::thread t([]
	{
		s = new Scene(500, 500);
	});

	t.join();
	

	return 0;
}