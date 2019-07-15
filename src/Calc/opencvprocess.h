//
// Created by askariz on 11/14/18.
//

#ifndef TX2_OPENCVPROCESS_H
#define TX2_OPENCVPROCESS_H

#include <opencv2/opencv.hpp>
#include "../Utils/threadexchangedata.h"
#include "VideoProcess/VideoProcess.h"

namespace OpencvProcess{

    static int process(ThreadExchangeData *data){
        VideoProcess* videoProcess =new VideoProcess(data);
        if(videoProcess->init()){
            videoProcess->loop();
        }
    }
}



#endif //TX2_OPENCVPROCESS_H
