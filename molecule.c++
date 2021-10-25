#include <GL/glut.h>
#include "molecule.h"

void Molecule::render()
{
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1, 1, 1); glVertex3f(x, y+2*size, z);
		glColor3f(1, 0, 0); glVertex3f(x-size, y, z+size);
		glColor3f(0, 1, 0); glVertex3f(x+size, y, z+size);
		glColor3f(0, 0, 1); glVertex3f(x, y, z-1.4*size);
		glColor3f(1, 1, 1); glVertex3f(x, y+2*size, z);
		glColor3f(1, 0, 0); glVertex3f(x-size, y, z+size);
	glEnd();
}

void Molecule::move()
{
	//Acceleration due to gravity?
	
    if (y >= -30)	
		vY -= 0.01;
	else
	{
		vY = (vY * -1)* 0.4;
		y = -30;
	}
	
	x += vX;
	y += vY;
	z += vZ;


}
