
#include "Scene.h"

#include "Tools.h"


/**
 * @brief Блок определения статических переменных
 * 
 */
double Scene::m_select_x = -1000;
double Scene::m_select_y = -1000;
double Scene::m_select_z = -1000;

Axes* Scene::m_axes = new Axes;
PointSeries Scene::m_point_series;
LineSeries Scene::m_line_series;
SurfaceSeries Scene::m_surface_series;

double Scene::m_max_x = 1.0;
double Scene::m_mid_x = 0.0;
double Scene::m_min_x = -1.0;
double Scene::m_step_x = 0.1;

double Scene::m_max_y = 1.0;
double Scene::m_mid_y = 0.0;
double Scene::m_min_y = -1.0;
double Scene::m_step_y = 0.1;

double Scene::m_max_z = 1.0;
double Scene::m_mid_z = 0.0;
double Scene::m_min_z = -1.0;
double Scene::m_step_z = 0.1;

float Scene::m_sphi = -20.0;
float Scene::m_stheta = 60.0;
float Scene::m_sdepth = 5.0;
float Scene::m_z_near = 1.0;
float Scene::m_z_far = 100.0;
float Scene::m_aspect = 5.0 / 4.0;
float Scene::m_xcam = 0.0;
float Scene::m_ycam = 0.0;
long Scene::m_xsize = 0.0;
long Scene::m_ysize = 0.0;
int Scene::m_down_x = 0.0;
int Scene::m_down_y = 0.0;
bool Scene::m_left_btn = false;
bool Scene::m_middle_btn = false;
/**
 * @brief Блок инициализации динамических массивов для точек, линий и поверхностей
 * 
 */
double* Scene::m_point_series_array = nullptr;
double* Scene::m_line_series_array = nullptr;
double* Scene::m_surface_series_array = nullptr;

/**
 * @brief Блок инициализации размеров динамических массивов для точек, линий и поверхностей
 *  
 */
std::size_t Scene::m_point_arr_size = 0;
std::size_t Scene::m_line_arr_size = 0;
std::size_t Scene::m_surface_arr_size = 0;





Scene::Scene(int width, int height):
	m_width(width), m_height(height), m_red(1),
	m_green(1), m_blue(1), m_alpha(1)
{
	gl_init();

}


Scene::~Scene()
{
	delete m_axes;

	delete[] m_point_series_array;
	delete[] m_line_series_array;
	delete[] m_surface_series_array;
}

void Scene::gl_init()
{
	// режим отображения 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// Размер окна
	glutInitWindowSize(m_width, m_height);
	// Создание окна
	glutCreateWindow("3D PLOT");
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// Цвет окна
	glClearColor(m_red, m_green, m_blue, m_alpha);
	// Смещение
	glPolygonOffset(1, 1);
	// Отключение режима учета граней
	glDisable(GL_CULL_FACE);
	// Сглаживание линий
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// выполнение растеризации примитивов           
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// Установка цвета материала
	glEnable(GL_COLOR_MATERIAL);
	// Свойство материала
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	// Обратобка ввод/вывод
	glutDisplayFunc(Scene::display_callback);
	glutReshapeFunc(Scene::reshape_callback);
	glutMouseFunc(Scene::mouse_callback);
	glutMotionFunc(Scene::motion_callback);
	glutPassiveMotionFunc(Scene::passive_motion_func);
	glutMainLoop();
}
void Scene::client_to_opengl(int x, int y, double* ox, double* oy, double* oz)
{
	int vp[4];
	double mMatrix[16], pMatrix[16];
	float z;

	glGetIntegerv(GL_VIEWPORT, vp);
	y = vp[3] - y - 1;

	glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, pMatrix);
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(x, y, z, mMatrix, pMatrix, vp, ox, oy, oz);
	
}
void Scene::display_callback()
{
	if (m_sphi < -360 || m_sphi > 360)
		m_sphi = 0;

	if (m_stheta < -360 || m_stheta > 360)
		m_stheta = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(64, m_aspect, m_z_near, m_z_far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -m_sdepth);
	glRotatef(-m_stheta, 1.0, 0.0, 0.0);
	glRotatef(m_sphi, 0.0, 0.0, 1.0);

	m_axes->paint_axes();
	
	draw_point_series();
	draw_line_series();
	draw_surface_series();

	if (m_select_x > -2 && m_select_y > -2 && m_select_z > -2)
		paint_project_line();

	glutSwapBuffers();
}

