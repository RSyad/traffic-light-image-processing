#pragma once

// TrafficLightsInterface.h

#ifndef _TLIGHT_INTERFACE
#define _TLIGHT_INTERFACE

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

// global variables ///////////////////////////////////////////////////////////////////////////////
const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_YELLOW = cv::Scalar(0.0, 255.0, 255.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);

class TrafficLightsInterface
{
public:
	virtual void drawEmpty(cv::Mat &imgFrame2Copy, cv::Scalar color) = 0;
	virtual void drawTrafficLight(cv::Mat &imgFrame2Copy, cv::Scalar color) = 0;
	virtual void turnTrafficLight(cv::Mat &imgFrame2Copy, int &turn) = 0;
    virtual void drawTimer(cv::Mat &imgFrame2Copy) = 0;

	virtual bool getCarPassed() = 0;
	virtual bool getYellowLight() = 0;
	virtual int getTimer() = 0;
    virtual int getTimer2() = 0;
	virtual bool getTrafficGo() = 0;
	virtual bool getIsEmpty() = 0;
    virtual bool getTimerExceed() = 0;

	virtual int getCirclePositionX() = 0;
	virtual int getCirclePositionY() = 0;

	virtual void setCarPassed(bool carPassed) = 0;
	virtual void setYellowLight(bool yellowLight) = 0;
	virtual void minusTimer(int timer) = 0;
	virtual void plusTimer(int timer) = 0;
	virtual void setTimer(int timer) = 0;
    virtual void plusTimer2(int timer2) = 0;
    virtual void setTimer2(int timer2) = 0;
	virtual void setTrafficGo(bool trafficGo) = 0;
	virtual void setIsEmpty(bool isEmpty) = 0;
    virtual void setTimerExceed(bool timerExceed) = 0;
};

#endif    // _TLIGHT_INTERFACE
