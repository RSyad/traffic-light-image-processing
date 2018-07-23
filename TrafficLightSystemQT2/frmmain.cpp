#include "frmmain.h"
#include "ui_frmmain.h"


#include<QtCore>
#include<QMessageBox>

// constructor ////////////////////////////////////////////////////////////////////////////
frmMain::frmMain(QWidget *parent) :  QMainWindow(parent), ui(new Ui::frmMain) {
    ui->setupUi(this);

    traffic1 = new TrafficLightsC1(1);
    traffic2 = new TrafficLightsC1(2);
    traffic3 = new TrafficLightsC1(3);
    traffic4 = new TrafficLightsC1(4);
    TLightsList = new LinkedList<TrafficLightsInterface*>();
    TLightsList->insert(1,traffic1);
    TLightsList->insert(2,traffic2);
    TLightsList->insert(3,traffic3);
    TLightsList->insert(4,traffic4);

    line1 = new LineC1(1);
    line2 = new LineC1(2);
    line3 = new LineC1(3);
    line4 = new LineC1(4);
    LineList = new LinkedList<LineInterface*>();
    LineList->insert(1,line1);
    LineList->insert(2,line2);
    LineList->insert(3,line3);
    LineList->insert(4,line4);

    //ROI Junction 1
    ROI_Vertices1.push_back(cv::Point( 100, 280 ));
    ROI_Vertices1.push_back(cv::Point( 220, 330));
    ROI_Vertices1.push_back(cv::Point( 70, 420));
    ROI_Vertices1.push_back(cv::Point( 1, 350));

    //ROI Junction 2
    ROI_Vertices2.push_back(cv::Point( 660, 270));
    ROI_Vertices2.push_back(cv::Point( 820, 320));
    ROI_Vertices2.push_back(cv::Point( 780, 460));
    ROI_Vertices2.push_back(cv::Point( 550, 400));

    //ROI Junction 3
    ROI_Vertices3.push_back(cv::Point( 630, 85 ));
    ROI_Vertices3.push_back(cv::Point( 720, 95));
    ROI_Vertices3.push_back(cv::Point( 710, 170));
    ROI_Vertices3.push_back(cv::Point( 570, 150));

    //ROI Junction 4
    ROI_Vertices4.push_back(cv::Point( 240, 70));
    ROI_Vertices4.push_back(cv::Point( 320, 90));
    ROI_Vertices4.push_back(cv::Point( 220, 135));
    ROI_Vertices4.push_back(cv::Point( 140, 110 ));

    timeLimit = 0;
    caseChoice = 2;

    capVideo.open("dataset1a.mp4");                  // associate the capture object to the default webcam

    if(!capVideo.isOpened()) {                 // if unsuccessful
        QMessageBox::information(this, "", "error reading video file \n\n exiting program\n");        // show error message
        exitProgram();                                  // and exit program
        return;                                         //
    }

    if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 2) {
        QMessageBox::information(this, "", "error: video file must have at least two frames \n\n exiting program\n");        // show error message
        exitProgram();                                  // and exit program
        return;
    }

    capVideo.read(imgFrame1);
    capVideo.read(imgFrame2);

    // Read the image file
    imageBlank = cv::imread("original.jpg");

    // Check for failure
    if (imageBlank.empty())
    {
        QMessageBox::information(this, "", "Could not open or find the image\n");        // show error message
        exitProgram();                                  // and exit program
        return;
    }

    chCheckForEscKey = 0;

    blnFirstFrame = true;

    frameCount = 2;

    qtimer = new QTimer(this);                          // instantiate timer
    connect(qtimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));     // associate timer to processFrameAndUpdateGUI
    qtimer->start(20);                                  // start timer, set to cycle every 20 msec (50x per sec), it will not actually cycle this often

}

