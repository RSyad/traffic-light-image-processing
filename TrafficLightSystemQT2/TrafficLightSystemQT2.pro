#-------------------------------------------------
#
# Project created by QtCreator 2018-04-30T07:51:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrafficLightSystemQT2
TEMPLATE = app


SOURCES += main.cpp\
        frmmain.cpp \
    Blob.cpp \
    LineC1.cpp \
    LineC2.cpp \
    TrafficLightsC1.cpp \
    TrafficLightsC2.cpp

HEADERS  += frmmain.h \
    Blob.h \
    LineC1.h \
    LineC2.h \
    LineInterface.h \
    LinkedList.h \
    Node.h \
    TrafficLightsC1.h \
    TrafficLightsC2.h \
    TrafficLightsInterface.h \
    ui_frmmain.h

FORMS    += frmmain.ui

INCLUDEPATH += C:\\OpenCV-3.3.1\\opencv\\build\\include
LIBS += -LC:\\OpenCV-3.3.1\\mybuild\\lib\\Debug \
    -lopencv_calib3d331d \
    -lopencv_core331d \
    -lopencv_dnn331d \
    -lopencv_features2d331d \
    -lopencv_flann331d \
    -lopencv_highgui331d \
    -lopencv_imgcodecs331d \
    -lopencv_imgproc331d \
    -lopencv_ml331d \
    -lopencv_objdetect331d \
    -lopencv_photo331d \
    -lopencv_shape331d \
    -lopencv_stitching331d \
    -lopencv_superres331d \
    -lopencv_ts331d \
    -lopencv_video331d \
    -lopencv_videoio331d \
    -lopencv_videostab331d
