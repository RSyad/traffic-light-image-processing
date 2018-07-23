#ifndef CASE_H
#define CASE_H

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // it may be necessary to change or remove this line if not using Windows

#include "LinkedList.h"
#include "TrafficLightsC1.h"
#include "TrafficLightsC2.h"
#include "LineC1.h"
#include "LineC2.h"

class Case{
    cv::VideoCapture capVideo;

    cv::Mat imgFrame1;
    cv::Mat imgFrame2;

    std::vector<Blob> blobs;

    TrafficLightsInterface* traffic1;
    TrafficLightsInterface* traffic2;
    TrafficLightsInterface* traffic3;
    TrafficLightsInterface* traffic4;
    LinkedList<TrafficLightsInterface*>* TLightsList;

    LineInterface* line1;
    LineInterface* line2;
    LineInterface* line3;
    LineInterface* line4;
    LinkedList<LineInterface*>* LineList;

    int timeLimit;
    int turn;

    cv::Mat imageBlank;

    char chCheckForEscKey;

    bool blnFirstFrame;

    int frameCount;

    void chooseCase(int option);
};

#endif // CASE_H