// destructor ////////////////////////////////////////////////////////////////////////////
frmMain::~frmMain() {
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void frmMain::exitProgram() {
    if(qtimer->isActive()) qtimer->stop();          // if timer is running, stop timer
    QApplication::quit();                           // and exit program
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void frmMain::processFrameAndUpdateGUI() {

    /////////RESET ALL///////////////////////////////////////
    if (capVideo.get(CV_CAP_PROP_POS_FRAMES) < 10){
        if(caseChoice == 4)
            turn = 4;
        else if(caseChoice == 2)
            turn = 3;
        else if(caseChoice == 3 || caseChoice == 5)
            turn = 1;

        for(int i = 1; i < 5; i++){
            TLightsList->getEntry(i)->setTimer(80);
            TLightsList->getEntry(i)->setTimer2(0);
            TLightsList->getEntry(i)->setIsEmpty(true);
            TLightsList->getEntry(i)->setTimerExceed(false);
            TLightsList->getEntry(i)->setYellowLight(false);
            TLightsList->getEntry(i)->setTrafficGo(false);
        }
    }
    ///////////////////////////////////////////////////////

    std::vector<Blob> currentFrameBlobs;

    cv::Mat imgFrame1Copy(480, 854, CV_8UC3);
    cv::Mat imgFrame2Copy(480, 854, CV_8UC3);

    ////// ROI /////////////////////////////////////////////////////////////////
    cv::Mat mask(480, 854, CV_8UC1);
    // Create black image with the same size as the original
    for(int i=0; i<mask.cols; i++)
       for(int j=0; j<mask.rows; j++)
           mask.at<uchar>(cv::Point(i,j)) = 0;

    cv::approxPolyDP(ROI_Vertices1, ROI_Poly1, 1.0, true);
    cv::approxPolyDP(ROI_Vertices2, ROI_Poly2, 1.0, true);
    cv::approxPolyDP(ROI_Vertices3, ROI_Poly3, 1.0, true);
    cv::approxPolyDP(ROI_Vertices4, ROI_Poly4, 1.0, true);

    // Fill polygon white
    cv::fillConvexPoly(mask, &ROI_Poly1[0], ROI_Poly1.size(), 255, 8, 0);
    cv::fillConvexPoly(mask, &ROI_Poly2[0], ROI_Poly2.size(), 255, 8, 0);
    cv::fillConvexPoly(mask, &ROI_Poly3[0], ROI_Poly3.size(), 255, 8, 0);
    cv::fillConvexPoly(mask, &ROI_Poly4[0], ROI_Poly4.size(), 255, 8, 0);

    // Create new image for result storage
    //cv::Mat imageDest(480, 854, CV_8UC3);

    // Cut out ROI and store it in imageDest
    imageBlank.copyTo(imgFrame1Copy, mask);
    imgFrame2.copyTo(imgFrame2Copy, mask);

    /////////////////////////////////////////////////////////////////////////////

    cv::Mat imgDifference;
    cv::Mat imgThresh;

    cv::cvtColor(imgFrame1Copy, imgFrame1Copy, CV_BGR2GRAY);
    cv::cvtColor(imgFrame2Copy, imgFrame2Copy, CV_BGR2GRAY);

    //cv::imshow("imgGrayscale", imgFrame1Copy);

    cv::GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);
    cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);

    cv::absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);

    cv::threshold(imgDifference, imgThresh, 30, 255.0, CV_THRESH_BINARY);

    //cv::imshow("imgGaussianBlur", imgFrame1Copy);
    //cv::imshow("imgOriginal", imgFrame2Copy);
    //cv::imshow("imgThresh", imgThresh);

    cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
    cv::Mat structuringElement15x15 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));

    for (unsigned int i = 0; i < 2; i++) {
        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::erode(imgThresh, imgThresh, structuringElement9x9);
    }

    //cv::imshow("imgThresh", imgThresh);

    cv::Mat imgThreshCopy = imgThresh.clone();

    std::vector<std::vector<cv::Point> > contours;

    cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    //drawAndShowContours(imgThresh.size(), contours, "imgContours");

    std::vector<std::vector<cv::Point> > convexHulls(contours.size());

    for (unsigned int i = 0; i < contours.size(); i++) {
        cv::convexHull(contours[i], convexHulls[i]);
    }

    //drawAndShowContours(imgThresh.size(), convexHulls, "imgConvexHulls");

    for (auto &convexHull : convexHulls) {
        Blob possibleBlob(convexHull);

        if (possibleBlob.currentBoundingRect.area() > 200 &&
            possibleBlob.dblCurrentAspectRatio > 0.2 &&
            possibleBlob.dblCurrentAspectRatio < 4.0 &&
            possibleBlob.currentBoundingRect.width > 20 &&
            possibleBlob.currentBoundingRect.height > 20 &&
            possibleBlob.dblCurrentDiagonalSize > 60.0 &&
            (cv::contourArea(possibleBlob.currentContour) / (double)possibleBlob.currentBoundingRect.area()) > 0.50) {
            currentFrameBlobs.push_back(possibleBlob);
        }
    }

    //drawAndShowContours(imgThresh.size(), currentFrameBlobs, "imgCurrentFrameBlobs");

    if (blnFirstFrame == true) {
        for (auto &currentFrameBlob : currentFrameBlobs) {
            blobs.push_back(currentFrameBlob);
        }
    }
    else {
        matchCurrentFrameBlobsToExistingBlobs(blobs, currentFrameBlobs);
    }

    //drawAndShowContours(imgThresh.size(), blobs, "imgBlobs");

    imgFrame2Copy = imgFrame2.clone();          // get another copy of frame 2 since we changed the previous frame 2 copy in the processing above

    drawBlobInfoOnImage(blobs, imgFrame2Copy);

    for (int i = 1; i <= 4; i++) {
        //If car inside the parallelogram
        if(LineList->getEntry(i)->checkLineCrossed(blobs) == true){
            LineList->getEntry(i)->drawRectangle(imgFrame2Copy, SCALAR_GREEN);
            TLightsList->getEntry(i)->setIsEmpty(false);
            if (turn == i){
                if(TLightsList->getEntry(i)->getYellowLight() == false){
                        TLightsList->getEntry(i)->setTrafficGo(true);
                }
            }
        }
        //If no car inside the parallelogram
        else{
            TLightsList->getEntry(i)->setIsEmpty(true);
            LineList->getEntry(i)->drawRectangle(imgFrame2Copy, SCALAR_RED);
            TLightsList->getEntry(i)->setTrafficGo(false);
        }

        if (turn == i) {
            //Draw timer beside traffic light
            TLightsList->getEntry(i)->drawTimer(imgFrame2Copy);

            //Draw red light for the rest of the lane
            TLightsList->getEntry(i)->turnTrafficLight(imgFrame2Copy, i);

            //If timer exceeded turn to yellow
            if(TLightsList->getEntry(i)->getTimer2() >= 480){
                TLightsList->getEntry(i)->setTimer2(0);
                TLightsList->getEntry(i)->setTimer(timeLimit+32);
            }

            //Green Light Traffic Lights
            //Junction 1
            if(i == 1){
                //Minus timer if there is no car detected
                if (TLightsList->getEntry(i)->getYellowLight() == false &&
                    TLightsList->getEntry(i)->getTrafficGo() == false &&
                    (TLightsList->getEntry(2)->getIsEmpty() == false ||
                    TLightsList->getEntry(3)->getIsEmpty() == false ||
                    TLightsList->getEntry(4)->getIsEmpty() == false)) {
                        TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_GREEN);
                        TLightsList->getEntry(i)->minusTimer(1);
                }
                //Timer stays if car detected
                else if (TLightsList->getEntry(i)->getYellowLight() == false || TLightsList->getEntry(i)->getTrafficGo() == true){
                        TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_GREEN);
                        if(TLightsList->getEntry(2)->getIsEmpty() == false ||
                            TLightsList->getEntry(3)->getIsEmpty() == false ||
                            TLightsList->getEntry(4)->getIsEmpty() == false){
                            TLightsList->getEntry(i)->plusTimer2(1);
                        }
                }
            }
            //Junction 2
            else if(i == 2){
                //Minus timer if there is no car detected
                if (TLightsList->getEntry(i)->getYellowLight() == false &&
                    TLightsList->getEntry(i)->getTrafficGo() == false &&
                    (TLightsList->getEntry(1)->getIsEmpty() == false ||
                    TLightsList->getEntry(3)->getIsEmpty() == false ||
                    TLightsList->getEntry(4)->getIsEmpty() == false)) {
                        TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_GREEN);
                        TLightsList->getEntry(i)->minusTimer(1);
                }
                //Timer stays if car detected
                else if (TLightsList->getEntry(i)->getYellowLight() == false || TLightsList->getEntry(i)->getTrafficGo() == true){
                        TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_GREEN);
                        if(TLightsList->getEntry(1)->getIsEmpty() == false ||
                            TLightsList->getEntry(3)->getIsEmpty() == false ||
                            TLightsList->getEntry(4)->getIsEmpty() == false){
                            TLightsList->getEntry(i)->plusTimer2(1);
                        }
                }
            }
            //Junction 3
            else if(i == 3){
                //Minus timer if there is no car detected
                if (TLightsList->getEntry(i)->getYellowLight() == false &&
                    TLightsList->getEntry(i)->getTrafficGo() == false &&
                    (TLightsList->getEntry(1)->getIsEmpty() == false ||
                    TLightsList->getEntry(2)->getIsEmpty() == false ||
                    TLightsList->getEntry(4)->getIsEmpty() == false)) {
                        TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_GREEN);
                        TLightsList->getEntry(i)->minusTimer(1);
                }
                //Timer stays if car detected
                else if (TLightsList->getEntry(i)->getYellowLight() == false || TLightsList->getEntry(i)->getTrafficGo() == true){
                        TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_GREEN);
                        if(TLightsList->getEntry(1)->getIsEmpty() == false ||
                            TLightsList->getEntry(2)->getIsEmpty() == false ||
                            TLightsList->getEntry(4)->getIsEmpty() == false){
                            TLightsList->getEntry(i)->plusTimer2(1);
                        }
                }
            }
            //Junction 4
            else if(i == 4){
                //Minus timer if there is no car detected
                if (TLightsList->getEntry(i)->getYellowLight() == false &&
                    TLightsList->getEntry(i)->getTrafficGo() == false &&
                    (TLightsList->getEntry(1)->getIsEmpty() == false ||
                    TLightsList->getEntry(2)->getIsEmpty() == false ||
                    TLightsList->getEntry(3)->getIsEmpty() == false)) {
                        TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_GREEN);
                        TLightsList->getEntry(i)->minusTimer(1);
                }
                //Timer stays if car detected
                else if (TLightsList->getEntry(i)->getYellowLight() == false || TLightsList->getEntry(i)->getTrafficGo() == true){
                        TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_GREEN);
                        if(TLightsList->getEntry(1)->getIsEmpty() == false ||
                            TLightsList->getEntry(2)->getIsEmpty() == false ||
                            TLightsList->getEntry(3)->getIsEmpty() == false){
                            TLightsList->getEntry(i)->plusTimer2(1);
                        }
                }
            }

            //Yellow Light Traffic Lights
            if (TLightsList->getEntry(i)->getTimer() <= (timeLimit+32) && TLightsList->getEntry(i)->getTimer() > timeLimit) {
                     TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_YELLOW);
                     TLightsList->getEntry(i)->minusTimer(1);
                     TLightsList->getEntry(i)->setYellowLight(true);
            }

            //Red Light Traffic Lights
            else if (TLightsList->getEntry(i)->getTimer() <= timeLimit) {
                TLightsList->getEntry(i)->setTimer(70);
                TLightsList->getEntry(i)->setTimerExceed(false);
                TLightsList->getEntry(i)->setYellowLight(false);
                TLightsList->getEntry(i)->setTrafficGo(false);
                TLightsList->getEntry(i)->drawTrafficLight(imgFrame2Copy, SCALAR_RED);
                TLightsList->getEntry(i)->setIsEmpty(true);
                if(turn == 1){
                    if (TLightsList->getEntry(2)->getIsEmpty() == true) {
                        turn = 3;
                        if (TLightsList->getEntry(3)->getIsEmpty() == true) {
                            turn = 4;
                            if (TLightsList->getEntry(4)->getIsEmpty() == true)
                                turn = 2;
                        }
                    }
                    else
                        turn = 2;
                }
                else if(turn == 2){
                    if (TLightsList->getEntry(3)->getIsEmpty() == true) {
                        turn = 4;
                        if (TLightsList->getEntry(4)->getIsEmpty() == true) {
                            turn = 1;
                            if (TLightsList->getEntry(1)->getIsEmpty() == true)
                                turn = 3;
                        }
                    }
                    else
                        turn = 3;
                }
                else if(turn == 3){
                    if (TLightsList->getEntry(4)->getIsEmpty() == true) {
                        turn = 1;
                        if (TLightsList->getEntry(1)->getIsEmpty() == true) {
                            turn = 2;
                            if (TLightsList->getEntry(2)->getIsEmpty() == true)
                                turn = 4;
                        }
                    }
                    else
                        turn = 4;
                }
                else if(turn == 4){
                    if (TLightsList->getEntry(1)->getIsEmpty() == true) {
                        turn = 2;
                        if (TLightsList->getEntry(2)->getIsEmpty() == true) {
                            turn = 3;
                            if (TLightsList->getEntry(3)->getIsEmpty() == true)
                                turn = 1;
                        }
                    }
                    else
                        turn = 1;
                }
            }
        }
    }

    //Put text to display which case
    drawCase(imgFrame2Copy, caseChoice);

    if(caseChoice == 1){
        drawAndShowContours(imgThresh.size(), blobs, "imgBlobs");
    }

    if(caseChoice >= 2){
        QImage qimgOriginal = matToQImage(imgFrame2Copy);                         // convert from OpenCV Mat to Qt QImage

        ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));           // show images on form labels
    }


    //cv::waitKey(0);                 // uncomment this line to go frame by frame for debugging

    // now we prepare for the next iteration

    currentFrameBlobs.clear();

    imgFrame1 = imgFrame2.clone();           // move frame 1 up to where frame 2 is

    if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT) - 6) {
        capVideo.read(imgFrame2);
    }
    else {
        std::cout << "end of video\n";
        capVideo.set(CV_CAP_PROP_POS_FRAMES, 1);
    }

    blnFirstFrame = false;
    frameCount++;
    chCheckForEscKey = cv::waitKey(1);

    if (chCheckForEscKey != 27) {               // if the user did not press esc (i.e. we reached the end of the video)
        cv::waitKey(0);                         // hold the windows open to allow the "end of video" message to show
    }

    // note that if the user did press esc, we don't need to hold the windows open, we can simply let the program end which will close the windows
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void frmMain::matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs) {

    for (auto &existingBlob : existingBlobs) {

        existingBlob.blnCurrentMatchFoundOrNewBlob = false;

        existingBlob.predictNextPosition();
    }

    for (auto &currentFrameBlob : currentFrameBlobs) {

        int intIndexOfLeastDistance = 0;
        double dblLeastDistance = 100000.0;

        for (unsigned int i = 0; i < existingBlobs.size(); i++) {

            if (existingBlobs[i].blnStillBeingTracked == true) {

                double dblDistance = distanceBetweenPoints(currentFrameBlob.centerPositions.back(), existingBlobs[i].predictedNextPosition);

                if (dblDistance < dblLeastDistance) {
                    dblLeastDistance = dblDistance;
                    intIndexOfLeastDistance = i;
                }
            }
        }

        if (dblLeastDistance < currentFrameBlob.dblCurrentDiagonalSize * 0.5) {
            addBlobToExistingBlobs(currentFrameBlob, existingBlobs, intIndexOfLeastDistance);
        }
        else {
            addNewBlob(currentFrameBlob, existingBlobs);
        }

    }

    for (auto &existingBlob : existingBlobs) {

        if (existingBlob.blnCurrentMatchFoundOrNewBlob == false) {
            existingBlob.intNumOfConsecutiveFramesWithoutAMatch++;
        }

        if (existingBlob.intNumOfConsecutiveFramesWithoutAMatch >= 5) {
            existingBlob.blnStillBeingTracked = false;
        }

    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////
void frmMain::addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex) {

    existingBlobs[intIndex].currentContour = currentFrameBlob.currentContour;
    existingBlobs[intIndex].currentBoundingRect = currentFrameBlob.currentBoundingRect;

    existingBlobs[intIndex].centerPositions.push_back(currentFrameBlob.centerPositions.back());

    existingBlobs[intIndex].dblCurrentDiagonalSize = currentFrameBlob.dblCurrentDiagonalSize;
    existingBlobs[intIndex].dblCurrentAspectRatio = currentFrameBlob.dblCurrentAspectRatio;

    existingBlobs[intIndex].blnStillBeingTracked = true;
    existingBlobs[intIndex].blnCurrentMatchFoundOrNewBlob = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void frmMain::addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs) {

    currentFrameBlob.blnCurrentMatchFoundOrNewBlob = true;

    existingBlobs.push_back(currentFrameBlob);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
double frmMain::distanceBetweenPoints(cv::Point point1, cv::Point point2) {

    int intX = abs(point1.x - point2.x);
    int intY = abs(point1.y - point2.y);

    return(sqrt(pow(intX, 2) + pow(intY, 2)));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void frmMain::drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName) {
    cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);

    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);

    QImage qimgContours = matToQImage(image);                         // convert from OpenCV Mat to Qt QImage

    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgContours));           // show images on form labels
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void frmMain::drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName) {

    cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);

    std::vector<std::vector<cv::Point> > contours;

    for (auto &blob : blobs) {
        if (blob.blnStillBeingTracked == true) {
            contours.push_back(blob.currentContour);
        }
    }

    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);

    QImage qimgContours = matToQImage(image);                         // convert from OpenCV Mat to Qt QImage

    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgContours));           // show images on form labels
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void frmMain::drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy) {

    for (unsigned int i = 0; i < blobs.size(); i++) {

        if (blobs[i].blnStillBeingTracked == true) {
            cv::rectangle(imgFrame2Copy, blobs[i].currentBoundingRect, SCALAR_RED, 2);

            int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
            double dblFontScale = blobs[i].dblCurrentDiagonalSize / 60.0;
            int intFontThickness = (int)std::round(dblFontScale * 1.0);

            //cv::putText(imgFrame2Copy, std::to_string(i), blobs[i].centerPositions.back(), intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void frmMain::drawCase(cv::Mat &imgFrame2Copy, int choice) {

    std::string choice2 = "Case 1: Normal case";
    std::string choice3 = "Case 2: Skip lane";
    std::string choice4 = "Case 3: Extended time";
    std::string choice5 = "Case 4: No car around";

    int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
    double dblFontScale = 0.7;
    int intFontThickness = (int)std::round(dblFontScale * 3);
    cv::Point textPos;
    textPos.x = 300;
    textPos.y = 30;

    if (choice == 2) {
        cv::putText(imgFrame2Copy, choice2, textPos, intFontFace, dblFontScale, SCALAR_WHITE, intFontThickness);
    }
    else if (choice == 3) {
        cv::putText(imgFrame2Copy, choice3, textPos, intFontFace, dblFontScale, SCALAR_WHITE, intFontThickness);
    }
    else if (choice == 4) {
        cv::putText(imgFrame2Copy, choice4, textPos, intFontFace, dblFontScale, SCALAR_WHITE, intFontThickness);
    }
    else if (choice == 5) {
        cv::putText(imgFrame2Copy, choice5, textPos, intFontFace, dblFontScale, SCALAR_WHITE, intFontThickness);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
QImage frmMain::matToQImage(cv::Mat mat) {
    if(mat.channels() == 1) {                                   // if 1 channel (grayscale or black and white) image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // return QImage
    } else if(mat.channels() == 3) {                            // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB);                     // flip colors
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // return QImage
    } else {
        qDebug() << "in openCVMatToQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage();        // return a blank QImage if the above did not work
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void frmMain::on_btn1_clicked(){
    caseChoice = 1;
}

void frmMain::on_btn2_clicked(){
    if(caseChoice == 1 && checkCase2 == true){
        caseChoice = 2;
    }
    else{
        checkCase2 = true;
        checkCase3 = false;
        checkCase4 = false;
        checkCase5 = false;
        imageBlank = cv::imread("original.jpg");
        caseChoice = 2;
        capVideo.open("dataset1a.mp4");
    }
}

void frmMain::on_btn3_clicked(){
    if(caseChoice == 1 && checkCase3 == true){
        caseChoice = 3;
    }
    else{
        checkCase2 = false;
        checkCase3 = true;
        checkCase4 = false;
        checkCase5 = false;
        imageBlank = cv::imread("original.jpg");
        caseChoice = 3;
        capVideo.open("dataset1b.mp4");
        turn = 1;
    }
}

void frmMain::on_btn4_clicked()
{
    if(caseChoice == 1 && checkCase4 == true){
        caseChoice = 4;
    }
    else{
        checkCase2 = false;
        checkCase3 = false;
        checkCase4 = true;
        checkCase5 = false;
        imageBlank = cv::imread("original2.jpg");
        caseChoice = 4;
        capVideo.open("dataset1c.mp4");
    }
}

void frmMain::on_btn5_clicked(){
    if(caseChoice == 1 && checkCase5 == true){
        caseChoice = 5;
    }
    else{
        checkCase2 = false;
        checkCase3 = false;
        checkCase4 = false;
        checkCase5 = true;
        imageBlank = cv::imread("original2.jpg");
        caseChoice = 5;
        capVideo.open("dataset1d.mp4");
    }
}

void frmMain::on_btn6_clicked(){
    if(caseChoice == 1 && checkCase2 == true){
        caseChoice = 2;
    }
    else{
        checkCase2 = true;
        checkCase3 = false;
        checkCase4 = false;
        checkCase5 = false;
        imageBlank = cv::imread("original.jpg");
        caseChoice = 2;
        capVideo.open("dataset1a.mp4");
    }
}
