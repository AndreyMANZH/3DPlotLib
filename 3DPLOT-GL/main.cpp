#include <iostream>
#include "Scene.h"
#include <thread>
Scene* s;

int main(int arg, char** argv)
{
	Scene::scene_glutInit(arg, argv);
	
	
	std::thread t([] {
		s = new Scene(100, 100);
	});
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