void Scene::reshape_callback(int width, int height)
{
	m_xsize = width;
	m_ysize = height;
	m_aspect = static_cast<float>(m_xsize) / static_cast<float>(m_ysize);
	glViewport(0, 0, m_xsize, m_ysize);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutPostRedisplay();
}

void Scene::mouse_callback(int button, int state, int x, int y)
{
	m_down_x = x; 
	m_down_y = y;
	
	m_left_btn = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
	m_middle_btn = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));

	glutPostRedisplay();
}
void Scene::motion_callback(int x, int y)
{
	// Поворот оси
	if (m_left_btn) 
	{
		m_sphi += static_cast<float>(x - m_down_x) / 4.0;
		m_stheta += static_cast<float>(m_down_y - y) / 4.0;
	} 
	// Приближение
	if (m_middle_btn) {

		m_sdepth += static_cast<float>(m_down_y - y) / 10.0;
	}

	m_down_x = x;
	m_down_y = y;

	glutPostRedisplay();
}

void Scene::passive_motion_func(int x, int y)
{
	double temp_x, temp_y, temp_z;
	client_to_opengl(x, y, &temp_x, &temp_y, &temp_z);
	double temp_sel_x = 0.0;
	double temp_sel_y = 0.0;
	double temp_sel_z = 0.0;
	if (m_point_arr_size> 0)
	{
		std::size_t m_point_s = m_point_arr_size * 3;
		for (std::size_t i = 0; i < m_point_s; ++i)
		{
			temp_sel_x = m_point_series_array[i];
			temp_sel_y = m_point_series_array[i + 1];
			temp_sel_z = m_point_series_array[i + 2];
			// Если нашли совпадение по точке то полностью делаем перерисовку и полностью выходим из функции поиска
			if (math_tools::is_close(temp_x, temp_sel_x, 0.02) && math_tools::is_close(temp_y, temp_sel_y, 0.02) && math_tools::is_close(temp_z, temp_sel_z, 0.02))
			{
				Scene::m_select_x = temp_sel_x;
				Scene::m_select_y = temp_sel_y;
				Scene::m_select_z = temp_sel_z;
				glutPostRedisplay();
				return; 
			}
			else
			{
				Scene::m_select_x = -1000;
				Scene::m_select_y = -1000;
				Scene::m_select_z = -1000;
				glutPostRedisplay();
			}

		
		}
		
	}

	if (m_surface_arr_size> 0)
	{
		for (std::size_t i = 0; i < m_surface_arr_size; ++i)
		{
			temp_sel_x = m_surface_series_array[i];
			temp_sel_y = m_surface_series_array[i + 1];
			temp_sel_z = m_surface_series_array[i + 2];
			// Если нашли совпадение по точке то полностью делаем перерисовку и полностью выходим из функции поиска
			if (math_tools::is_close(temp_x, temp_sel_x, 0.02) && math_tools::is_close(temp_y, temp_sel_y, 0.02) && math_tools::is_close(temp_z, temp_sel_z, 0.02))
			{
				Scene::m_select_x = temp_sel_x;
				Scene::m_select_y = temp_sel_y;
				Scene::m_select_z = temp_sel_z;
				glutPostRedisplay();
				return; 
			}
			else
			{
				Scene::m_select_x = -1000;
				Scene::m_select_y = -1000;
				Scene::m_select_z = -1000;
				glutPostRedisplay();
			}

		
		}
		
	}
}
void Scene::scene_glut_init(int arg, char** argv)
{
	glutInit(&arg, argv);	
}

