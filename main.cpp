#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 1.0, 1.0);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Hello World!");

	glewInit();
	if (glewIsSupported("GL_VERSION_4_5")) {
		std::cout << "GLEW version 4.5\n";
	} else {
		std::cout << "GLEW 4.5 not supported\n";
	}

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);
	glutMainLoop();

	return 0;
}