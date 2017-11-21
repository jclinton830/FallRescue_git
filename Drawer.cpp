#include "Drawer.h"
#include "HumanTracker.h"
#include "SerialPort.h"
#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <Ole2.h>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

namespace FallRescue
{

Drawer::Drawer()
{
}


Drawer::~Drawer()
{
}

void Drawer::drawBoundingBox()
{
	//tolerances 
	CameraSpacePoint Tolerance;
	Tolerance.X = 0.1;
	Tolerance.Y = 0.1;

	//vertices of the bounding box
	CameraSpacePoint TopLeftVertice;
	CameraSpacePoint TopRightVertice;
	CameraSpacePoint BottomLeftVertice;
	CameraSpacePoint BottomRightVertice;

	//variables used to find the boundaries of the bounding box
	CameraSpacePoint initminFeet;
	CameraSpacePoint initminLeft;
	CameraSpacePoint initmaxRight;

	//calculating boundaries
	initmaxRight.X = std::max(rknee.X, std::max(rfoot.X, std::max(relbow.X, rhand.X)));
	initminLeft.X = std::min(lknee.X, std::min(lfoot.X, std::min(lelbow.X, lhand.X)));
	inithead.Y = head.Y;
	initminFeet.Y = std::min(lfoot.Y, rfoot.Y);
	//head2toe.Y = head.Y - initminFeet.Y;

	//coordinates od the vertices 
	TopLeftVertice.X = initminLeft.X - Tolerance.X;
	TopLeftVertice.Y = head.Y + Tolerance.Y;
	TopLeftVertice.Z = spineshoulder.Z;

	TopRightVertice.X = initmaxRight.X + Tolerance.X;
	TopRightVertice.Y = head.Y + Tolerance.Y;
	TopRightVertice.Z = spineshoulder.Z;

	BottomLeftVertice.X = initminLeft.X - Tolerance.X;
	BottomLeftVertice.Y = initminFeet.Y - Tolerance.Y;
	BottomLeftVertice.Z = spineshoulder.Z;

	BottomRightVertice.X = initmaxRight.X + Tolerance.X;
	BottomRightVertice.Y = initminFeet.Y - Tolerance.Y;
	BottomRightVertice.Z = spineshoulder.Z;

	//drwaing the bounding box
	glColor3f(0.f, 1.f, 0.f);
	glBegin(GL_LINES);
	glLineWidth(10.0f);
	glVertex3f(TopLeftVertice.X, TopLeftVertice.Y, TopLeftVertice.Z);
	glVertex3f(TopRightVertice.X, TopRightVertice.Y, TopRightVertice.Z);
	glVertex3f(TopRightVertice.X, TopRightVertice.Y, TopRightVertice.Z);
	glVertex3f(BottomRightVertice.X, BottomRightVertice.Y, BottomRightVertice.Z);
	glVertex3f(BottomRightVertice.X, BottomRightVertice.Y, BottomRightVertice.Z);
	glVertex3f(BottomLeftVertice.X, BottomLeftVertice.Y, BottomLeftVertice.Z);
	glVertex3f(BottomLeftVertice.X, BottomLeftVertice.Y, BottomLeftVertice.Z);
	glVertex3f(TopLeftVertice.X, TopLeftVertice.Y, TopLeftVertice.Z);
	glEnd();

	float delta_head;
	HumanTracker time;
	int counter = time.TicToc;

	//std::cout << "time: "<< (int)TicToc << std::endl;
	float max_threshold = 0.25;
	float min_threshold = 0.005;

	float mid_threshold = 1.1;

	HumanTracker humanTracker;
	if (counter % 4000 == 0)
	{
		delta_head = abs(head.Y - std::min(lfoot.Y, rfoot.Y));
		//std::cout << "height difference: " << delta_head << std::endl;

		if (delta_head < max_threshold)
		{
			//fall intitiated
			std::cout << "Fall initiated" << std::endl;
			if ((delta_head > min_threshold) && (delta_head < max_threshold))
			{
				//fall detected
				std::cout << "FALL DETECTED" << std::endl;
				humanTracker.transferData("FALL");
				return;
			}
			else
			{
				std::cout << "NOT A FALL" << std::endl;
				return;
			}
		}

		if ((delta_head > max_threshold) && (delta_head < mid_threshold))
		{
			//not a fall scenario
			std::cout << "SEATED" << std::endl;
			return;
		}

	}
}

void Drawer::drawKinectData() {

	HumanTracker getKinectData();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnable(GL_PROGRAM_POINT_SIZE);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, cboId);
	glColorPointer(3, GL_FLOAT, 0, NULL);

	glLineWidth(5.0f);
	glPointSize(15.0f);

