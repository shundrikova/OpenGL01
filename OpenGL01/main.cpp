#include <windows.h>
#include <gl\freeglut.h>
#include <time.h> 

static int w = 0, h = 0;

double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;

int shape = rand() % 9;

void renderWireTeapot(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);

	glutWireTeapot(.5);

	glFlush();
	glutSwapBuffers();
}

void renderRectangle() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(rotate_z, 0.0, 0.0, 1.0);

	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.5f);  
	glVertex2f(-0.5f, 0.5f);  
	glVertex2f(0.5f, 0.5f); 
	glVertex2f(0.5f, -0.5f);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void renderTriangle() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(rotate_z, 0.0, 0.0, 1.0);

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5f, -0.5f, 0.0f); 
	glVertex3f(-0.5f, 0.5f, 0.0f); 
	glVertex3f(0.5f, 0.5f, 0.0f);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void renderColorTriangle() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(rotate_z, 0.0, 0.0, 1.0);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);  	glVertex3f(-0.5f, -0.5f, 0.0f);
	glColor3f(0.0, 1.0, 0.0);  	glVertex3f(-0.5f, 0.5f, 0.0f);
	glColor3f(0.0, 0.0, 1.0);  	glVertex3f(0.5f, 0.5f, 0.0f);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP: rotate_x += 5; break;
		case GLUT_KEY_DOWN: rotate_x -= 5; break;

		case GLUT_KEY_RIGHT: rotate_y += 5; break;
		case GLUT_KEY_LEFT: rotate_y -= 5; break;

		case GLUT_KEY_PAGE_UP: rotate_z += 5; break;
		case GLUT_KEY_PAGE_DOWN: rotate_z -= 5; break;
	}
	glutPostRedisplay();
}

void renderRandomShape() {
	srand(time(NULL));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3ub(rand() % 255, rand() % 255, rand() % 255);
	glLoadIdentity();

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);

	switch (shape){
		case 0: glutWireSphere(.7, 50, 50); break;
		case 1: glutWireCube(1); break;
		case 2: glutWireCone(.7, .7, 50, 50);  break;
		case 3: glutWireTorus(.5, .2, 50, 50);  break;
		case 4: glScaled(.5, .5, .5); glutWireDodecahedron(); break;
		case 5: glutWireOctahedron(); break;
		case 6: glutWireTetrahedron(); break;
		case 7: glutWireIcosahedron(); break;
		case 8: glutWireTeapot(.5); break;
	}
	glFlush();
	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		glColor3ub(rand() % 255, rand() % 255, rand() % 255);
		shape = rand() % 9;
		glutPostRedisplay();
	}
}

void Keyboard(unsigned char key, int x, int y) {
	#define ESCAPE '\033'
		if (key == ESCAPE)
			exit(0);
}

void Reshape(int width, int height) {
	w = width;   h = height;
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(550, 550);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("OpenGL");
	// 1.
	//glutDisplayFunc(renderWireTeapot);
	// 2.
	//glutDisplayFunc(renderRectangle);
	//glutDisplayFunc(renderTriangle);
	//glutDisplayFunc(renderColorTriangle);
	// 3.
	glutDisplayFunc(renderRandomShape);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);

	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}