void Scene::add_points_series(PointSeries& points_series)
{
	if (points_series.get_size() > 0)
	{	
		m_point_arr_size = points_series.get_size();
		// Размер определяется из следующего соображения количество точек * на количество координат
		Scene::m_point_series_array = new double[m_point_arr_size*3];
		// Переменные для нормализвции
		double x, y, z = 0;
		// Цикл для перевода из структуры PointSeries в которой данные 
		// хранятся как вектор Point в одномерный массив данные в котором именют
		// структуру [x0, y0, z0, x1, y1, z1, x2, y2, z2 ...]
		for (std::size_t i = 0, j = 0; i < points_series.get_size(); ++i)
		{	
			// Нормализация данных из pointSeries
			x = math_tools::data_normalize(points_series[i]->get_x(), Scene::get_min_x(), Scene::get_mid_x(), Scene::get_max_x());
			y = math_tools::data_normalize(points_series[i]->get_y(), Scene::get_min_y(), Scene::get_mid_y(), Scene::get_max_y());
			z = math_tools::data_normalize(points_series[i]->get_z(), Scene::get_min_z(), Scene::get_mid_z(), Scene::get_max_z());
			// Нормализация данных из pointSeries
			Scene::m_point_series_array[j+0] = x;
			Scene::m_point_series_array[j+1] = y;
			Scene::m_point_series_array[j+2] = z;
			// увеличение на 3 с учетом 3-х координат
			j += 3;
		}

	}
}

