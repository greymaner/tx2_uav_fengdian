//
// Created by askariz on 11/14/18.
//

#include "VideoProcess.h"
#include <algorithm>
#include <time.h>

std::string get_tegra_pipeline(int width, int height, int fps) {
    return "v4l2src device=/dev/video0 ! video/x-raw,width=1920,height=1080,format=(string)I420 ! nvvidconv ! videoconvert ! video/x-raw, format=(string)BGR ! appsink drop=true sync=false";
//        return "filesrc location=/home/nvidia/a.mp4 ! decodebin ! videoconvert ! appsink sync=false";
//        return "//home//nvidia//saveVideo.avi";

}



VideoProcess::VideoProcess(ThreadExchangeData *data):_data(data),_threadshouldexit (false){
}

bool VideoProcess::init() {
    std::cout << "opencv build varibles" << std::endl;
    std::cout << cv::getBuildInformation() << std::endl;

    std::string pipeline = get_tegra_pipeline(1920,1080,60);
    std::cout << "Using pipeline :" << pipeline  << std::endl;

    // open gstreamer capture
//    _cap = new cv::VideoCapture("/home/mmc-wy/Videos/chenzhou-DJI/DJI_0013.MOV");
    _cap = new cv::VideoCapture(1);
    // open normal camera

//    _cap = new cv::VideoCapture(pipeline,cv::CAP_GSTREAMER);
//    _cap->set(cv::CV_CAP_PROP_BUFFERSIZE,1);
//    _cap = new cv::VideoCapture(1);
    if(!_cap->isOpened()){
        std::cout << "Open Video Capture error !" << std::endl;
        return false;
    } else
    {
        std::cout << "Open Video Capture ok !" << std::endl;
        return true;
    }

}

void VideoProcess::loop() {
    cv::Mat frame;
    double mean_yaw = 0;
    int count = 1;
    int count_frame =0;
    float angle_sum=0;
    std::vector<double> angle;

    while(!_threadshouldexit){
       if(_cap->isOpened()){
        _cap->read(frame);
        if(frame.data){

            _data->frame.push(frame);
            std::cout << "push frame queue size:" << _data->frame.size() << std::endl;

            if(_data->start_calc){
                if(count_frame < _data->frame_num){
                    _data->calcFrame.push(frame);
                    std::cout << count_frame <<std::endl;
                    count_frame++;
                }
            } else{

                count_frame=0;
            }

            }
        }
    }
}


void VideoProcess::labHarrisAngle(cv::Mat frame,double* ang,double& res)
{
    //Lab
    cv::Mat gray;
    cv::Mat Lab;
    cv::Mat mask;
    cv::Mat open1;
    cv::cvtColor(frame,gray,CV_BGR2GRAY);
    cv::cvtColor(frame,Lab,CV_BGR2Lab);
    //掩模
    cv::inRange(Lab,cv::Scalar(0,138,120),cv::Scalar(255,170,135),mask);
    //开运算
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(31,31));
    cv::morphologyEx(mask,open1,cv::MORPH_OPEN,element);
    //harris角点提取
    gray.convertTo(gray,CV_32FC1);
    cv::Mat corners;
    cv::cornerHarris(gray,corners,5,5,0.04);
    //亚像素角点
    //亚像素角点
    double s = 0.0;
    cv::max(corners,s);
    cv::threshold(corners,corners,0.01*s,255,0);
    corners.convertTo(corners,CV_8UC1);
    cv::Mat labels,stats,centroids;
