#include "glut.h"
#include "HumanTracker.h"
#include "Drawer.h"

namespace FallRescue
{
glut::glut()
{
}


glut::~glut()
{
}

 void glut::draw() {
	HumanTracker drawKinectData();
	glutSwapBuffers();
}

void glut::execute() {
	glutMainLoop();
}

bool glut::init(int argc, char* argv[]) {

	Drawer drawer;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(drawer.width, drawer.height);
	glutCreateWindow("Human Tracker");
	glutDisplayFunc(glut::draw);
	glutIdleFunc(glut::draw);
	glewInit();
	return true;
}
}


