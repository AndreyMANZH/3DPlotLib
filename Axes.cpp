#include "Axes.h"

#include "Scene.h"
	// Константные выражения для максимальных и минимальных углов поворота осей (для перескакивания координатных плоскостей, текста, осей)
	constexpr double MIN_THETA = -1.0;
	constexpr double MAX_THETA = -0.35;
	constexpr double MIN_PHI = -1.0;
	constexpr double MAX_PHI = -0.15;
Axes::Axes() :

	m_x_axis_grid_visible(true), m_y_axis_grid_visible(true),
	m_z_axis_grid_visible(true), m_xyz_plate_visible(true),
	m_x_axis_visible(true), 	 m_y_axis_visible(true),
	m_z_axis_visible(true), 	 m_x_text_visible(true),
	m_y_text_visible(true),		 m_z_text_visible(true)

{
	glColor3f(0.24, 0.24, 0.24);
}

Axes::~Axes()
{ }

void Axes::paint_x_grid() const
{
	glColor3f(0.24, 0.24, 0.24);
	//Переместить в другое место (что бы не считать каждый раз при перерисовке....)
	double norm_x_step = (Scene::get_step_x() * 2.0) / ((Scene::get_max_x() - Scene::get_min_x()));
	double norm_y_step = (Scene::get_step_y() * 2.0) / ((Scene::get_max_y() - Scene::get_min_y()));
	glLineWidth(1);
	glBegin(GL_LINES);
	if (cos(math_tools::grad_to_rad(Scene::m_stheta)) >= MIN_THETA && cos(math_tools::grad_to_rad(Scene::m_stheta)) <= MAX_THETA)
	{
			for (double i = -1.0; ; i += norm_x_step)
			{
				paint_tools::paint_line(Point(i, -1.0, 1.0), Point(i, 1.0, 1.0));
				if (math_tools::is_close(i, 1.0))
					break;
			}
			for (double i = -1.0;; i += norm_y_step)
			{
				paint_tools::paint_line(Point(-1.0, i, 1.0), Point(1.0, i, 1.0));
				if (math_tools::is_close(i, 1.0))
					break;
			}
	}
	else
	{
			for (double i = -1.0; ; i += norm_x_step)
			{
				paint_tools::paint_line(Point(i, -1.0, -1.0), Point(i, 1.0, -1.0));
				if (math_tools::is_close(i, 1.0))
					break;
			}
			for (double i = -1.0;; i += norm_y_step)
			{
				paint_tools::paint_line(Point(-1.0, i, -1.0), Point(1.0, i, -1.0));
				if (math_tools::is_close(i, 1.0))
					break;
			}
	}

}
void Axes::paint_y_grid() const
{
	double norm_x_step = (Scene::get_step_x() * 2) / ((Scene::get_max_x() - Scene::get_min_x()));
	double norm_z_step = (Scene::get_step_z() * 2) / ((Scene::get_max_z() - Scene::get_min_z()));
	glColor3f(0.24, 0.24, 0.24);
	if ((cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 0.1 && (cos(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0)))
	{
			for (double i = -1.0;; i += norm_z_step)
			{
				paint_tools::paint_line(Point(-1.0, -1.0, i), Point(1.0, -1.0, i));
				if (math_tools::is_close(i, 1.0))
					break;
			}
			for (double i = -1;; i += norm_x_step)
			{
				paint_tools::paint_line(Point(i, -1.0, 1.0), Point(i, -1.0, -1.0));
				if (math_tools::is_close(i, 1.0))
					break;
			}
	}
	else
	{
			for (double i = -1;; i += norm_z_step)
			{
				paint_tools::paint_line(Point(-1.0, 1.0, i), Point(1.0, 1.0, i));
				if (math_tools::is_close(i, 1.0))
					break;
			}
			for (double i = -1;; i += norm_x_step)
			{
				paint_tools::paint_line(Point(i, 1.0, 1.0), Point(i, 1.0, -1.0));
				if (math_tools::is_close(i, 1.0))
					break;
			}
	}
}
void Axes::paint_z_grid() const
{
	double norm_y_step = (Scene::get_step_y() * 2.0) / ((Scene::get_max_y() - Scene::get_min_y()));
	double norm_z_step = (Scene::get_step_z() * 2.0) / ((Scene::get_max_z() - Scene::get_min_z()));
	if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) <= MAX_PHI && (sin(math_tools::grad_to_rad(Scene::m_sphi)) >= MIN_PHI)))
	{
			for (double i = -1;; i += norm_z_step)
			{
				paint_tools::paint_line(Point(-1.0, 1.0, i), Point(-1.0, -1.0, i));
				if (math_tools::is_close(i, 1.0))
					break;
			}
			for (double i = -1.0;; i += norm_y_step)
			{
				paint_tools::paint_line(Point(-1.0, i, 1.0), Point(-1.0, i, -1.0));
				if (math_tools::is_close(i, 1.0))
					break;
			}
	}
	else
	{
			for (double i = -1.0;; i += norm_z_step)
			{
				paint_tools::paint_line(Point(1.0, 1.0, i), Point(1.0, -1.0, i));
				if (math_tools::is_close(i, 1.0))
					break;
			}
			for (double i = -1.0;; i += norm_y_step)
			{
				paint_tools::paint_line(Point(1.0, i, 1.0), Point(1.0, i, -1.0));
				if (math_tools::is_close(i, 1.0))
					break;
			}
	}
}

