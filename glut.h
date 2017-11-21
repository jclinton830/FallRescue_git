#ifndef GLUT_H_
#define GLUT_H_

#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

#pragma once

namespace FallRescue
{
class glut
{
public:
	glut();
	~glut();
	bool init(int argc, char* argv[]);
	static void draw();
	void execute();
};
}
#endif //GLUT_H_