void Scene::add_lines_series(LineSeries& lines_series)
{
	if (lines_series.get_size() > 0)
	{
		m_line_arr_size = lines_series.get_size() * 2;
		// Размер определяется из следующего соображения количество линий * на количество точек
		// для одной линии * на количество координат одной точки
		m_line_series_array = new double[m_line_arr_size * 3];
		// Переменные для нормализвции
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		// Цикл для перевода из структуры PointSeries в которой данные 
		// хранятся как вектор Point в одномерный массив данные в котором именют
		// структуру [x0, y0, z0, x1, y1, z1, x2, y2, z2 ...]
		for (std::size_t i = 0, j = 0; i < lines_series.get_size(); ++i)
		{
			Point* ptr_point_f = lines_series[i]->get_first();
			Point* ptr_point_s = lines_series[i]->get_second();
			// Нормализация данных из lineSeries для i-й линии и её первой точки
			x = math_tools::data_normalize(ptr_point_f->get_x(), Scene::get_min_x(), Scene::get_mid_x(), Scene::get_max_x());
			y = math_tools::data_normalize(ptr_point_f->get_y(), Scene::get_min_y(), Scene::get_mid_y(), Scene::get_max_y());
			z = math_tools::data_normalize(ptr_point_f->get_z(), Scene::get_min_z(), Scene::get_mid_z(), Scene::get_max_z());
			//занесение данные в массив по j-му индексу
			Scene::m_line_series_array[j + 0] = x;
			Scene::m_line_series_array[j + 1] = y;
			Scene::m_line_series_array[j + 2] = z;	
			// Нормализация данных из lineSeries для i-й линии и её второй точки
			x = math_tools::data_normalize(ptr_point_s->get_x(), Scene::get_min_x(), Scene::get_mid_x(), Scene::get_max_x());
			y = math_tools::data_normalize(ptr_point_s->get_y(), Scene::get_min_y(), Scene::get_mid_y(), Scene::get_max_y());
			z = math_tools::data_normalize(ptr_point_s->get_z(), Scene::get_min_z(), Scene::get_mid_z(), Scene::get_max_z());
			//занесение данных в массив по j-му индексу
			Scene::m_line_series_array[j + 3] = x;
			Scene::m_line_series_array[j + 4] = y;
			Scene::m_line_series_array[j + 5] = z;
			delete ptr_point_f;
			delete ptr_point_s;
			j += 6;
		}
	}
	std::cout << "lines_series.get_size() " << lines_series.get_size() << std::endl;
}
void Scene::add_surfaces_series(SurfaceSeries* surfaces_series)
{										
	if (surfaces_series->get_size() != 0)
	{
		//Идем по поверхностям
		for (std::size_t i = 0; i < surfaces_series->get_size(); ++i)
		{
			// Идем по рядам поверхности i
			for (std::size_t j = 0; j < (*surfaces_series)[i]->get_size() - 1; ++j)
			{
				// Идем по элементам ряда j i-й поверхности
				for (std::size_t k = 0; k < (*(*surfaces_series)[i])[j]->get_size() - 1; ++k)
				{
					m_surface_arr_size += 18;
				}
			}
		}	
		
		m_surface_series_array = new double[m_surface_arr_size];
		double temp_x_1 = 0.0;
		double temp_y_1 = 0.0;
		double temp_z_1 = 0.0;
		double temp_x_2 = 0.0;
		double temp_y_2 = 0.0;
		double temp_z_2 = 0.0;
		double temp_x_3 = 0.0;
		double temp_y_3 = 0.0;
		double temp_z_3 = 0.0;
		std::size_t l = 0;
		
		//Идем по поверхностям
		for (std::size_t i = 0; i < surfaces_series->get_size(); ++i)
		{
			// Идем по рядам поверхности i
			for (std::size_t j = 0; j < (*surfaces_series)[i]->get_size() - 1; ++j)
			{
				// Идем по элементам ряда j i-й поверхности
				int r = 0;				
				for (std::size_t k = 0; k < (*(*surfaces_series)[i])[j]->get_size() - 1; )
				{
					
					switch (r)
					{
						case 0:
							temp_x_1 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j])[k]->get_x(), Scene::get_min_x(), Scene::get_mid_x(), Scene::get_max_x());
							temp_y_1 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j])[k]->get_y(), Scene::get_min_y(), Scene::get_mid_y(), Scene::get_max_y());
							temp_z_1 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j])[k]->get_z(), Scene::get_min_z(), Scene::get_mid_z(), Scene::get_max_z());

							temp_x_2 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j + 1])[k + 1]->get_x(),  Scene::get_min_x(), Scene::get_mid_x(), Scene::get_max_x());
							temp_y_2 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j + 1])[k + 1]->get_y(), Scene::get_min_y(), Scene::get_mid_y(), Scene::get_max_y());
							temp_z_2 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j + 1])[k + 1]->get_z(), Scene::get_min_z(), Scene::get_mid_z(), Scene::get_max_z());

							temp_x_3 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j+1])[k]->get_x(),  Scene::get_min_x(), Scene::get_mid_x(), Scene::get_max_x());
							temp_y_3 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j+1])[k]->get_y(), Scene::get_min_y(), Scene::get_mid_y(), Scene::get_max_y());
							temp_z_3 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j+1])[k]->get_z(), Scene::get_min_z(), Scene::get_mid_z(), Scene::get_max_z());

							r = 1;
							break;
						case 1:
							temp_x_1 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j])[k]->get_x(), Scene::get_min_x(), Scene::get_mid_x(), Scene::get_max_x());
							temp_y_1 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j])[k]->get_y(), Scene::get_min_y(), Scene::get_mid_y(), Scene::get_max_y());
							temp_z_1 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j])[k]->get_z(), Scene::get_min_z(), Scene::get_mid_z(), Scene::get_max_z());

							temp_x_2 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j])[k + 1]->get_x(),  Scene::get_min_x(), Scene::get_mid_x(), Scene::get_max_x());
							temp_y_2 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j])[k + 1]->get_y(), Scene::get_min_y(), Scene::get_mid_y(), Scene::get_max_y());
							temp_z_2 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j])[k + 1]->get_z(), Scene::get_min_z(), Scene::get_mid_z(), Scene::get_max_z());

							temp_x_3 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j + 1])[k + 1]->get_x(),  Scene::get_min_x(), Scene::get_mid_x(), Scene::get_max_x());
							temp_y_3 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j + 1])[k + 1]->get_y(), Scene::get_min_y(), Scene::get_mid_y(), Scene::get_max_y());
							temp_z_3 = math_tools::data_normalize((*(*(*surfaces_series)[i])[j + 1])[k + 1]->get_z(), Scene::get_min_z(), Scene::get_mid_z(), Scene::get_max_z());

							r = 0;
							++k;
							break;
					}
						m_surface_series_array[l + 0] = temp_x_1;
						m_surface_series_array[l + 1] = temp_y_1;
						m_surface_series_array[l + 2] = temp_z_1;
						
						m_surface_series_array[l + 3] = temp_x_2;
						m_surface_series_array[l + 4] = temp_y_2;
						m_surface_series_array[l + 5] = temp_z_2;

						m_surface_series_array[l + 6] = temp_x_3;
						m_surface_series_array[l + 7] = temp_y_3;
						m_surface_series_array[l + 8] = temp_z_3;
					// увеличение на 9 с учетом 9-х записаных координат
					l += 9;
				}
			}

		}

	}
	
}
void Scene::draw_point_series()
{
	glColor3f(0, 0, 0);
	glPointSize(10);
	glVertexPointer(3, GL_DOUBLE, 0, Scene::m_point_series_array);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POINTS, 0, m_point_arr_size);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Scene::draw_line_series()
{
	glColor3f(0, 0, 0);
	glVertexPointer(3, GL_DOUBLE, 0, m_line_series_array);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_LINES, 0, m_line_arr_size);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Scene::draw_surface_series()
{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		// точечный источник света

		// убывание интенсивности с расстоянием

		// отключено (по умолчанию)

		GLfloat light1_diffuse[] = {0.4, 0.7, 0.2};

		GLfloat light1_position[] = {0.0, 0.0, 1.0, 1.0};

		glEnable(GL_LIGHT1);

		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


		glColor3f(0.55, 0.84, 0.53);

		glVertexPointer(3, GL_DOUBLE, 0, m_surface_series_array);
		glEnableClientState(GL_VERTEX_ARRAY);
		// Делим на 3 так как на 1 треугольник требуеться 3 точки
		glDrawArrays(GL_TRIANGLES, 0, m_surface_arr_size/3);
		glDisableClientState(GL_VERTEX_ARRAY);

		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);

}
double Scene::get_max_x()
{
	return Scene::m_max_x;
}
double Scene::get_min_x()
{
	return Scene::m_min_x;
}
double Scene::get_mid_x()
{
	return 0.5 * (Scene::get_min_x() + Scene::get_max_x());
}
double Scene::get_step_x()
{
	return Scene::m_step_x;
}
void Scene::set_max_x(double max_x)
{
	Scene::m_max_x = max_x;
}
void Scene::set_min_x(double min_x)
{
	Scene::m_min_x = min_x;
}
void Scene::set_step_x(double step_x)
{
	Scene::m_step_x = step_x;
}

