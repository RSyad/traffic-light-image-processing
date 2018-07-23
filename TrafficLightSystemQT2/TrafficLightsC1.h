#pragma once

// TrafficLightsC1.h

#ifndef MY_TLIGHTC1
#define MY_TLIGHTC1

#include "TrafficLightsInterface.h"

class TrafficLightsC1 : public TrafficLightsInterface
{
private:
	bool carPassed;
	bool yellowLight;
	int timer;
    int timer2;
	bool trafficGo;
	bool isEmpty;
    int circleRadius;
    bool timerExceed;

    cv::Point timerPosition;
	cv::Point circlePosition;
	cv::Point textPosition;
    cv::Point timerPosition1;
	cv::Point circlePosition1;
	cv::Point textPosition1;
	cv::Point circlePosition2;
	cv::Point textPosition2;
    cv::Point timerPosition2;
	cv::Point circlePosition3;
	cv::Point textPosition3;
    cv::Point timerPosition3;
	cv::Point circlePosition4;
	cv::Point textPosition4;
    cv::Point timerPosition4;

	cv::Point textPositionEmpty;

public:
	TrafficLightsC1(int junction);
	void drawEmpty(cv::Mat &imgFrame2Copy, cv::Scalar color);
	void drawTrafficLight(cv::Mat &imgFrame2Copy, cv::Scalar color);
	void turnTrafficLight(cv::Mat &imgFrame2Copy, int &turn);
    void drawTimer(cv::Mat &imgFrame2Copy);

	bool getCarPassed();
	bool getYellowLight();
	int getTimer();
    int getTimer2();
	bool getTrafficGo();
	bool getIsEmpty();
    bool getTimerExceed();

	int getCirclePositionX();
	int getCirclePositionY();

	void setCarPassed(bool carPassed);
	void setYellowLight(bool yellowLight);
	void minusTimer(int timer);
	void plusTimer(int timer);
	void setTimer(int timer);
    void plusTimer2(int timer2);
    void setTimer2(int timer2);
	void setTrafficGo(bool trafficGo);
	void setIsEmpty(bool isEmpty);
    void setTimerExceed(bool timerExceed);
};

#endif    // MY_TLIGHTC1
