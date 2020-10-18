#include <iostream>
#include "Scene.h"
#include "Point.h"
#include "PointSeries.h"
#include <thread>
Scene* s;

int main(int arg, char** argv)
{
	Scene::scene_glutInit(arg, argv);
	
	
	std::thread t([] {
		s = new Scene(100, 100);	
	});
	PointSeries ps;
	Point p1(125, -500, -1500);
	Point p2(1, 0, -10);
	Point p3(10, -835, -1);
	double x, y, z = 0;

	for (int i = 0; i < 100000; i++)
	{
		x = rand() % 200 - 100;
		y = rand() % 200 - 100;
		z = rand() % 200 - 100;
		Point p(x, y, z);
		ps.push_back(p);
	}

	

	s->push_PointSeries(ps);
	
	std::cout << " MAX " << ps.getMax() << std::endl;
	int in = 0;
	while (true)
	{
		std::cin >> in;
		switch (in)
		{
		case 0:
			s->showXAxis(false);
			break;
		case 1:
			s->showXAxis(true);
			break;
		case 2:
			s->showXYZPlate(false);
			break;
		case 3:
			s->showXYZPlate(true);
			break;
		}
	}
	
	t.join();

	return 0;
}