	glDrawArrays(GL_POINTS, 0, width*height);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	HumanTracker human;
	for (int i = 0; i < BODY_COUNT; i++) {
		if (human.tracked){

			//Draw Joints
			glBegin(GL_POINTS);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(lthumb.X, lthumb.Y, lthumb.Z);
			glVertex3f(rthumb.X, rthumb.Y, rthumb.Z);
			glVertex3f(lhandtip.X, lhandtip.Y, lhandtip.Z);
			glVertex3f(rhandtip.X, rhandtip.Y, rhandtip.Z);
			glVertex3f(lhand.X, lhand.Y, lhand.Z);
			glVertex3f(rhand.X, rhand.Y, rhand.Z);
			glVertex3f(lwrist.X, lwrist.Y, lwrist.Z);
			glVertex3f(rwrist.X, rwrist.Y, rwrist.Z);
			glVertex3f(lelbow.X, lelbow.Y, lelbow.Z);
			glVertex3f(relbow.X, relbow.Y, relbow.Z);
			glVertex3f(lshoulder.X, lshoulder.Y, lshoulder.Z);
			glVertex3f(rshoulder.X, rshoulder.Y, rshoulder.Z);
			glVertex3f(spineshoulder.X, spineshoulder.Y, spineshoulder.Z);
			glVertex3f(neck.X, neck.Y, neck.Z);
			glVertex3f(head.X, head.Y, head.Z);
			glVertex3f(spinemid.X, spinemid.Y, spinemid.Z);
			glVertex3f(spinebase.X, spinebase.Y, spinebase.Z);
			glVertex3f(lhip.X, lhip.Y, lhip.Z);
			glVertex3f(rhip.X, rhip.Y, rhip.Z);
			glVertex3f(lknee.X, lknee.Y, lknee.Z);
			glVertex3f(rknee.X, rknee.Y, rknee.Z);
			glVertex3f(lankle.X, lankle.Y, lankle.Z);
			glVertex3f(rankle.X, rankle.Y, rankle.Z);
			glVertex3f(lfoot.X, lfoot.Y, lfoot.Z);
			glVertex3f(rfoot.X, rfoot.Y, rfoot.Z);
			glEnd();

			// Draw skeleton
			glBegin(GL_LINES);
			glColor3f(1.f, 0.f, 0.f);
			//left upper body lines
			glVertex3f(lhandtip.X, lhandtip.Y, lhandtip.Z);
			glVertex3f(lhand.X, lhand.Y, lhand.Z);
			glVertex3f(lthumb.X, lthumb.Y, lthumb.Z);
			glVertex3f(lhand.X, lhand.Y, lhand.Z);
			glVertex3f(lhand.X, lhand.Y, lhand.Z);
			glVertex3f(lwrist.X, lwrist.Y, lwrist.Z);
			glVertex3f(lwrist.X, lwrist.Y, lwrist.Z);
			glVertex3f(lelbow.X, lelbow.Y, lelbow.Z);
			glVertex3f(lelbow.X, lelbow.Y, lelbow.Z);
			glVertex3f(lshoulder.X, lshoulder.Y, lshoulder.Z);
			glVertex3f(lshoulder.X, lshoulder.Y, lshoulder.Z);
			glVertex3f(spineshoulder.X, spineshoulder.Y, spineshoulder.Z);
			glEnd();
			//right upper body lines
			glBegin(GL_LINES);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(spineshoulder.X, spineshoulder.Y, spineshoulder.Z);
			glVertex3f(rshoulder.X, rshoulder.Y, rshoulder.Z);
			glVertex3f(rshoulder.X, rshoulder.Y, rshoulder.Z);
			glVertex3f(relbow.X, relbow.Y, relbow.Z);
			glVertex3f(relbow.X, relbow.Y, relbow.Z);
			glVertex3f(rwrist.X, rwrist.Y, rwrist.Z);
			glVertex3f(rwrist.X, rwrist.Y, rwrist.Z);
			glVertex3f(rhand.X, rhand.Y, rhand.Z);
			glVertex3f(rhand.X, rhand.Y, rhand.Z);
			glVertex3f(rthumb.X, rthumb.Y, rthumb.Z);
			glVertex3f(rhand.X, rhand.Y, rhand.Z);
			glVertex3f(rhandtip.X, rhandtip.Y, rhandtip.Z);
			glEnd();
			//mid upper body lines
			glBegin(GL_LINES);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(spineshoulder.X, spineshoulder.Y, spineshoulder.Z);
			glVertex3f(neck.X, neck.Y, neck.Z);
			glVertex3f(neck.X, neck.Y, neck.Z);
			glVertex3f(head.X, head.Y, head.Z);
			glEnd();
			//mid center body lines
			glBegin(GL_LINES);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(spineshoulder.X, spineshoulder.Y, spineshoulder.Z);
			glVertex3f(spinemid.X, spinemid.Y, spinemid.Z);
			glVertex3f(spinemid.X, spinemid.Y, spinemid.Z);
			glVertex3f(spinebase.X, spinebase.Y, spinebase.Z);
			glEnd();
			//left lower body lines
			glBegin(GL_LINES);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(spinebase.X, spinebase.Y, spinebase.Z);
			glVertex3f(lhip.X, lhip.Y, lhip.Z);
			glVertex3f(lhip.X, lhip.Y, lhip.Z);
			glVertex3f(lknee.X, lknee.Y, lknee.Z);
			glVertex3f(lknee.X, lknee.Y, lknee.Z);
			glVertex3f(lankle.X, lankle.Y, lankle.Z);
			glVertex3f(lankle.X, lankle.Y, lankle.Z);
			glVertex3f(lfoot.X, lfoot.Y, lfoot.Z);
			glEnd();
			//right lower body lines 
			glBegin(GL_LINES);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(spinebase.X, spinebase.Y, spinebase.Z);
			glVertex3f(rhip.X, rhip.Y, rhip.Z);
			glVertex3f(rhip.X, rhip.Y, rhip.Z);
			glVertex3f(rknee.X, rknee.Y, rknee.Z);
			glVertex3f(rknee.X, rknee.Y, rknee.Z);
			glVertex3f(rankle.X, rankle.Y, rankle.Z);
			glVertex3f(rankle.X, rankle.Y, rankle.Z);
			glVertex3f(rfoot.X, rfoot.Y, rfoot.Z);
			glEnd();


			drawBoundingBox();

		}
	}

}

}
