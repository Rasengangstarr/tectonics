#ifndef MOLECULE_H
#define MOLECULE_H

#include <GL/glut.h>

class Molecule
{
    public:
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat vX;
		GLfloat vY;
		GLfloat vZ;
        GLfloat temp;
        GLfloat size;

        void render();
        void move();
};

#endif
