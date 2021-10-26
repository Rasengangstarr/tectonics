#include <GL/glut.h>
#include <math.h>
#include "molecule.h"
#include <iostream>


void Molecule::render()
{
//glutSolidDodecahedron();
//glBegin(GL_TRIANGLE_STRIP);
//		glColor3f(1, 1, 1); glVertex3f(x, y+2*size, z);
//		glColor3f(1, 0, 0); glVertex3f(x-size, y, z+size);
//		glColor3f(0, 1, 0); glVertex3f(x+size, y, z+size);
//		glColor3f(0, 0, 1); glVertex3f(x, y, z-1.4*size);
//		glColor3f(1, 1, 1); glVertex3f(x, y+2*size, z);
//		glColor3f(1, 0, 0); glVertex3f(x-size, y, z+size);
//	glEnd();
	glColor3d(temp*100,0,0.5);
	glPushMatrix();
        glTranslated(x, y, z);
        glScaled(size*0.5, size*0.5, size*0.5);
        glutWireDodecahedron();
    glPopMatrix(); 

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
		vX = vX * 0.8;
		vZ = vZ * 0.8;
		temp += 0.05;	
		
	}
	if (x < -30)
	{
		vX = vX * -1 * 0.4;
	    x = -30;	
	}
	else if (x > 30)
	{
		vX = vX * -1 * 0.4;
	    x = 30;	
	}
	x += vX;
	y += vY;
	//z += vZ;
	//
	if (temp > 0)
		temp -= 0.01;
	vX += (rand() % 5 - 2) * temp ;
	vY += (rand() % 3) * temp ;

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
			GLfloat beta = getAngle(x, y, z, molecules[m].x, molecules[m].y, molecules[m].z);
			GLfloat alpha = getAngle2(x, y, z, molecules[m].x, molecules[m].y, molecules[m].z);
			//and apply them to the velocity of both molecules
			GLfloat totalVel2 = sqrt(pow(molecules[m].vX,2) + pow(molecules[m].vY,2) +  pow(molecules[m].vZ,2));
			
			
			vX = (totalVel+totalVel2)/2 * cos(beta) * -0.4;
			vY = (totalVel+totalVel2)/2 * sin(beta) * -0.4;
				
			molecules[m].vX = (totalVel+totalVel2)/2 * cos(beta) * 0.4; 
			molecules[m].vY = (totalVel+totalVel2)/2 * sin(beta) * 0.4;
			
			//vZ = totalVel * cos (alpha) * cos(beta) * 0.4;
		   	int sepCount = 0; 
			//and move the objects out of each other
			while (distance <= size + otherSize)
			{
				sepCount += 1;
				if (sepCount > 1000)
					break;
				dx = (x + size) - (molecules[m].x + otherSize);
				dy = (y + size) - (molecules[m].y + otherSize);
				dz = (z + size) - (molecules[m].z + otherSize);
				distance = sqrt(pow(dx,2) + pow(dy,2) + pow(dz,2));
				x += vX;
				y += vY;
				molecules[m].x += molecules[m].vX;
				molecules[m].y += molecules[m].vY;

			}
			//z -= dy;	
		    	
		}
	}
	


}

GLfloat Molecule::getAngle (GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2) 
{
    //GLfloat theta = atan2(z1-z2,x1-x2);
	GLfloat theta = atan2(y2-y1,x2-x1);
    return theta;
}

GLfloat Molecule::getAngle2 (GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2)
{
    GLfloat dist=sqrt(pow(x1 - x2,2) + pow(y1 - y2,2) + pow(z1 - z2,2));
    GLfloat dist2=sqrt(pow(x1 - x2,2) + pow(z1 - z2,2));
    return acos(dist2/dist);
}

