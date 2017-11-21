#include "glut.h"
#include "SerialPort.h"
#include "Drawer.h"
#include "HumanTracker.h"

#include <iostream>
#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <minwindef.h>

using namespace FallRescue;


int main(int argc, char* argv[])
{
	glut glut;
	HumanTracker humanTracker;
	Drawer drawer;

	if (!glut.init(argc, argv)) return 1;
	if (!humanTracker.initKinect()) return 1;

	// OpenGL setup
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);

	// Set up array buffers
	const int dataSize = drawer.width*drawer.height * 3 * 4;
	glGenBuffers(1, &drawer.vboId);
	glBindBuffer(GL_ARRAY_BUFFER, drawer.vboId);
	glBufferData(GL_ARRAY_BUFFER, dataSize, 0, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &drawer.cboId);
	glBindBuffer(GL_ARRAY_BUFFER, drawer.cboId);
	glBufferData(GL_ARRAY_BUFFER, dataSize, 0, GL_DYNAMIC_DRAW);

	// Camera setup
	glViewport(0, 0, drawer.width, drawer.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, drawer.width / (GLdouble)drawer.height, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0);

	// Main loop
	glut.execute();

	return 0;

}
