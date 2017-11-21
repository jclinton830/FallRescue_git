#include "HumanTracker.h"
#include "SerialPort.h"
#include "glut.h"
#include "Drawer.h"
namespace FallRescue
{
HumanTracker::HumanTracker()
{
}

bool HumanTracker::initKinect()
{
	if (FAILED(GetDefaultKinectSensor(&sensor))) {
		return false;
	}
	if (sensor) {
		sensor->get_CoordinateMapper(&mapper);

		sensor->Open();
		sensor->OpenMultiSourceFrameReader(
			FrameSourceTypes::FrameSourceTypes_Body,
			&reader);
		return reader;
	}
	else {
		return false;
	}
}

void HumanTracker::getBodyData(IMultiSourceFrame* frame)
{
	IBodyFrameReader* bodyframeReader = NULL;
	IBodyFrame* bodyframe;
	IBodyFrameReference* frameref = NULL;

	frame->get_BodyFrameReference(&frameref);
	frameref->AcquireFrame(&bodyframe);
	if (frameref) frameref->Release();

	if (!bodyframe) return;

	//getting timespan
	TicToc = bodyframe->get_RelativeTime(&nTime);
	if (!nStartTime)
	{
		nStartTime = nTime;
	}
	TicToc = (nTime - nStartTime) / 10000.f;


	double scale = 0.01;
	TicToc = (int)(TicToc / scale) * scale;
	//std::cout << "Time Span: " << (int)TicToc << std::endl;
	LARGE_INTEGER qpcNow = { 0 };

	if (m_fFreq)
	{
		if (QueryPerformanceCounter(&qpcNow))
		{
			if (m_nLastCounter)
			{
				m_nFramesSinceUpdate++;
				fps = m_fFreq * m_nFramesSinceUpdate / double(qpcNow.QuadPart - m_nLastCounter);
			}
		}
	}
	//std::cout << "FPS: " << fps << std::endl;

	//getting joint data
	Drawer skeleton;
	IBody* body[BODY_COUNT] = { 0 };
	bodyframe->GetAndRefreshBodyData(BODY_COUNT, body);
	for (int i = 0; i < BODY_COUNT; i++) {
		body[i]->get_IsTracked(&tracked);
		if (tracked) {
			body[i]->GetJoints(JointType_Count, skeleton.joints);
			break;
		}
	}
	if (bodyframe) bodyframe->Release();
}

void HumanTracker::getKinectData()
{
	IMultiSourceFrame* frame = NULL;
	if (SUCCEEDED(reader->AcquireLatestFrame(&frame))) {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		getBodyData(frame);
	}
	if (frame) frame->Release();
}

void HumanTracker::transferData(std::string activity)
{
	SerialPort arduino(port_name);
	if (arduino.isConnected())
	{
		std::cout << "Connection Established" << std::endl;
		activity = "FALL";
		if (activity == "FALL")
		{
			char fall_data[] = "at+send=1\r";
			arduino.writeSerialPort(fall_data, 10);
		}

	}
	else
	{
		std::cout << "ERROR, check port name" << std::endl;
	}
	return;
}

HumanTracker::~HumanTracker()
{
}
}