//    cv::connectedComponentsWithStats()
    cv::connectedComponentsWithStats(corners,labels,stats,centroids);
    centroids.convertTo(centroids,CV_32FC1);
    cv::cornerSubPix(open1,centroids,cv::Size(5,5),cv::Size(-1,-1),cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,100,0.001));
    //
    double l = 0.0;
    double maxDis = 0.0;

    cv::Point2f p1;
    cv::Point2f p2;

    double angle ,angle1 , angle2;

    for (int i = 0; i < centroids.size[0]; ++i) {
        float *data = centroids.ptr<float>(i);
        for (int j = 0; j < centroids.size[1]; ++j) {
            float *data2 = centroids.ptr<float>(i);

            l = std::sqrt(std::pow(data[0]-data2[0],2)+std::pow(data[1]-data2[1],2));
            if(l > maxDis){
                maxDis = l;
                p1.x = data[0];
                p1.y = data[1];
                p2.x = data2[0];
                p2.y = data2[1];
            }
        }
    }

    angle = std::abs(p1.y - p2.y) / std::abs(p1.x - p2.x);

    if((p1.y - p2.y)*(p1.x - p2.x)<0)
    {
        angle1 = -atan(angle) * 180 / CV_PI;
        angle2 = 180 -atan(angle) * 180 / CV_PI;
    }
    else
    {
        angle1 = atan(angle) * 180 / CV_PI - 180;
        angle2 = atan(angle) * 180 / CV_PI;
    }
    ang[0] = angle1;
    ang[1] = angle2;

    //计算叶片偏转角度
}





double VideoProcess::GetRotateAngle(cv::Mat frame, bool BACA = false, int threhold_method=2)
{
//    cv::inRange(bw,cv::Scalar(126,120,105),cv::Scalar(255,128,128),bw);

    cv::Mat bw = frame;
    int imgWidth = frame.cols;
    int imgHeight = frame.rows;
    std::cout<<imgWidth <<"   "<<imgHeight<<std::endl;

    if(BACA)
    {
        BrightnessAndContrastAuto(bw,bw,1);
    }


    if(threhold_method == 1)
    {
        cv::cvtColor(bw,bw,cv::COLOR_BGR2GRAY);
        cv::threshold(bw,bw,0,255, CV_THRESH_BINARY | CV_THRESH_TRIANGLE);
        cv::medianBlur(bw,bw,7);
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(11,11));
        cv::dilate(bw,bw,element);
    }
    else if(threhold_method == 2)
    {
        cv::cvtColor(bw,bw,cv::COLOR_BGR2GRAY);
        cv::threshold(bw,bw,155,255, 8);
        cv::medianBlur(bw,bw,7);
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(11,11));
        cv::dilate(bw,bw,element);
    }
    else if(threhold_method == 3)
    {
        cv::cvtColor(bw,bw,CV_BGR2Lab);
        cv::inRange(bw,cv::Scalar(126,120,105),cv::Scalar(255,128,128),bw);
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(5,5));
        cv::dilate(bw,bw,kernel);
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(9,9));
        cv::morphologyEx(bw,bw,cv::MORPH_OPEN,element);
    }
    else if(threhold_method == 4)
    {
        // HSV  XYZ
        cv::Mat hsv,xyz;
        cv::cvtColor(bw,hsv,cv::COLOR_BGR2HSV);
        std::vector<cv::Mat> hsvChannels;
        cv::split(hsv, hsvChannels);
        cv::cvtColor(bw,xyz,cv::COLOR_BGR2XYZ);
        std::vector<cv::Mat> xyzChannels;
        cv::split(xyz, xyzChannels);
        // Combine H and Z
        bw = hsvChannels.at(0) + xyzChannels.at(2);
        cv::threshold(bw,bw,0,255,cv::THRESH_TRIANGLE);
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(9,9));
        cv::erode(bw,bw,kernel);
        cv::dilate(bw,bw,kernel);
        cv::erode(bw,bw,kernel);
        cv::erode(bw,bw,kernel);
        cv::dilate(bw,bw,kernel);
        cv::dilate(bw,bw,kernel);
        cv::dilate(bw,bw,kernel);
    }


    if(threhold_method == 1)
    {
        cv::Mat bw_show = convertTo3Channels(bw);
        _data->threholdFrame.push(bw_show);
    }
    else if(threhold_method == 2)
    {
        cv::Mat bw_show = convertTo3Channels(bw);
        _data->threholdFrame2.push(bw_show);
    }
    else if(threhold_method == 3)
    {
        cv::Mat bw_show = convertTo3Channels(bw);
        _data->threholdFrame3.push(bw_show);
    }
    else if(threhold_method == 4)
    {
        cv::Mat bw_show = convertTo3Channels(bw);
        _data->threholdFrame4.push(bw_show);
    }

