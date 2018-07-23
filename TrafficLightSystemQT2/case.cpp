void chooseCase(int option){
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

    timeLimit = 100;
    turn = 2;

    capVideo.open("dataset1.mp4");                  // associate the capture object to the default webcam

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

    frameCount = 2;                               // start timer, set to cycle every 20 msec (50x per sec), it will not actually cycle this often
}
