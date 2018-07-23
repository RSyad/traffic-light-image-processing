#pragma once

// LineInterface.h

#ifndef _LINE_INTERFACE
#define _LINE_INTERFACE

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include "TrafficLightsC1.h"
#include "TrafficLightsC2.h"
#include "Blob.h"
#include<iostream>

class LineInterface
{
public:
    virtual void drawRectangle(cv::Mat &imgFrame, cv::Scalar color) = 0;
	
	virtual bool checkLineCrossed(std::vector<Blob> &blobs) = 0;
};

#endif    // _LINE_INTERFACE
