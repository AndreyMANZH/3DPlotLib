#include "TextLabel.h"

TextLabel::TextLabel(char* line, double x, double y, double z):
    m_line(line)
{
    unsigned int len = static_cast<int>(strlen(line));
    glRasterPos3f(x, y, z);

    for (unsigned int i = 0; i < len; i++) 
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, line[i]);
    }
}