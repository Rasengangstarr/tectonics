#include <GL/glut.h>
#include "molecule.c++"


Molecule mols[2];

static const int NUMMOLS = 2;
static const int FPS = 60;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	for (int i = 0; i < NUMMOLS; i++)	
		mols[i].render();	
	
	glFlush();	
	glutSwapBuffers();
}

void timer(int v) {
	
	for (int i = 0; i < NUMMOLS; i++)	
		mols[i].move(mols, NUMMOLS);	
	
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, v);
}
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		// width is smaller, go from -50 .. 50 in width
		glOrtho(-50.0, 50.0, -50.0/aspect, 50.0/aspect, 0.0, 1.0);
	} else {
	    // height is smaller, go from -50 .. 50 in height
	    glOrtho(-50.0*aspect, 50.0*aspect, -50.0, 50.0, -5.0, 5.0);
	}
}

int main(int argc, char **argv) {
	Molecule mol1;
	Molecule mol2;	
	mol1.id = 0;	
	mol1.x = 1;
	mol1.y = 0;
	mol1.z = 0;
	mol1.size = 2;
	mol1.vX = 0;
	mol1.vY = 0;
	mol1.vZ = 0;	
	
	mol2.id = 1;	
	mol2.x = 0;
	mol2.y = 10;
	mol2.z = 0;
	mol2.size = 2;
	mol2.vX = 0;
	mol2.vY = 0;
	mol2.vZ = 0;	

	mols[0] = mol1;
	mols[1] = mol2;	
	
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Convection");
		
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutTimerFunc(100,timer,0);
		
	// enter GLUT event processing cycle
	glutMainLoop();
		 										
	return 1;
}
