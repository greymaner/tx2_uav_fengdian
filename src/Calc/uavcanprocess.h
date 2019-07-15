//
// Created by askariz on 11/14/18.
//

#ifndef TX2_UAVCANPROCESS_H
#define TX2_UAVCANPROCESS_H

#include <opencv2/opencv.hpp>
#include "../Utils/threadexchangedata.h"
#include "UavcanNode/UavcanNode.h"

namespace UavcanProcess{

    static int process(ThreadExchangeData *data){
        UavcanNode* uavcanProcess =new UavcanNode(data);
        std::cout<< "start with mmc onboard!";
        const int self_node_id = 20;
        std::vector<std::string> iface_names={"slcan0"};
        uavcanProcess->init(iface_names,self_node_id,"mmc.onboard.processor");
        uavcanProcess->loop();
    }
}



#endif //TX2_OPENCVPROCESS_H
