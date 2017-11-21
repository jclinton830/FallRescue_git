#ifndef DRAWER_H_
#define DRAWER_H_

#pragma once
#include "glut.h"
#include <Kinect.h>


namespace FallRescue
{
class Drawer
{
public:
	Drawer();
	~Drawer();
	void drawBoundingBox();
	void drawKinectData();

public:
	const int width = 512;
	const int height = 424;
	const int colorwidth = 1920;
	const int colorheight = 1080;
	// We'll be using buffer objects to store the kinect point cloud
	GLuint vboId;
	GLuint cboId;

	// Body tracking variables
	Joint joints[JointType_Count];				// List of joints in the tracked body

private: 


	const CameraSpacePoint& lwrist = joints[JointType_WristLeft].Position;;
	const CameraSpacePoint& rwrist = joints[JointType_WristRight].Position;;
	const CameraSpacePoint& lelbow = joints[JointType_ElbowLeft].Position;;
	const CameraSpacePoint& relbow = joints[JointType_ElbowRight].Position;;
	const CameraSpacePoint& lshoulder = joints[JointType_ShoulderLeft].Position;;
	const CameraSpacePoint& rshoulder = joints[JointType_ShoulderRight].Position;;
	const CameraSpacePoint& lhand = joints[JointType_HandLeft].Position;;
	const CameraSpacePoint& rhand = joints[JointType_HandRight].Position;;
	const CameraSpacePoint& lhip = joints[JointType_HipLeft].Position;;
	const CameraSpacePoint& rhip = joints[JointType_HipRight].Position;;
	const CameraSpacePoint& lknee = joints[JointType_KneeLeft].Position;;
	const CameraSpacePoint& rknee = joints[JointType_KneeRight].Position;;
	const CameraSpacePoint& lankle = joints[JointType_AnkleLeft].Position;;
	const CameraSpacePoint& rankle = joints[JointType_AnkleRight].Position;;
	const CameraSpacePoint& lfoot = joints[JointType_FootLeft].Position;;
	const CameraSpacePoint& rfoot = joints[JointType_FootRight].Position;;
	const CameraSpacePoint& spineshoulder = joints[JointType_SpineShoulder].Position;;
	const CameraSpacePoint& spinebase = joints[JointType_SpineBase].Position;;
	const CameraSpacePoint& spinemid = joints[JointType_SpineMid].Position;;
	const CameraSpacePoint& neck = joints[JointType_Neck].Position;;
	const CameraSpacePoint& head = joints[JointType_Head].Position;;
	const CameraSpacePoint& lthumb = joints[JointType_ThumbLeft].Position;;
	const CameraSpacePoint& rthumb = joints[JointType_ThumbRight].Position;;
	const CameraSpacePoint& lhandtip = joints[JointType_HandTipLeft].Position;;
	const CameraSpacePoint& rhandtip = joints[JointType_HandTipRight].Position;;

	CameraSpacePoint inithead;
	CameraSpacePoint finhead;


};
}
#endif //DRAWER_H_

