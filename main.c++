#include <GL/glut.h>
#include "molecule.c++"

static const int NUMMOLS = 1000;

static const int FPS = 60;
Molecule mols[NUMMOLS];

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	for (int i = 0; i < NUMMOLS; i++)	
		mols[i].render();	
	
	glFlush();	
	glutSwapBuffers();
}


float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
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
		glOrtho(-50.0, 50.0, -50.0/aspect, 50.0/aspect, -50.0, 50.0);
	} else {
	    // height is smaller, go from -50 .. 50 in height
	    glOrtho(-50.0*aspect, 50.0*aspect, -50.0, 50.0, -50.0, 50.0);
	}
}

int main(int argc, char **argv) {
	
	for (int i = 0; i < NUMMOLS; i++)
	{
		Molecule mol;
		mol.id = i;
		mol.x = RandomFloat(-20, 20);
		mol.y = RandomFloat(-20, 20);
		mol.z = 0;
		mol.size = 0.5;
		mol.temp = 0;
		mol.vX = RandomFloat(-0.5, 0.5);
		mol.vY = 0;
		mol.vZ = 0;
		mols[i] = mol;
	}

	
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
