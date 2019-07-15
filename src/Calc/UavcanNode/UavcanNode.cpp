//
// Created by askariz on 11/18/18.
//

#include "UavcanNode.h"

#include <Tx2Command.hpp>
#include <FcState1.hpp>

using mmc::Tx2Command;
using mmc::FcState1;
UavcanNode::UavcanNode(ThreadExchangeData *data):_data(data),_task_should_exit(false){

}

void UavcanNode::init(const std::vector<std::string>& ifaces, uavcan::NodeID nid,
                      const std::string& name)
{
    _node = uavcan_linux::makeNode(ifaces);
    /*
    * Configuring the node.
    */
    _node->setNodeID(nid);
    _node->setName(name.c_str());

    _node->getLogger().setLevel(uavcan::protocol::debug::LogLevel::DEBUG);

    /*
    * Starting the node.
    */
    std::cout << "Starting the node..." << std::endl;
    const int start_res = _node->start();
    std::cout << "Start returned: " << start_res << std::endl;

    std::cout << "Node started successfully" << std::endl;

    /*
    * Say Hi to the world.
    */
    _node->setModeOperational();
//    _node->logInfo("init", "Hello world! I'm [%*], NID %*",
//                   _node->getNodeStatusProvider().getName().c_str(), int(_node->getNodeID().get()));

}


void UavcanNode::loop() {
    /*
     * Subscribing to the UAVCAN logging topic
     */
//    auto log_handler = [](const uavcan::ReceivedDataStructure<uavcan::protocol::debug::LogMessage>& msg)
//    {
//        std::cout << msg << std::endl;
//    };
//    auto log_sub = _node->makeSubscriber<uavcan::protocol::debug::LogMessage>(log_handler);


    /*
     * yaw
     */
    auto yaw_handler = [&](const uavcan::ReceivedDataStructure<mmc::FcState1>& msg)
    {
        //std::cout << msg.yaw << std::endl;
        if(_data->start_calc)
        {
                _data->yaw.push_back(msg.yaw);
                //std::cout << "---------------msg.yaw---------------"<<msg.yaw<<std::endl;

        }

    };
    auto yaw_sub = _node->makeSubscriber<mmc::FcState1>(yaw_handler);


    auto tunnel_handler = [](const uavcan::ReceivedDataStructure<uavcan::tunnel::Broadcast>& msg)
    {
        //std::cout << msg << std::endl;
        // 处理透传数据


    };
    auto tunnel_sub = _node->makeSubscriber<uavcan::tunnel::Broadcast>(tunnel_handler);


    /*
     * tunnel groundcontroller
     */
//    uavcan::Publisher<uavcan::tunnel::Broadcast> tunnel_pub(*_node);
    auto tunnel_pub = _node->makePublisher<uavcan::tunnel::Broadcast>();
//    auto log_pub = _node->makePublisher<uavcan::protocol::debug::LogMessage>();

    /*
     * server
     */

    uavcan::ServiceServer<Tx2Command> work_status(*_node);
    const int res = work_status.start([&](const Tx2Command::Request& request, Tx2Command::Response& response)
            {
                //request
                if(request.magic_number == request.MAGIC_NUMBER && request.cmd == request.CMD_START_WORK)
                {
                    _data->start_calc = true;
                    response.ok = true;
//                    while (true)
//                    {
//                        if(_data->calc_over)
//                        {
//                            response.ok = true;
//                            break;
//                        }
//                    }
                }
            });
    if (res < 0)
    {
        throw std::runtime_error("Failed to start the Tx2Command server: " + std::to_string(res));
    }

    //--

   // auto ang_pub = _node->makePublisher<uavcan::protocol::Direction>();

//    const int ang_pub_init_res = ang_pub->init(0);
//    if(ang_pub_init_res < 0)
//    {
//        //throw std::runtime_error("Failed to start the publisher; error: " + std::to_string(ang_pub_init_res));
//    }
    //--

    /*
     * Printing when other nodes enter the network or change status
     */
//    struct NodeStatusMonitor : public uavcan::NodeStatusMonitor
//    {
//        explicit NodeStatusMonitor(uavcan::INode& node) : uavcan::NodeStatusMonitor(node) { }
//
//        void handleNodeStatusChange(const NodeStatusChangeEvent& event) override
//        {
//            std::cout << "Remote node NID " << int(event.node_id.get()) << " changed status: "
//                      << event.old_status.toString() << " --> "
//                      << event.status.toString() << std::endl;
//        }
//    };

    //NodeStatusMonitor nsm(*_node);

    /*
     * Adding a stupid timer that does nothing once a minute
     */
//    auto do_nothing_once_a_minute = [this](const uavcan::TimerEvent&)
//    {
//        //_node->logInfo("timer", "Another minute passed...");
//        // coverity[dont_call]
//        //_node->setVendorSpecificStatusCode(static_cast<std::uint16_t>(std::rand())); // Setting to an arbitrary value
//    };
   // auto timer = _node->makeTimer(uavcan::MonotonicDuration::fromMSec(60000), do_nothing_once_a_minute);

    /*
     * Spinning forever
     */
    while (!_task_should_exit)
    {
        const int res = _node->spin(uavcan::MonotonicDuration::fromMSec(1000));

        // publish range data to bus
        //std::cout << queue_range.size() <<endl;
//        if(!queue_range.empty()){
//            mynt_range_t tmp = queue_range.front();//
//
            uavcan::protocol::debug::LogMessage log;

//            measure.fov_h = 150;
//            measure.fov_v = 60;
//            memcpy(&measure.range,tmp.range,sizeof(measure.range));
//            log.text ="123";
//            const int res2 = log_pub->broadcast(log);

            /*
            * Publishing the message.
            */

//            if (pub_res < 0)
//            {
//                std::cerr << "direction_msg publication failure: " << pub_res << std::endl;
//            }

            /*
             * publish tunnel message to groundcontorller
             */

            uavcan::tunnel::Broadcast angle_msg;
            if(_data->calc_over)
//            _data->angle =0.123;
//            if(1)
            {
                uint8_t  buf[11] = {20, 0, 8 ,0xa5, 1, 6}; // canid pyload_lenth

//                angle_msg.buffer.push_back(20);
//                angle_msg.buffer.push_back(0);          // can id
//                angle_msg.buffer.push_back(0xA5);
//                angle_msg.buffer.push_back(0x01);
//                angle_msg.buffer.push_back(6);
                uint8_t *p_data = (uint8_t *)&_data->angle;
                for(int i = 0 ;i < sizeof(_data->angle);i++)
                    buf[6 + i] = *p_data++;
                buf[10] =  cal_crc_table((unsigned char *)(&(buf[3])), 6);

//                    angle_msg.buffer.push_back(*p_data++);
//                angle_msg.buffer.push_back(cal_crc_table((unsigned char *)(&(angle_msg.buffer[2])), 6));
                for(int i = 0 ; i < sizeof(buf); i ++ ) {
                    angle_msg.buffer.push_back(buf[i]);
                    std::cout << (int)buf[i] << std::endl;
                }
                const int tunnel_pub_res = tunnel_pub->broadcast(angle_msg);
                if (tunnel_pub_res < 0)
                {
                    std::cerr << "angle_msg publication failure: " << tunnel_pub_res << std::endl;
                }
                _data->calc_over = false;
            }
    }
}

