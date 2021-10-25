#include <GL/glut.h>
#include <math.h>
#include "molecule.h"
#include <iostream>


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

void Molecule::move(Molecule molecules[], int numMol)
{
	//Acceleration due to gravity?
	
    if (y >= -30)	
		vY -= 0.01;
	else
	{
		vY = vY * -1 * 0.4;
		y = -30;
	}

	GLfloat totalVel = sqrt(pow(vX,2) + pow(vY,2) +  pow(vZ,2));

	for (int m = 0; m < numMol; m++)
	{
		//don't try and collide with yourself
		if (molecules[m].id	== id){
			continue;
		}

		GLfloat otherSize = molecules[m].size;

		GLfloat dx = (x + size) - (molecules[m].x + otherSize);
		GLfloat dy = (y + size) - (molecules[m].y + otherSize);
		GLfloat dz = (z + size) - (molecules[m].z + otherSize);

		GLfloat distance = sqrt(pow(dx,2) + pow(dy,2) + pow(dz,2)); 

		if (distance <= size + otherSize)
		{
			GLfloat overlap = distance - size + otherSize;
			//there was a collision, so calculate the angles of collision
			GLfloat alpha = getAngle(x, y, z, molecules[m].x, molecules[m].y, molecules[m].z);
			GLfloat beta = getAngle2(x, y, z, molecules[m].x, molecules[m].y, molecules[m].z);
			//and apply them to the velocity
			vX = totalVel * sin (alpha + 180) * cos(beta + 180) * 0.6;
			vY = totalVel * sin (beta + 180) * 0.6; 
			vZ = totalVel * cos (alpha + 180) * cos(beta + 180) * 0.6;
			
			//x -= overlap;	
			//y -= overlap;	
			//z -= overlap;	
			//and move the objects out of each other
		    	
		}
	}
	
	x += vX;
	y += vY;
	z += vZ;


}

GLfloat Molecule::getAngle (GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2) 
{
    GLfloat theta = atan2(z1-z2,x1-x2);
    return -theta*180/3.1415926;
}

GLfloat Molecule::getAngle2 (GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2)
{
    GLfloat dist=sqrt(pow(x1 - x2,2) + pow(y1 - y2,2) + pow(z1 - z2,2));
    GLfloat dist2=sqrt(pow(x1 - x2,2) + pow(z1 - z2,2));
    return acos(dist2/dist)*180/3.1415926;
}

