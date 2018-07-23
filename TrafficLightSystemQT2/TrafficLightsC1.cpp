#include "TrafficLightsC1.h"

TrafficLightsC1::TrafficLightsC1(int junction)
{
	carPassed = false;
	yellowLight = false;
    timer = 80;
    timer2 = 0;
    trafficGo = false;
	isEmpty = true;
    timerExceed = false;
    circleRadius = 15;

    circlePosition1.x = 240;
    circlePosition1.y = 260;
    textPosition1.x = 220;
    textPosition1.y = 295;
    timerPosition1.x = 270;
    timerPosition1.y = 250;

    circlePosition2.x = 660;
    circlePosition2.y = 210;
    textPosition2.x = 640;
    textPosition2.y = 245;
    timerPosition2.x = 615;
    timerPosition2.y = 220;

    circlePosition3.x = 560;
    circlePosition3.y = 80;
    textPosition3.x = 540;
    textPosition3.y = 115;
    timerPosition3.x = 585;
    timerPosition3.y = 90;

    circlePosition4.x = 280;
    circlePosition4.y = 140;
    textPosition4.x = 260;
    textPosition4.y = 175;
    timerPosition4.x = 305;
    timerPosition4.y = 150;

	if (junction == 1) {
        circlePosition.x = circlePosition1.x;
        circlePosition.y = circlePosition1.y;
        textPosition.x = textPosition1.x + 7;
        textPosition.y = textPosition1.y;
        timerPosition.x = timerPosition1.x;
        timerPosition.y = timerPosition1.y;
	}
	else if (junction == 2) {
        circlePosition.x = circlePosition2.x;
        circlePosition.y = circlePosition2.y;
        textPosition.x = textPosition2.x + 7;
        textPosition.y = textPosition2.y;
        timerPosition.x = timerPosition2.x;
        timerPosition.y = timerPosition2.y;
	}
	else if (junction == 3) {
        circlePosition.x = circlePosition3.x;
        circlePosition.y = circlePosition3.y;
        textPosition.x = textPosition3.x + 7;
        textPosition.y = textPosition3.y;
        timerPosition.x = timerPosition3.x;
        timerPosition.y = timerPosition3.y;

	}
	else if (junction == 4) {
        circlePosition.x = circlePosition4.x;
        circlePosition.y = circlePosition4.y;
        textPosition.x = textPosition4.x + 7;
        textPosition.y = textPosition4.y;
        timerPosition.x = timerPosition4.x;
        timerPosition.y = timerPosition4.y;
	}

}

void TrafficLightsC1::drawEmpty(cv::Mat &imgFrame2Copy, cv::Scalar color)
{
    /*
	std::string choiceCar = "CAR";
	std::string choiceEmpty = "EMPTY";
	int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
    double dblFontScale = 0.5;
	int intFontThickness = (int)std::round(dblFontScale * 3);

	if (color == SCALAR_GREEN) {
		cv::putText(imgFrame2Copy, choiceCar, textPositionEmpty, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
	}
	else if (color == SCALAR_RED) {
		cv::putText(imgFrame2Copy, choiceEmpty, textPositionEmpty, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
	}
    */
}