void Axes::paint_xyz_plate() const
{
	if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) <= MAX_PHI && (sin(math_tools::grad_to_rad(Scene::m_sphi)) >= MIN_PHI)))
	{
		paint_tools::paint_square(Point(-1.005, -1.005, 1.005),
								  Point(-1.005, 1.005, 1.005), 
								  Point(-1.005, 1.005, -1.005), 
								  Point(-1.005, -1.005, -1.005));
	}else
	{
		paint_tools::paint_square(Point(1.005, -1.005, 1.005),
								  Point(1.005, 1.005, 1.005), 
								  Point(1.005, 1.005, -1.005), 
								  Point(1.005, -1.005, -1.005));
	}
	if (cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 0.1 && cos(math_tools::grad_to_rad(Scene::m_sphi)) >= MIN_PHI)
	{
		paint_tools::paint_square(Point(1.005, -1.005, 1.005),
								  Point(-1.005, -1.005, 1.005), 
								  Point(-1.005, -1.005, -1.005), 
								  Point(1.005, -1.005, -1.005));
	}
	else
	{
		paint_tools::paint_square(Point(1.005, 1.005, 1.005),
								  Point(-1.005, 1.005, 1.005), 
								  Point(-1.005, 1.005, -1.005), 
								  Point(1.005, 1.005, -1.005));
	}
	if (cos(math_tools::grad_to_rad(Scene::m_stheta)) >= MIN_THETA && cos(math_tools::grad_to_rad(Scene::m_stheta)) <= MAX_THETA)
	{
		paint_tools::paint_square(Point(-1.005, -1.005, 1.005),
								  Point(-1.005, 1.005, 1.005), 
								  Point(1.005, 1.005, 1.005), 
								  Point(1.005, -1.005, 1.005));
	}
	else 
	{
		paint_tools::paint_square(Point(-1.005, -1.005, -1.005),
								  Point(-1.005, 1.005, -1.005), 
								  Point(1.005, 1.005, -1.005), 
								  Point(1.005, -1.005, -1.005));
	}
	
}

void Axes::paint_x_axis_text() const
{		
		double norm_x_step = (Scene::get_step_x() * 2.0) / ((Scene::get_max_x() - Scene::get_min_x()));
		double z = 0;
		double y = 0;
		double x_label = Scene::get_min_x();

		if (cos(math_tools::grad_to_rad(Scene::m_stheta)) >= MIN_THETA && cos(math_tools::grad_to_rad(Scene::m_stheta)) <= MAX_THETA)
			z = 1.0;
		else
			z = -1.0;

		if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0 && sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0) && cos(math_tools::grad_to_rad(Scene::m_sphi)) > 0.1)
		{
			y = -1.1;
		}
		else
		{
			y = 1.1;
		}
			
		glColor3f(0.2, 0.2, 0.2);

		// интермал промежуточных значений
		int intermed_val_count = 1;
		// Счетчик промежуточных значений
		int intermed_val = intermed_val_count;
		double i = -1.0;
		do
		{
			if (intermed_val == intermed_val_count)
			{
				std::stringstream ss;
				ss << math_tools::round(x_label, 100);
				TextLabel l((char*)ss.str().c_str(), i, y, z);
				intermed_val = 0;
			}
			x_label += Scene::get_step_x();
			++intermed_val;
			if (math_tools::is_close(i, 1.0))
				break;
			i += norm_x_step;
		}while(true);
}

