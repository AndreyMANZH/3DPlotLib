#include "TextLabel.h"
#include <string>
#include <GL/GLUT.h>
TextLabel::TextLabel(char* line, double x, double y, double z)
{
    int len, i;
	this->line = line;
    glRasterPos3f(x, y, z);

    len = (int)strlen(line);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line[i]);
    }
}