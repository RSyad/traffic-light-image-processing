#pragma once

// LineC1.h

#ifndef MY_LINEC1
#define MY_LINEC1

#include "LineInterface.h"

class LineC1 : public LineInterface
{
private:
	int id;

    std::vector<cv::Point> contour;
    const cv::Point *pts;
    int npts;

public:
	LineC1(int junction);
	
    void drawRectangle(cv::Mat &imgFrame, cv::Scalar color);
	bool checkLineCrossed(std::vector<Blob> &blobs);
};

#endif    // MY_LINEC1
