/*****************************************************/
/** @copyright    2018 Alex Sommer All rights reserved.
 *     @author    Alex Sommer
 *    @version    1.0
 *       @date    23.04.18
 *****************************************************/

#ifndef THESIS_TESTCALC_H
#define THESIS_TESTCALC_H

#include <chrono>
#include <thread>
#include <Eigen/Dense>
#include "../Utils/threadexchangedata.h"
#include "VideoProcess/VideoProcess.h"

namespace TestCalc
{
    /**
     * Example mech changing calculation function done concurrently in
     * a second thread, while GUI is running on another thread.
     * @param test
     */
    void foo(ThreadExchangeData* test) {
        Eigen::Matrix3Xf verts;
        verts.resize(3, 8);
        Eigen::Matrix3Xi indices;
        indices.resize(3, 12);
        indices.col( 0) << 0, 1, 3;
        indices.col( 1) << 3, 2, 1;
        indices.col( 2) << 3, 2, 6;
        indices.col( 3) << 6, 7, 3;
        indices.col( 4) << 7, 6, 5;
        indices.col( 5) << 5, 4, 7;
        indices.col( 6) << 4, 5, 1;
        indices.col( 7) << 1, 0, 4;
        indices.col( 8) << 4, 0, 3;
        indices.col( 9) << 3, 7, 4;
        indices.col(10) << 5, 6, 2;
        indices.col(11) << 2, 1, 5;
        verts.col(0) << -1,  1,  1;
        verts.col(1) << -1,  1, -1;
        verts.col(2) <<  1,  1, -1;
        verts.col(3) <<  1,  1,  1;
        verts.col(4) << -1, -1,  1;
        verts.col(5) << -1, -1, -1;
        verts.col(6) <<  1, -1, -1;
        verts.col(7) <<  1, -1,  1;

        test->vertices = &verts;
        test->indices = &indices;
        test->newData = true;

        // Crashes when thread closes too fast
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Do some calculations and update mech while GUI is running
    }

