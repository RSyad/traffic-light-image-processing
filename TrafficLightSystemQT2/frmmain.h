#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>

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

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow
{
    Q_OBJECT

public slots:
    void processFrameAndUpdateGUI();                // function prototype

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

    // function prototypes ////////////////////////////////////////////////////////////////////////////
    void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);
    void addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);
    void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);
    double distanceBetweenPoints(cv::Point point1, cv::Point point2);
    void drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName);
    void drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName);
    void drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy);
    void drawCase(cv::Mat &imgFrame2Copy, int choice);
    void drawTimer(cv::Mat &imgFrame2Copy, int noOfFrames);
    ///////////////////////////////////////////////////////////////////////////////////////////////////

private slots:

    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn4_clicked();

    void on_btn3_clicked();

    void on_btn6_clicked();

    void on_btn5_clicked();

private:

   Ui::frmMain *ui;

   cv::VideoCapture capVideo;

   cv::Mat imgFrame1;
   cv::Mat imgFrame2;

   std::vector<Blob> blobs;

   std::vector<cv::Point> ROI_Vertices1;
   std::vector<cv::Point> ROI_Vertices2;
   std::vector<cv::Point> ROI_Vertices3;
   std::vector<cv::Point> ROI_Vertices4;
   std::vector<cv::Point> ROI_Poly1;
   std::vector<cv::Point> ROI_Poly2;
   std::vector<cv::Point> ROI_Poly3;
   std::vector<cv::Point> ROI_Poly4;

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
   int caseChoice;

   cv::Mat imageBlank;

   char chCheckForEscKey;

   bool blnFirstFrame;

   bool checkCase2;
   bool checkCase3;
   bool checkCase4;
   bool checkCase5;

   int frameCount;

   std::vector<cv::Rect> roi;

   QTimer* qtimer;                 // timer for processFrameAndUpdateGUI()

   QImage frmMain::matToQImage(cv::Mat mat);       // function prototype

   void frmMain::exitProgram();                    // function prototype
};

#endif // FRMMAIN_H