void Axes::paint_y_axis_text() const
{
		double norm_y_step = (Scene::get_step_y() * 2.0) / ((Scene::get_max_y() - Scene::get_min_y()));
		double z = 0;
		double x = 0;
		double y_label = Scene::get_min_y();
		
		if (cos(math_tools::grad_to_rad(Scene::m_stheta)) >= -MIN_THETA && cos(math_tools::grad_to_rad(Scene::m_stheta)) <= -MAX_THETA)
			z = 1.0;
		else
			z = -1.0;

		if ((cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0 && cos(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0) && sin(math_tools::grad_to_rad(Scene::m_sphi)) <= -0.15)
		{
			x = 1.1;
		}
		else
		{
			x = -1.1;
		}

		glColor3f(0.2, 0.2, 0.2);
		// интермал промежуточных значений
		int intermed_val_count = 5;
		// Счетчик промежуточных значений
		int intermed_val = intermed_val_count;
		double i = -1.0;
		do
		{
			if (intermed_val == intermed_val_count)
			{
				std::stringstream ss;
				ss << math_tools::round(y_label, 100);
				TextLabel l((char*)ss.str().c_str(), x, i, z);
				intermed_val = 0;
			}
			y_label += Scene::get_step_y();
			++intermed_val;
			if (math_tools::is_close(i, 1.0))
				break;
			i += norm_y_step;
		}while(true);
}

void Axes::paint_z_axis_text() const
{
		double norm_z_step = (Scene::get_step_z() * 2.0) / ((Scene::get_max_z() - Scene::get_min_z()));
		double y = 0.0;
		double x = 0.0;

		if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) <= -0.15 && sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0) && (cos(math_tools::grad_to_rad(Scene::m_sphi)) >= 0.1 && cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0))
		{	
			x = -1.2;
			y = -1.2;
		}
		if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -0.15 && sin(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0) && (cos(math_tools::grad_to_rad(Scene::m_sphi)) >= 0.1 && cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0))
		{
			x = -1.2;
			y =  1.2;
		}
		
		if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -0.15 && sin(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0) && (cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 0.1 && cos(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0))
		{
			x = 1.2;
			y = 1.2;

		}
		if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) <= -0.15 && sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0) && (cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 0.1 && cos(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0))
		{
			x =  1.2;
			y = -1.2;
		}

		glColor3f(0.2, 0.2, 0.2);
		double z_label = Scene::get_min_z();
		// интермал промежуточных значений
		int intermed_val_count = 1;
		// Счетчик промежуточных значений
		int intermed_val = intermed_val_count;
		double i = -1.0;
		do
		{
			if (intermed_val == intermed_val_count)
			{
				std::stringstream ss;
				ss << math_tools::round(z_label, 100);
				TextLabel l((char*)ss.str().c_str(), x, y, i);
				z_label += Scene::get_step_z();
				intermed_val = 0;
			}
			++intermed_val;
			if (math_tools::is_close(i, 1.0))
				break;
			i += norm_z_step;
		}while(true);
}


