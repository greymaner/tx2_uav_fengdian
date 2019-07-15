### onboard application

### libuavcan 
 [参考地址](https://uavcan.org/Implementations/Libuavcan/Tutorials/)
 #### 编译配置
 libuavcan 可以通过c++预处理器构建,所有的编译选项都在libuavcan/include/uavcan/build_config.hpp中.
 
 注意：应用程序应该和库具有相同的配置
 
 * UAVCAN_EXCEPTIONS: 定义异常处理,如runtime_error,out_of_range等,libuavcan会抛出std::exception,如果该值设为0,当发生致命错误的时候
 debug编译的就会停在assert
 
 ### 节点初始化
 
 libuavcan 通过以下三个抽象接口将库和平台隔离
  
  *uavcan::ICanDriver
  *uavacan::ICanIface
  *uavcan::ISystemClock
  
 在linux端使用libuavcan可以有两种方式
 
 * 安装libuavcan
 ```` 
 cd libuavcan
 mkdir build
 cd build
 cmake ..        # Optionally, set the build type: -DCMAKE_BUILD_TYPE=Release (default is RelWithDebInfo)
 make -j4        # This  will invoke the DSDL compiler automatically
 sudo make install # 默认会将头问价和静态库文件安装在/usr/localz中,如果需要改变安装路径可以通过PREFIX来改变
 ````
 * 不安装直接使用,直接再cmake中添加
 ````
 add_definitions(
         -DUAVCAN_PLATFORM=linux
         -DUAVCAN_CPP_VERSION=UAVCAN_CPP11
         -DUAVCAN_MEM_POOL_BLOCK_SIZE=48
         -DUAVCAN_NO_ASSERTIONS
 )
 add_subdirectory(modules/libuavcan
                 ${CMAKE_BINARY_DIR}/modules/libuavcan EXCLUDE_FROM_ALL)
 include_directories(
         modules/libuavcan/libuavcan/include
         modules/libuavcan/libuavcan/include/dsdlc_generated
         modules/libuavcan/libuavcan_drivers/linux/include
 )
 #target_link_libraries(target uavcan)

 ````
 应用程序运行需要用到的平台can接口可以有两个,libuavcan提供了两个脚本/libuavcan/libuavcan_drivers/linux/scripts/uavca_add_*can
 
 * virtual can interface
 * slcan(tunneling can over serial port)
 
  ##### append
  uavcan_add_slcan 脚本分析
