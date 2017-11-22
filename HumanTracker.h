#ifndef HUMANTRACKER_H_
#define HUMANTRACKER_H_

#pragma once

#include <Kinect.h>
#include <iostream>
#include <string>
#include "SerialPort.h"

namespace FallRescue
{
class HumanTracker
{
public:
	HumanTracker();
	~HumanTracker();
	bool initKinect();
	void getKinectData();
	void getBodyData(IMultiSourceFrame* frame);
	void transferData(std::string activity);

public:
	float					TicToc;
	BOOLEAN tracked;							// Whether we see a body
	// Kinect Variables
	IKinectSensor* sensor;             // Kinect sensor
	IMultiSourceFrameReader* reader;   // Kinect data source
	ICoordinateMapper* mapper;         // Converts between depth, color, and 3d coordinates

private:

	INT64                   m_nLastCounter;
	double                  m_fFreq;
	DWORD                   m_nFramesSinceUpdate;
	INT64                   m_nStartTime;
	double					fps = 0.0;
	INT64					nTime = 0;
	INT64					nStartTime = 0;
	HWND                    m_hWnd;

	
	

	//String for getting the output from arduino
	char output[MAX_DATA_LENGTH];

	/*Portname must contain these backslashes, and remember to
	replace the following com port*/
	char *port_name = "\\\\.\\COM3";

	//String for incoming data
	char incomingData[MAX_DATA_LENGTH];
};
}

#endif //HUMANTRACKER_H_