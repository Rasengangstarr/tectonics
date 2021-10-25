#ifndef MOLECULE_H
#define MOLECULE_H

#include <GL/glut.h>

class Molecule
{
	private:
		GLfloat getAngle (GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2);
		GLfloat getAngle2 (GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2);
    
	
	public:
		int id;
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat vX;
		GLfloat vY;
		GLfloat vZ;
        GLfloat temp;
        GLfloat size;

        void render();
        void move(Molecule molecules[], int numMol);
};

#endif