void Axes::paint_x_axis() const
{
	if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0 && sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0) && cos(math_tools::grad_to_rad(Scene::m_sphi)) > 0.1)
	{
		paint_tools::paint_line(Point(-1.0, -1.0, -1.0), Point(1.0, -1.0, -1.0), 3);
	}
	else
	{
		paint_tools::paint_line(Point(-1.0, 1.0, -1.0), Point(1.0, 1.0, -1.0), 3);
	}
}
void Axes::paint_y_axis() const
{
	if ((cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0 && cos(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0) && sin(math_tools::grad_to_rad(Scene::m_sphi)) <= -0.15)
	{
		paint_tools::paint_line(Point(1.0, -1.0, -1.0), Point(1.0, 1.0, -1.0), 3.0);
	}
	else
	{
		paint_tools::paint_line(Point(-1.0, -1.0, -1.0), Point(-1.0, 1.0, -1.0), 3);
	}
			
}
void Axes::paint_z_axis() const
{
	if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) <= -0.15 && sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0) && (cos(math_tools::grad_to_rad(Scene::m_sphi)) >= 0.1 && cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0))
	{	
		paint_tools::paint_line(Point(-1.0, -1.0, 1.0), Point(-1.0, -1.0, -1.0), 3.0);
	}
	if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -0.15 && sin(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0) && (cos(math_tools::grad_to_rad(Scene::m_sphi)) >= 0.1 && cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0))
	{
		paint_tools::paint_line(Point(-1.0, 1.0, 1.0), Point(-1.0, 1.0, -1.0), 3.0);
	}
	
	if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -0.15 && sin(math_tools::grad_to_rad(Scene::m_sphi)) <= 1.0) && (cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 0.1 && cos(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0))
	{
		paint_tools::paint_line(Point(1.0, 1.0, 1.0), Point(1.0, 1.0, -1.0), 3.0);
	}
	if ((sin(math_tools::grad_to_rad(Scene::m_sphi)) <= -0.15 && sin(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0) && (cos(math_tools::grad_to_rad(Scene::m_sphi)) <= 0.1 && cos(math_tools::grad_to_rad(Scene::m_sphi)) >= -1.0))
	{
		paint_tools::paint_line(Point(1.0, -1.0, 1.0), Point(1.0, -1.0, -1.0), 3);
	}
}

void Axes::set_visible_x_axis(bool show)
{
	m_x_axis_visible = show;
}
void Axes::set_visible_y_axis(bool show)
{
	m_y_axis_visible = show;
}
void Axes::set_visible_z_axis(bool show)
{
	m_z_axis_visible = show;
}

void Axes::set_visible_x_grid(bool show)
{
	m_x_axis_grid_visible = show;
}
void Axes::set_visible_y_grid(bool show)
{
	m_y_axis_grid_visible = show;
}
void Axes::set_visible_z_grid(bool show)
{
	m_z_axis_grid_visible = show;
}
void Axes::set_visible_xyz_plate(bool show)
{
	m_xyz_plate_visible = show;
}

void Axes::set_visible_x_axis_text(bool show)
{
	m_x_text_visible = show;
}
void Axes::set_visible_y_axis_text(bool show)
{
	m_y_text_visible = show;
}
void Axes::set_visible_z_axis_text(bool show)
{
	m_z_text_visible = show;
}

bool Axes::is_x_axis_visible() const
{
	return m_x_axis_visible;
}
bool Axes::is_y_axis_visible() const
{
	return m_y_axis_visible;
}
bool Axes::is_z_axis_visible() const
{
	return m_z_axis_visible;
}

bool Axes::is_x_grid_visible() const
{
	return m_x_axis_grid_visible;
}
bool Axes::is_y_grid_visible() const
{
	return m_y_axis_grid_visible;
}
bool Axes::is_z_grid_visible() const
{
	return m_x_axis_grid_visible;
}
bool Axes::is_xyz_plate_visible() const
{
	return m_xyz_plate_visible;
}

bool Axes::is_x_axis_text_visible() const
{
	return m_x_text_visible;
}
bool Axes::is_y_axis_text_visible() const
{
	return m_y_text_visible;
}
bool Axes::is_z_axis_text_visible() const
{
	return m_z_text_visible;
}
void Axes::paint_axes() const
{
	if (is_x_axis_visible())
		paint_x_axis();

	if (is_y_axis_visible())
		paint_y_axis();

	if (is_z_axis_visible())
		paint_z_axis();

	if (is_x_grid_visible())
		paint_x_grid();
	
	if (is_y_grid_visible())
		paint_y_grid();

	if (is_z_grid_visible())
		paint_z_grid();

	if (is_xyz_plate_visible())
		paint_xyz_plate();

	if (is_x_axis_text_visible())
		paint_x_axis_text();
	
	if (is_y_axis_text_visible())
		paint_y_axis_text();

	if (is_z_axis_text_visible())
		paint_z_axis_text();
}