#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

#include "ShaderLoader.h"

using namespace Core;

GLuint program;

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 1.0, 1.0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void initialize() {
	glEnable(GL_DEPTH_TEST);

	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VertexShader.glsl", "FragmentShader.glsl");
	glUseProgram(program);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Hello World!");
	glewInit();

	initialize();

	if (glewIsSupported("GL_VERSION_4_5")) {
		std::cout << "GLEW version 4.5\n";
	} else {
		std::cout << "GLEW 4.5 not supported\n";
	}

	glutDisplayFunc(renderScene);
	glutMainLoop();
	glDeleteProgram(program);

	return 0;
}