#pragma once

class Scene
{
private:

	
	int width;
	int	height;
	float red;
	float green;
	float blue;
	float alpha;
	
	void GLinit();
	static void DisplayCallback();
	static void ReshapeCallback(int width, int height);
	static void MouseCallback(int button, int state, int x, int y);
	static void MotionCallback(int x, int y);
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
public:
	static void scene_glutInit(int arg, char** argv);
	
	static void showXAxis(bool show);
	void showYAxis(bool show);
	void showZAxis(bool show);
	void showXYZPlate(bool state);

	static bool isXAxis();
	static bool isYAxis();
	static bool isZAxis();
	static bool isshowXYZPlate();

	Scene(int width, int height);
	Scene(int width, int height, Scene::Color colour);
	~Scene();

};