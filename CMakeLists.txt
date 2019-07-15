cmake_minimum_required(VERSION 2.8)
project(tx2)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#Require OpenGL
find_package(OpenGL REQUIRED)
#Require GLM
find_package(GLM REQUIRED)

########### uavcan library
add_definitions(
        -DUAVCAN_PLATFORM=linux
        -DUAVCAN_CPP_VERSION=UAVCAN_CPP11
        -DUAVCAN_MEM_POOL_BLOCK_SIZE=48
        -DUAVCAN_NO_ASSERTIONS
)
add_subdirectory(modules/MMC_UAVCAN_spec/libuavcan
                ${CMAKE_BINARY_DIR}/modules/libuavcan EXCLUDE_FROM_ALL)
include_directories(
        modules/MMC_UAVCAN_spec/dsdl/generated/mmc
        modules/MMC_UAVCAN_spec/libuavcan/libuavcan/include
        modules/MMC_UAVCAN_spec/libuavcan/libuavcan/include/dsdlc_generated
        modules/MMC_UAVCAN_spec/libuavcan/libuavcan_drivers/linux/include
)
#target_link_libraries(target uavcan)
include(modules/MMC_UAVCAN_spec/CMakeLists.txt)
########### gstreamer libs
find_package(PkgConfig)
message("GST_INCLUDE_DIRS:" ${GST_INCLUDE_DIRS})
pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.4
        #gstreamer1.0-libav
      )
message("-----" ${GST_LIBRARIES})

include_directories(
        ${GST_INCLUDE_DIRS}
)

########### opencv libs
find_package(OpenCV 3.4.3 REQUIRED)
#${OpenCV_LIBS}
include_directories(
        ${OpenCV_INCLUDE_DIRS}
)

########### nanogui libs
# Disable building extras we won't need (pure C++ project)
set(NANOGUI_BUILD_EXAMPLE ON CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_PYTHON  OFF CACHE BOOL " " FORCE)
set(NANOGUI_INSTALL       OFF CACHE BOOL " " FORCE)

# Add the configurations from nanogui
add_subdirectory(modules/nanogui)

include_directories(modules/nanogui/include)
include_directories(${NANOGUI_EXTRA_INCS})
add_definitions(${NANOGUI_EXTRA_DEFS})
# For reliability of parallel build, make the NanoGUI targets dependencies
set_property(TARGET glfw glfw_objects nanogui PROPERTY FOLDER "dependencies")


include_directories(modules/embed-resource)
add_subdirectory(modules/embed-resource)

embed_resources(MyResources src/GUI/shader/vert.glsl src/GUI/shader/frag.glsl src/GUI/shader/basicShader.fs src/GUI/shader/basicShader.vs )

# Add the glad OpenGL loader extension
include_directories(modules/glad/include)

#Find all Header and Source files
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS src/*.h)
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES src/*.cpp)

add_executable(${PROJECT_NAME}
        modules/glad/src/glad.c
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS}
        ${MyResources}
        )

#link libraries to project
target_link_libraries(${PROJECT_NAME}
        uavcan
        nanogui
        ${OPENGL_LIBRARIES}
        ${OpenCV_LIBS}
        ${GST_LIBRARIES}
        )


########### module tests
add_executable(test_cv_nanogui test_cv_nanogui.cpp ${MyResources})
target_link_libraries(test_cv_nanogui  ${OpenCV_LIBS} nanogui ${NANOGUI_EXTRA_LIBS} )

add_executable(test_gst_opencv test_gst_opencv.cpp)
target_link_libraries(test_gst_opencv  ${OpenCV_LIBS})