/*
 * crc8
 */
static const unsigned char crc_table[] =
        {
                0x00,0x31,0x62,0x53,0xc4,0xf5,0xa6,0x97,0xb9,0x88,0xdb,0xea,0x7d,0x4c,0x1f,0x2e,
                0x43,0x72,0x21,0x10,0x87,0xb6,0xe5,0xd4,0xfa,0xcb,0x98,0xa9,0x3e,0x0f,0x5c,0x6d,
                0x86,0xb7,0xe4,0xd5,0x42,0x73,0x20,0x11,0x3f,0x0e,0x5d,0x6c,0xfb,0xca,0x99,0xa8,
                0xc5,0xf4,0xa7,0x96,0x01,0x30,0x63,0x52,0x7c,0x4d,0x1e,0x2f,0xb8,0x89,0xda,0xeb,
                0x3d,0x0c,0x5f,0x6e,0xf9,0xc8,0x9b,0xaa,0x84,0xb5,0xe6,0xd7,0x40,0x71,0x22,0x13,
                0x7e,0x4f,0x1c,0x2d,0xba,0x8b,0xd8,0xe9,0xc7,0xf6,0xa5,0x94,0x03,0x32,0x61,0x50,
                0xbb,0x8a,0xd9,0xe8,0x7f,0x4e,0x1d,0x2c,0x02,0x33,0x60,0x51,0xc6,0xf7,0xa4,0x95,
                0xf8,0xc9,0x9a,0xab,0x3c,0x0d,0x5e,0x6f,0x41,0x70,0x23,0x12,0x85,0xb4,0xe7,0xd6,
                0x7a,0x4b,0x18,0x29,0xbe,0x8f,0xdc,0xed,0xc3,0xf2,0xa1,0x90,0x07,0x36,0x65,0x54,
                0x39,0x08,0x5b,0x6a,0xfd,0xcc,0x9f,0xae,0x80,0xb1,0xe2,0xd3,0x44,0x75,0x26,0x17,
                0xfc,0xcd,0x9e,0xaf,0x38,0x09,0x5a,0x6b,0x45,0x74,0x27,0x16,0x81,0xb0,0xe3,0xd2,
                0xbf,0x8e,0xdd,0xec,0x7b,0x4a,0x19,0x28,0x06,0x37,0x64,0x55,0xc2,0xf3,0xa0,0x91,
                0x47,0x76,0x25,0x14,0x83,0xb2,0xe1,0xd0,0xfe,0xcf,0x9c,0xad,0x3a,0x0b,0x58,0x69,
                0x04,0x35,0x66,0x57,0xc0,0xf1,0xa2,0x93,0xbd,0x8c,0xdf,0xee,0x79,0x48,0x1b,0x2a,
                0xc1,0xf0,0xa3,0x92,0x05,0x34,0x67,0x56,0x78,0x49,0x1a,0x2b,0xbc,0x8d,0xde,0xef,
                0x82,0xb3,0xe0,0xd1,0x46,0x77,0x24,0x15,0x3b,0x0a,0x59,0x68,0xff,0xce,0x9d,0xac
        };
//------------------------------------------------------------------------------
//--函数名：  cal_crc_table
//--函数功能：软件crc校验
//--输入参数： ptr：需要校验的数据指针，len：需要校验的数据长度
//--输出参数： crc
//------------------------------------------------------------------------------
unsigned char UavcanNode::cal_crc_table(unsigned char *ptr, unsigned char len)
{
    unsigned char  crc = 0x00;
    while (len--)
    {
        crc = crc_table[crc ^ *ptr++];
    }
    return (crc);
}