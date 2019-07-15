//
// Created by askariz on 11/18/18.
//

#ifndef TX2_UAVCANNODE_H
#define TX2_UAVCANNODE_H

#include "../../Utils/threadexchangedata.h"
#include <uavcan/uavcan.hpp>
#include <uavcan_linux/uavcan_linux.hpp>
#include <uavcan/protocol/node_status_monitor.hpp>
#include <uavcan/tunnel/Broadcast.hpp>

class UavcanNode {
private:
    ThreadExchangeData *_data;
    uavcan_linux::NodePtr _node;
    bool _task_should_exit;
public:
    UavcanNode(ThreadExchangeData* data);

    void init(const std::vector<std::string>& ifaces, uavcan::NodeID nid,
               const std::string& name);
    void loop();
    unsigned char cal_crc_table(unsigned char *ptr, unsigned char len);
};


#endif //TX2_UAVCANNODE_H
