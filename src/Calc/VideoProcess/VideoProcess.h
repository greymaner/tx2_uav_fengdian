//
// Created by askariz on 11/14/18.
//

#ifndef TX2_VIDEO_H
#define TX2_VIDEO_H

#include <opencv2/opencv.hpp>
#include "../../Utils/threadexchangedata.h"
class VideoProcess {
private:
    ThreadExchangeData * _data;
    cv::VideoCapture *_cap;

public:
    VideoProcess(ThreadExchangeData* data);
    void loop();
    bool init(void);
    bool _threadshouldexit;
    double getMinEnclosingTriangle(std::vector<cv::Point> &pts, cv::Mat img, int imgWidth, int imgHeight);
    double GetRotateAngle(cv::Mat frame, bool BACA, int threhold_method);
    void  BrightnessAndContrastAuto(const cv::Mat &src, cv::Mat &dst, float clipHistPercent);
    void labHarrisAngle(cv::Mat frame,double* ang,double& res);

    cv::Mat convertTo3Channels( cv::Mat binImg);
};


#endif //TX2_VIDEO_H
