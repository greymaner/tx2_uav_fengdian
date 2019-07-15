/*****************************************************/
/** @copyright    2018 Alex Sommer All rights reserved.
 *     @author    Alex Sommer
 *    @version    1.0
 *       @date    24.04.18
 *****************************************************/

#ifndef THESIS_THREADEXCHANGEDATA_H
#define THESIS_THREADEXCHANGEDATA_H

#include <Eigen/Dense>
#include <queue>
#include <opencv2/opencv.hpp>
/**
 * Data that needs to be exchanged between threads
 * try to keep it a minimum amount to prevent from synchronization errors
 */
struct ThreadExchangeData {
    // Vertice to be drawn
    Eigen::Matrix3Xf* vertices;
    // Indice data
    Eigen::Matrix3Xi* indices;
    // Weather there is new data to draw
    bool newData;
    //---------------
    bool start_calc = true;
    float angle;
    bool calc_over = false;
    std::vector<float> yaw={0};
    time_t startTime=0;
    time_t endTime=0;
    std::queue<cv::Mat> calcFrame;
    std::queue<cv::Mat> threholdFrame;
    std::queue<cv::Mat> threholdFrame2;
    std::queue<cv::Mat> threholdFrame3;
    std::queue<cv::Mat> threholdFrame4;
    const int frame_num = 50;
    double mean_angle[4]={0};
    cv::Mat result;
    //---------------
    std::queue<cv::Mat> frame;
};

#endif //THESIS_THREADEXCHANGEDATA_H