    double calcAngle(std::vector<double> angle)
    {
        double mean_angle=0;
        double sigma =0;
        std::vector<double> angle_filter;

        mean_angle = std::accumulate(std::begin(angle), std::end(angle), 0.0)/angle.size();
        for (int j = 0; j < angle.size(); ++j) {
//                        std::cout<<angle.at(j)<<std::endl;
            sigma += std::pow(angle.at(j)-mean_angle,2);
        }
        sigma = std::sqrt(sigma / angle.size());

        for (int i = 0; i < angle.size(); ++i) {
            if(std::abs(angle.at(i)-mean_angle) <= 2*sigma){
//                            std::cout<<"-----"<<angle.at(i)<<"-----"<<std::endl;
                angle_filter.push_back(angle.at(i));
            }
        }
        mean_angle = std::accumulate(std::begin(angle_filter), std::end(angle_filter), 0.0)/angle_filter.size();
        return mean_angle;
    }
    /*
     * start calc rotate angle
     */
    static int process(ThreadExchangeData *data) {
        VideoProcess *videoProcess = new VideoProcess(data);
        std::cout << "start calc" << std::endl;

        std::vector<double> angle_tri;
        std::vector<double> angle2_ostu;
        std::vector<double> angle3_lab;
        std::vector<double> angle4_hsv;

//        double mean_angle[3];

        double mean_yaw = 0;
//        double mean_angle = 0;
//        double sigma = 0;
        bool condition = true;
        while (condition){

            if(!data->calcFrame.empty()) {
                std::cout << "start calc -----------" <<std::endl;
//                //数组清0
//                for (int i = 0; i < 3; ++i) {
//                    data->mean_angle[i] = 0;
//                }
                //角度计算(4种方法)
                angle_tri.push_back(videoProcess->GetRotateAngle(data->calcFrame.front(), false,1)); //不增强亮度和对比度+采用三角阈值化方法
                angle2_ostu.push_back(videoProcess->GetRotateAngle(data->calcFrame.front(), false,2));//不增强亮度和对比度+采用OTSU阈值化方法
                angle3_lab.push_back(videoProcess->GetRotateAngle(data->calcFrame.front(), false,3));//不增强亮度和对比度+采用Lab颜色空间方法
                angle4_hsv.push_back(videoProcess->GetRotateAngle(data->calcFrame.front(), false,4));//不增强亮度和对比度+采用hsv和xyz颜色空间
                //pop掉处理完的frame
                data->calcFrame.pop();
                //计算完成后
                if(angle_tri.size() == data->frame_num)
                {
                    mean_yaw = std::accumulate(std::begin(data->yaw), std::end(data->yaw), 0.0)/data->yaw.size();
                    data->mean_angle[0]=calcAngle(angle_tri);
                    data->angle = data->mean_angle[0] + (mean_yaw * 180.0 / CV_PI);//  ???
                    data->mean_angle[1]=calcAngle(angle2_ostu) + (mean_yaw * 180.0 / CV_PI);
                    data->mean_angle[2]=calcAngle(angle3_lab) + (mean_yaw * 180.0 / CV_PI);
                    data->mean_angle[3]=calcAngle(angle4_hsv) + (mean_yaw * 180.0 / CV_PI);
//                    mean_angle = std::accumulate(std::begin(angle), std::end(angle), 0.0)/angle.size();
//                    for (int j = 0; j < angle.size(); ++j) {
////                        std::cout<<angle.at(j)<<std::endl;
//                        sigma += std::pow(angle.at(j)-mean_angle,2);
//                    }
//                    sigma = std::sqrt(sigma / angle.size());
//
//                    for (int i = 0; i < angle.size(); ++i) {
//                        if(std::abs(angle.at(i)-mean_angle) <= 2*sigma){
////                            std::cout<<"-----"<<angle.at(i)<<"-----"<<std::endl;
//                            angle_filter.push_back(angle.at(i));
//                        }
//                    }
//                    mean_angle = std::accumulate(std::begin(angle_filter), std::end(angle_filter), 0.0)/angle_filter.size();
//                    std::cout<<"---mean_angle--"<<mean_angle<<"-----"<<std::endl;

//                    mean_yaw=2.9;

//                    std::cout<<"---data->angle--"<<data->angle<<"-----"<<std::endl;
//                    data->angle = mean_yaw;
//                    data->angle = mean_angle;
                    data->calc_over = true;
                    data->start_calc = false;
                    mean_yaw = 0;
//                    mean_angle = 0;
//                    sigma = 0;
                    /*
                     * 清空vector变量
                     */
                    angle_tri.clear(); //triangle
                    angle2_ostu.clear();//otsu
                    angle3_lab.clear();//labyanse空间
                    angle4_hsv.clear();
//                    angle_filter.clear();//滤波后的角度

//                    cv::Mat resMat(1000,1000,CV_8UC3,cv::Scalar(0,0,0));
//                    char str[256],str2[256];
//                    sprintf(str, "%f", sigma);
//                    sprintf(str2, "%f", data->angle);
//                    std::string angle2str = str;
//                    std::string angle2str2 = str2;
//                    int font_face = cv::FONT_HERSHEY_COMPLEX;
//                    double font_scale = 4;
//                    int thickness = 1;
//                    cv::putText(resMat, angle2str2, cv::Point2f(10, resMat.rows / 2 - 200), font_face, font_scale, cv::Scalar(255,255,255), thickness, 8, 0);
//                    cv::putText(resMat, angle2str, cv::Point2f(10, resMat.rows / 2), font_face, font_scale, cv::Scalar(255,255,255), thickness, 8, 0);
//
//                    data->result = resMat;
//
//                    cv::destroyWindow("resMat");
//                    cv::destroyWindow("BrightnessAndContrastAuto");
//                    cv::destroyWindow("threshold");
//                    cv::destroyWindow("result");
                }
            }
        }
    }
}







#endif //THESIS_TESTCALC_H