void TrafficLightsC1::turnTrafficLight(cv::Mat &imgFrame2Copy, int &turn){
	std::string choiceStop = "STOP";
    std::string timerText = "0";

	int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
    double dblFontScale = 0.5;
    double dblFontScale2 = 0.7;
    int intFontThickness = (int)std::round(dblFontScale * 3);

	if (turn == 1) {
        cv::circle(imgFrame2Copy, circlePosition2, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition2, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition2, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
        cv::circle(imgFrame2Copy, circlePosition3, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition3, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition3, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
        cv::circle(imgFrame2Copy, circlePosition4, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition4, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition4, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
	}
	else if (turn == 2) {
        cv::circle(imgFrame2Copy, circlePosition1, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition1, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition1, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
        cv::circle(imgFrame2Copy, circlePosition3, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition3, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition3, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
        cv::circle(imgFrame2Copy, circlePosition4, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition4, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition4, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
	}
	else if (turn == 3) {
        cv::circle(imgFrame2Copy, circlePosition1, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition1, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition1, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
        cv::circle(imgFrame2Copy, circlePosition2, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition2, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition2, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
        cv::circle(imgFrame2Copy, circlePosition4, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition4, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition4, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
	}
	else if (turn == 4) {
        cv::circle(imgFrame2Copy, circlePosition1, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition1, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition1, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
        cv::circle(imgFrame2Copy, circlePosition2, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition2, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition2, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
        cv::circle(imgFrame2Copy, circlePosition3, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition3, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
        cv::putText(imgFrame2Copy, timerText, timerPosition3, intFontFace, dblFontScale2, SCALAR_RED, intFontThickness);
	}
}

void TrafficLightsC1::drawTrafficLight(cv::Mat &imgFrame2Copy, cv::Scalar color) {

	std::string choiceGo = "GO";
	std::string choiceSlow = "SLOW";
	std::string choiceStop = "STOP";

	int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
    double dblFontScale = 0.5;
	int intFontThickness = (int)std::round(dblFontScale * 3);


	if (color == SCALAR_GREEN) {
        cv::circle(imgFrame2Copy, circlePosition, circleRadius, SCALAR_GREEN, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceGo, textPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
	}
	else if (color == SCALAR_YELLOW) {
        cv::circle(imgFrame2Copy, circlePosition, circleRadius, SCALAR_YELLOW, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceSlow, textPosition, intFontFace, dblFontScale, SCALAR_YELLOW, intFontThickness);
	}
	else if (color == SCALAR_RED) {
        cv::circle(imgFrame2Copy, circlePosition, circleRadius, SCALAR_RED, CV_FILLED, 8, 0);
		cv::putText(imgFrame2Copy, choiceStop, textPosition, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
	}
}

void TrafficLightsC1::drawTimer(cv::Mat &imgFrame2Copy){
    std::string timeText[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11",
                              "12", "13", "14", "15", "16", "17", "18", "19", "20"};

    int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
    double dblFontScale = 0.7;
    int intFontThickness = (int)std::round(dblFontScale * 3);

    if(timer >= 160 && timer <= 176){
        cv::putText(imgFrame2Copy, timeText[11], timerPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
    }
    else if(timer > 144 && timer <= 160){
        cv::putText(imgFrame2Copy, timeText[10], timerPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
    }
    else if(timer > 128 && timer <= 144){
        cv::putText(imgFrame2Copy, timeText[9], timerPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
    }
    else if(timer > 112 && timer <= 128){
        cv::putText(imgFrame2Copy, timeText[8], timerPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
    }
    else if(timer > 96 && timer <= 112){
        cv::putText(imgFrame2Copy, timeText[7], timerPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
    }
    else if(timer > 80 && timer <= 96){
        cv::putText(imgFrame2Copy, timeText[6], timerPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
    }
    else if(timer > 64 && timer <= 80){
        cv::putText(imgFrame2Copy, timeText[5], timerPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
    }
    else if(timer > 48 && timer <= 64){
        cv::putText(imgFrame2Copy, timeText[4], timerPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
    }
    else if(timer > 32 && timer <= 48){
        cv::putText(imgFrame2Copy, timeText[3], timerPosition, intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
    }
    else if(timer > 16 && timer <= 32){
        cv::putText(imgFrame2Copy, timeText[2], timerPosition, intFontFace, dblFontScale, SCALAR_YELLOW, intFontThickness);
    }
    else if(timer > 0 && timer <= 16){
        cv::putText(imgFrame2Copy, timeText[1], timerPosition, intFontFace, dblFontScale, SCALAR_YELLOW, intFontThickness);
    }
    else if(timer <= 0){
        cv::putText(imgFrame2Copy, timeText[0], timerPosition, intFontFace, dblFontScale, SCALAR_RED, intFontThickness);
    }
}

bool TrafficLightsC1::getCarPassed() {
	return carPassed;
}

bool TrafficLightsC1::getYellowLight() {
	return yellowLight;
}

int TrafficLightsC1::getTimer() {
	return timer;
}

int TrafficLightsC1::getTimer2() {
    return timer2;
}

bool TrafficLightsC1::getTrafficGo() {
	return trafficGo;
}

bool TrafficLightsC1::getIsEmpty() {
	return isEmpty;
}

int TrafficLightsC1::getCirclePositionX() {
	return circlePosition.x;
}

int TrafficLightsC1::getCirclePositionY() {
	return circlePosition.y;
}

bool TrafficLightsC1::getTimerExceed() {
    return timerExceed;
}

void TrafficLightsC1::setCarPassed(bool carPassed) {
	this->carPassed = carPassed;
}

void TrafficLightsC1::setYellowLight(bool yellowLight) {
	this->yellowLight = yellowLight;
}

void TrafficLightsC1::minusTimer(int timer) {
	this->timer -= timer;
}

void TrafficLightsC1::plusTimer(int timer) {
	this->timer += timer;
}

void TrafficLightsC1::setTimer(int timer) {
	this->timer = timer;
}

void TrafficLightsC1::plusTimer2(int timer2) {
    this->timer2 += timer2;
}

void TrafficLightsC1::setTimer2(int timer2) {
    this->timer2 = timer2;
}

void TrafficLightsC1::setTrafficGo(bool trafficGo) {
	this->trafficGo = trafficGo;
}

void TrafficLightsC1::setIsEmpty(bool isEmpty) {
	this->isEmpty = isEmpty;
}

void TrafficLightsC1::setTimerExceed(bool timerExceed) {
    this->timerExceed = timerExceed;
}