//    std::cout<<_data->threholdFrame.size()<<"_data->threholdFrame"<<std::endl;

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i>hierarchy;
    cv::findContours(bw,contours,hierarchy,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

    double rotateAngle = 0;
    std::vector<double> area;
    if(contours.size()>0)
    {
        for (size_t i=0; i < contours.size(); ++i) {
            area.push_back(cv::contourArea(contours[i]));
        }
        auto biggest_area = std::max_element(std::begin(area),std::end(area));
        auto index = std::distance(std::begin(area),biggest_area);

        rotateAngle = getMinEnclosingTriangle(contours[index], frame, imgWidth, imgHeight);

        return rotateAngle;
    }
    else
    {
        return -999;
    }

}

double VideoProcess::getMinEnclosingTriangle(std::vector<cv::Point> &pts, cv::Mat img, int imgWidth, int imgHeight)
{
    cv::Mat triangle;

    double rect = cv::minEnclosingTriangle(pts, triangle);

    std::vector<cv::Point2f> p;
    p = cv::Mat_<cv::Point2f>(triangle);
    //triangle.points(P);
//    for (int j = 0; j < 3; j++)
//    {
//        cv::line(img, p[j], p[(j + 1) % 3], cv::Scalar(255,0,0), 5);
//    }
    double len[3];
    for (int i = 0; i < 3; i++) {
        len[i] = sqrt(pow(p[i].x - p[(i + 1) % 3].x, 2) + pow(p[i].y - p[(i + 1) % 3].y, 2));
    }
    int index = 0;
    if (len[0] > len[1]) {
        if (len[0] > len[2]) {
            index = 0;
        }
        else {
            index = 2;
        }
    }
    else {
        if (len[1] > len[2]) {
            index = 1;
        }
        else {
            index = 2;
        }
    }
    //index = len[0] > len[1] ? len[0] > len[2] ? 0 : 2 : 1;
    double result = ((p[(index + 2) % 3].x - p[(index + 1) % 3].x)*(p[index].y - p[(index + 1) % 3].y) / (p[index].x - p[(index + 1) % 3].x) + p[(index + 1) % 3].y) - p[(index + 2) % 3].y;
    double angle = ((p[(index) % 3].y - p[(index + 1) % 3].y) / (p[(index) % 3].x - p[(index + 1) % 3].x));
    angle = atan(angle) * 180 / CV_PI;

    if (result < 0 && (p[(index) % 3].y - p[(index + 1) % 3].y) * (p[(index) % 3].x - p[(index + 1) % 3].x) > 0 ){
        //180 -
        angle = angle-180;
    }
    else if(result < 0 && (p[(index) % 3].y - p[(index + 1) % 3].y) * (p[(index) % 3].x - p[(index + 1) % 3].x) < 0){
        angle = 180 + angle;
    }
//    double x0, y0, alpha;

//    x0 = rect.center.x;
//    y0 = rect.center.y;
//    alpha = -rect.angle*CV_PI / 180;
//    int w = 10;
    //
//    line(img, Point2f(x0 - w, y0), Point2f(x0 + w, y0), CV_RGB(0, 255, 0), 2);
//    line(img, Point2f(x0, y0 - w), Point2f(x0, y0 + w), CV_RGB(0, 255, 0), 2);
    //
//    cv::line(img, cv::Point2f(imgWidth / 2 - w, imgHeight / 2), cv::Point2f(imgWidth / 2 + w, imgHeight / 2), CV_RGB(255, 0, 255), 2);
//    cv::line(img, cv::Point2f(imgWidth / 2, imgHeight / 2 - w), cv::Point2f(imgWidth / 2, imgHeight / 2 + w), CV_RGB(255, 0, 255), 2);
//    double angle_3 = -rect.angle;
    ////putText
//    char str[256];
//    sprintf(str, "%f", angle);
//    std::string angle2str = str;
//
//    int font_face = cv::FONT_HERSHEY_COMPLEX;
//    double font_scale = 2;
//    int thickness = 2;
//    //int baseline;
//
//    cv::putText(img, angle2str, (cv::Point2f(imgWidth / 2 - w, imgHeight / 2),cv::Point2f(imgWidth / 2 + w, imgHeight / 2)), font_face, font_scale, cv::Scalar(0, 0, 255), thickness, 8, 0);


    return angle;
}


