#pragma once

// LineC2.h

#ifndef MY_LINEC2
#define MY_LINEC2

#include "LineInterface.h"

class LineC2 : public LineInterface
{
private:
	int id;

    std::vector<cv::Point> contour;
    const cv::Point *pts;
    int npts;

public:
	LineC2(int junction);
	
    void drawRectangle(cv::Mat &imgFrame, cv::Scalar color);
	bool checkLineCrossed(std::vector<Blob> &blobs);
};

#endif    // MY_LINEC2