double Scene::get_max_y()
{
	return Scene::m_max_y;
}
double Scene::get_min_y()
{
	return Scene::m_min_y;
}
double Scene::get_mid_y()
{
	return 0.5 * (Scene::get_min_y() + Scene::get_max_y());
}
double Scene::get_step_y()
{
	return Scene::m_step_y;
}
void Scene::set_max_y(double max_y)
{
	Scene::m_max_y = max_y;
}
void Scene::set_min_y(double min_y)
{
	Scene::m_min_y = min_y;
}
void Scene::set_step_y(double step_y)
{
	Scene::m_step_y = step_y;
}

double Scene::get_max_z()
{
	return Scene::m_max_z;
}
double Scene::get_min_z()
{
	return Scene::m_min_z;
}
double Scene::get_mid_z()
{
	return 0.5 * (Scene::get_min_z() + Scene::get_max_z());
}
double Scene::get_step_z()
{
	return Scene::m_step_z;
}
void Scene::set_max_z(double max_z)
{
	Scene::m_max_z = max_z;
}
void Scene::set_min_z(double min_z)
{
	Scene::m_min_z = min_z;
}
void Scene::set_step_z(double step_z)
{
	Scene::m_step_z = step_z;
}

void Scene::paint_project_line()
{
	glColor3f(0, 0, 0);
	glLineWidth(1.5);
	glBegin(GL_LINES);
	double x, y, z;
	
	if ((sin(GRAD(Scene::m_sphi)) <= -0.15 && (sin(GRAD(Scene::m_sphi)) >= -1.0)))
		x = -1;
	else
		x = 1;
		
	if ((cos(GRAD(Scene::m_sphi)) <= 0.1 && (cos(GRAD(Scene::m_sphi)) >= -1.0)))
		y = -1;
	else
		y = 1;
	if (cos(GRAD(Scene::m_stheta)) >= -1.0 && cos(GRAD(Scene::m_stheta)) <= -0.35)
		z = 1;
	else
		z = -1;

	glVertex3f(Scene::m_select_x, Scene::m_select_y, Scene::m_select_z);
	glVertex3f(Scene::m_select_x, Scene::m_select_y, z);

	glVertex3f(Scene::m_select_x, Scene::m_select_y, Scene::m_select_z);
	glVertex3f(Scene::m_select_x, y, Scene::m_select_z);

	glVertex3f(Scene::m_select_x, Scene::m_select_y, Scene::m_select_z);
	glVertex3f(x, Scene::m_select_y, Scene::m_select_z);
	glEnd();
	glLineWidth(1);
}