/****************************************/
/*   实现自动对比度的函数                  */
/*   目前只有前后中通道调用                */
/*   彩色的已经加入到了函数内部             */
/*****************************************/
void VideoProcess::BrightnessAndContrastAuto(const cv::Mat &src, cv::Mat &dst, float clipHistPercent)
{
    CV_Assert(clipHistPercent >= 0);
    CV_Assert((src.type() == CV_8UC1) || (src.type() == CV_8UC3) || (src.type() == CV_8UC4));

    int histSize = 256;
    float alpha, beta;
    double minGray = 0, maxGray = 0;

    //to calculate grayscale histogram
    cv::Mat gray;
    if (src.type() == CV_8UC1) gray = src;
    else if (src.type() == CV_8UC3) cv::cvtColor(src, gray, CV_BGR2GRAY);
    else if (src.type() == CV_8UC4) cv::cvtColor(src, gray, CV_BGRA2GRAY);
    if (clipHistPercent == 0)
    {
        // keep full available range
        cv::minMaxLoc(gray, &minGray, &maxGray);
    }
    else
    {
        cv::Mat hist; //the grayscale histogram

        float range[] = { 0, 256 };
        const float* histRange = { range };
        bool uniform = true;
        bool accumulate = false;
        cv::calcHist(&gray, 1, 0, cv::Mat (), hist, 1, &histSize, &histRange, uniform, accumulate);

        // calculate cumulative distribution from the histogram
        std::vector<float> accumulator(histSize);
        accumulator[0] = hist.at<float>(0);
        for (int i = 1; i < histSize; i++)
        {
            accumulator[i] = accumulator[i - 1] + hist.at<float>(i);
        }

        // locate points that cuts at required value
        float max = accumulator.back();
        clipHistPercent *= (max / 100.0); //make percent as absolute
        clipHistPercent /= 2.0; // left and right wings
        // locate left cut
        minGray = 0;
        while (accumulator[minGray] < clipHistPercent)
            minGray++;

        // locate right cut
        maxGray = histSize - 1;
        while (accumulator[maxGray] >= (max - clipHistPercent))
            maxGray--;
    }

    // current range
    float inputRange = maxGray - minGray;

    alpha = (histSize - 1) / inputRange;   // alpha expands current range to histsize range
    beta = -0.5*minGray * alpha;             // beta shifts current range so that minGray will go to 0

    // Apply brightness and contrast normalization
    // convertTo operates with saurate_cast
    src.convertTo(dst, -1, alpha, beta);

    // restore alpha channel from source
    if (dst.type() == CV_8UC4)
    {
        int from_to[] = { 3, 3};
        cv::mixChannels(&src, 4, &dst,1, from_to, 1);
    }
    return;
}
/*
 * one channel to three channel
 */
cv::Mat VideoProcess::convertTo3Channels(cv::Mat binImg)
{
    cv::Mat three_channel = cv::Mat::zeros(binImg.rows,binImg.cols,CV_8UC3);
    std::vector<cv::Mat> channels;
    for (int i=0;i<3;i++)
    {
        channels.push_back(binImg);
    }
    merge(channels,three_channel);
    return three_channel;
}



