#include "LineC1.h"



LineC1::LineC1(int junction)
{
	if (junction == 1) {
        id = 1;

        contour.push_back(cv::Point( 100, 280 ));
        contour.push_back(cv::Point( 220, 330));

        contour.push_back(cv::Point( 70, 420));
        contour.push_back(cv::Point( 1, 350));

        pts = (const cv::Point*) cv::Mat(contour).data;
        npts = cv::Mat(contour).rows;
	}
	else if (junction == 2) {
		id = 2;

        contour.push_back(cv::Point( 660, 270 ));
        contour.push_back(cv::Point( 820, 320));

        contour.push_back(cv::Point( 780, 460));
        contour.push_back(cv::Point( 550, 400));

        pts = (const cv::Point*) cv::Mat(contour).data;
        npts = cv::Mat(contour).rows;

	}
	else if (junction == 3) {
		id = 3;
        contour.push_back(cv::Point( 630, 85 ));
        contour.push_back(cv::Point( 720, 95));

        contour.push_back(cv::Point( 710, 150));
        contour.push_back(cv::Point( 570, 130));

        pts = (const cv::Point*) cv::Mat(contour).data;
        npts = cv::Mat(contour).rows;
	}
	else if (junction == 4) {
        id = 4;
        contour.push_back(cv::Point( 240, 70));
        contour.push_back(cv::Point( 320, 90));

        contour.push_back(cv::Point( 220, 135));
        contour.push_back(cv::Point( 140, 110 ));

        pts = (const cv::Point*) cv::Mat(contour).data;
        npts = cv::Mat(contour).rows;
	}

}

void LineC1::drawRectangle(cv::Mat &imgFrame, cv::Scalar color){
	if(color == SCALAR_GREEN)
        cv::polylines(imgFrame, &pts, &npts, 1, true, SCALAR_GREEN, 3);
	else if(color == SCALAR_RED)
        cv::polylines(imgFrame, &pts, &npts, 1, true, SCALAR_RED, 3);
}

bool LineC1::checkLineCrossed(std::vector<Blob> &blobs) {
	bool blnAtLeastOneBlobCrossedTheLine = false;

	for (auto blob : blobs) {

		if (blob.blnStillBeingTracked == true && blob.centerPositions.size() >= 2) {
			int prevFrameIndex = (int)blob.centerPositions.size() - 2;
            int currFrameIndex = (int)blob.centerPositions.size() - 1;
            /*
            std::cout << "Center Positions Prev Index Y:";
            std::cout << blob.centerPositions[prevFrameIndex].y;
            std::cout << "\n";
            std::cout << "Center Positions Curr Index Y:";
            std::cout << blob.centerPositions[currFrameIndex].y;
            std::cout << "\n";
            std::cout << "Center Positions Prev Index X:";
            std::cout << blob.centerPositions[prevFrameIndex].x;
            std::cout << "\n";
            std::cout << "Center Positions Curr Index X:";
            std::cout << blob.centerPositions[prevFrameIndex].x;
            std::cout << "\n";
            std::cout << "\n";
            std::cout << "ContourX 0:";
            std::cout << contour[0].x;
            std::cout << "\n";
            std::cout << "ContourY 0:";
            std::cout << contour[0].y;
            std::cout << "\n";
            std::cout << "ContourX 1:";
            std::cout << contour[1].x;
            std::cout << "\n";
            std::cout << "ContourY 1:";
            std::cout << contour[1].y;
            std::cout << "\n";
            std::cout << "ContourX 2:";
            std::cout << contour[2].x;
            std::cout << "\n";
            std::cout << "ContourY 2:";
            std::cout << contour[2].y;
            std::cout << "\n";
            std::cout << "ContourX 3:";
            std::cout << contour[3].x;
            std::cout << "\n";
            std::cout << "ContourY 3:";
            std::cout << contour[3].y;
            std::cout << "\n";
            std::cout << "\n";
            */

            if (blob.centerPositions[prevFrameIndex].x > contour[3].x &&
                blob.centerPositions[currFrameIndex].x <= contour[1].x &&
                blob.centerPositions[prevFrameIndex].y > contour[0].y &&
                blob.centerPositions[currFrameIndex].y <= contour[2].y)
                {
                    return blnAtLeastOneBlobCrossedTheLine = true;
                }
        }
    }
}
