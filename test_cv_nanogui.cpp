#include <nanogui/nanogui.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <queue>

using namespace nanogui;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::to_string;

enum test_enum {
    Item1 = 0,
    Item2,
    Item3
};

bool bvar = true;
int ivar = 12345678;
double dvar = 3.1415926;
float fvar = (float)dvar;
std::string strval = "A string";
test_enum enumval = Item2;
Color colval(0.5f, 0.5f, 0.7f, 1.f);

static std::queue<cv::Mat> queue_frame;


std::string get_tegra_pipeline(int width, int height, int fps) {
//    return "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + ", height=(int)" +
//           std::to_string(height) + ", format=(string)I420, framerate=(fraction)" + std::to_string(fps) +
//           "/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
    return "filesrc location=/home/askariz/Downloads/Falls9.mov  ! decodebin ! videoconvert ! appsink sync=false";
}

// Function turn a cv::Mat into a texture, and return the texture ID as a GLuint for use
GLuint matToTexture(cv::Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter)
{
    // Generate a number for our textureID's unique handle
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Bind to our texture handle
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Catch silly-mistake texture interpolation method for magnification
    if (magFilter == GL_LINEAR_MIPMAP_LINEAR  ||
        magFilter == GL_LINEAR_MIPMAP_NEAREST ||
        magFilter == GL_NEAREST_MIPMAP_LINEAR ||
        magFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        cout << "You can't use MIPMAPs for magnification - setting filter to GL_LINEAR" << endl;
        magFilter = GL_LINEAR;
    }

    // Set texture interpolation methods for minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    // Set texture clamping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter);

    // Set incoming texture format to:
    // GL_BGR       for CV_CAP_OPENNI_BGR_IMAGE,
    // GL_LUMINANCE for CV_CAP_OPENNI_DISPARITY_MAP,
    // Work out other mappings as required ( there's a list in comments in main() )
    GLenum inputColourFormat = GL_BGR;
    if (mat.channels() == 1)
    {
        inputColourFormat = GL_LUMINANCE;
    }

    // Create the texture
    glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                 0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,            // Internal colour format to convert to
                 mat.cols,          // Image width  i.e. 640 for Kinect in standard mode
                 mat.rows,          // Image height i.e. 480 for Kinect in standard mode
                 0,                 // Border width in pixels (can either be 1 or 0)
                 inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE,  // Image data type
                 mat.ptr());        // The actual image data itself

    // If we're using mipmaps then generate them. Note: This requires OpenGL 3.0 or higher
    if (minFilter == GL_LINEAR_MIPMAP_LINEAR  ||
        minFilter == GL_LINEAR_MIPMAP_NEAREST ||
        minFilter == GL_NEAREST_MIPMAP_LINEAR ||
        minFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    return textureID;
}

void opencv_thread(){
    int WIDTH = 1920;
    int HEIGHT = 1080;
    int FPS = 30;

    std::cout << "opencv build information: \n\t" << cv::getBuildInformation() << "\n";
    // Define the gstream pipeline
    std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";

    // Create OpenCV capture object, ensure it works.
    cv::VideoCapture cap(0);//pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened()) {
        std::cout << "Connection failed";
        return;
    }
    // View video
    cv::Mat frame;

    while(1){
        cap >> frame;  // Get a new frame from camera

        if(frame.data){
            queue_frame.push(frame);
            std::cout << "queue size " << queue_frame.size() << std::endl;
        }
        cv::waitKey(10); //needed to show frame
    }
}

int main(int /* argc */, char ** /* argv */) {
    nanogui::init();

    /* scoped variables */ {
        bool use_gl_4_1 = false;// Set to true to create an OpenGL 4.1 context.
        Screen *screen = nullptr;

        if (use_gl_4_1) {
            // NanoGUI presents many options for you to utilize at your discretion.
            // See include/nanogui/screen.h for what all of these represent.
            screen = new Screen(Vector2i(500, 700), "NanoGUI test [GL 4.1]",
                    /*resizable*/true, /*fullscreen*/false, /*colorBits*/8,
                    /*alphaBits*/8, /*depthBits*/24, /*stencilBits*/8,
                    /*nSamples*/0, /*glMajor*/4, /*glMinor*/1);
        } else {
            screen = new Screen(Vector2i(1920, 1080), "NanoGUI test",false,true);
        }

        auto imageWindow = new Window(screen, "FPS");
        imageWindow->setPosition(Vector2i(0, 0));
        imageWindow->setLayout(new GroupLayout(0,0,0,0));

        auto imageView = new ImageView(imageWindow, NULL);//mImagesData[0].first.texture());
        imageView->center();
        cv::Mat img = cv::imread("screenshot.png",CV_LOAD_IMAGE_COLOR);
        if(!img.empty()){
            GLuint texture = matToTexture(img, GL_LINEAR_MIPMAP_LINEAR,   GL_LINEAR, GL_CLAMP);
            imageView->bindImage(texture);
        }

        std::thread opencv_th(opencv_thread);
        opencv_th.detach();

        imageView->setCallback([imageView] {
            if(!queue_frame.empty()){
                GLuint texture = matToTexture(queue_frame.front(), GL_LINEAR_MIPMAP_LINEAR,   GL_LINEAR, GL_CLAMP);
                imageView->bindImage(texture);
                queue_frame.pop();
            }
        });

        screen->setVisible(true);
        screen->performLayout();

        nanogui::mainloop(20);
    }

    nanogui::shutdown();
    return 0;
}
