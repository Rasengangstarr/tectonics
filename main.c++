#include <GL/glut.h>
#include "molecule.c++"

Molecule test_mol;

static const int FPS = 60;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    test_mol.render();	
	
	glFlush();	
	glutSwapBuffers();
}

void timer(int v) {
	test_mol.move();	
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
		glOrtho(-50.0, 50.0, -50.0/aspect, 50.0/aspect, -1.0, 1.0);
	} else {
	    // height is smaller, go from -50 .. 50 in height
	    glOrtho(-50.0*aspect, 50.0*aspect, -50.0, 50.0, -1.0, 1.0);
	}
}

int main(int argc, char **argv) {
	
	test_mol.x = 0;
	test_mol.y = 0;
	test_mol.z = 0;
	test_mol.size = 1;
	test_mol.vX = 0;
	test_mol.vY = 0;
	test_mol.vZ = 0;
	

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
