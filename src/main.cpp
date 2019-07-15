/*****************************************************/
/** @copyright    2018 Alex Sommer All rights reserved.
 *     @author    Alex Sommer
 *    @version    1.0
 *       @date    20.04.18
 *****************************************************/

#include "GUI/appbuilder.h"
#include "Calc/testCalc.h"
#include "Calc/opencvprocess.h"
#include "Calc/uavcanprocess.h"
#include "Utils/threadexchangedata.h"
#include <thread>


int main(int /* argc */, char ** /* argv */) {
    ThreadExchangeData data;
    data.newData = false;

    std::thread opencvThread(OpencvProcess::process,&data);
    std::thread calcAngleThread(TestCalc::process, &data);
//    std::thread uavcanThread(UavcanProcess::process,&data);
    std::thread guiThread(AppBuilder::build, &data);

    opencvThread.join();
    calcAngleThread.join();
//    uavcanThread.join();
    guiThread.join();
    return 0;
}
