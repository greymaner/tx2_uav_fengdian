/*****************************************************/
/** @copyright    2018 Alex Sommer All rights reserved.
 *     @author    Alex Sommer
 *    @version    1.0
 *       @date    21.04.18
 *****************************************************/

#include "application.h"

/******************************************************
 * Constructors
 *****************************************************/

Application::Application(ThreadExchangeData* data) :  _data(data),nanogui::Screen(Eigen::Vector2i(1920,1080), "NanoGUI Starter",/*resizable*/true, /*fullscreen*/false, /*colorBits*/8,/*alphaBits*/8, /*depthBits*/24, /*stencilBits*/8,/*nSamples*/0, /*glMajor*/4, /*glMinor*/1) {
    nanogui::Window *window = new nanogui::Window(this, "Video");
    window->setPosition(Eigen::Vector2i(-25, -25));
    window->setLayout(new nanogui::GroupLayout(0,0,0,0));


    /* imageView */
    auto imageView = new nanogui::ImageView(window, NULL);//mImagesData[0].first.texture());

    imageView->setCallback([this,imageView] {
        if(!_data->frame.empty()){
            imageView->setSize({1080,768});
//            std::cout << "imageview size " << imageView->size() << std::endl;
            GLuint texture = matToTexture(_data->frame.front(), GL_LINEAR_MIPMAP_LINEAR,   GL_LINEAR, GL_CLAMP);
            imageView->bindImage(texture);
            _data->frame.pop();
        }
    });

//    nanogui::Window *window2 = new nanogui::Window(this, "Analysis Result");
//    window2->setPosition(Eigen::Vector2i(1000, 0));
//    window2->setLayout(new nanogui::GroupLayout(0,0,0,0));
//
//    /* imageView */
//    auto imageView2 = new nanogui::ImageView(window2, NULL);//mImagesData[0].first.texture());
////    performLayout();
//    imageView2->setCallback([this,imageView2] {
//        if(!_data->calcFrame.empty()){
//            imageView2->setSize({400,300});
////            std::cout << "imageview size " << imageView->size() << std::endl;
//            GLuint texture = matToTexture(_data->calcFrame.front(), GL_LINEAR_MIPMAP_LINEAR,   GL_LINEAR, GL_CLAMP);
//            imageView2->bindImage(texture);
////            _data->calcFrame.pop();
//        }
//    });

    //显示第一种阈值化算法(TRIANGLE)结果
    nanogui::Window *window_threhold = new nanogui::Window(this, "Method:TRIANGLE");
    window_threhold->setPosition(Eigen::Vector2i(1100, 0));
    window_threhold->setLayout(new nanogui::GridLayout());
    window_threhold->setSize(Eigen::Vector2i(500,300));
//    /* FP widget */
        auto label = new nanogui::Label(window_threhold, "Angle :", "sans-bold",20);
//        label->setColor(nanogui::Color(255, 0, 0, 100));

        auto textBox = new nanogui::TextBox(window_threhold);
        textBox->setEditable(false);

        textBox->setFixedSize(Eigen::Vector2i(300, 50));
//        textBox->setValue();
        textBox->setUnits("degree");
        textBox->setDefaultValue("0.0");
        textBox->setFontSize(18);
//      textBox->setFormat("[-]?[0-9]*\\.?[0-9]+");

    /* imageView */

    auto imageView_threhold = new nanogui::ImageView(window_threhold, NULL);//mImagesData[0].first.texture());
//    performLayout();
    imageView_threhold->setCallback([this,imageView_threhold,textBox] {
        textBox->setValue(std::to_string(_data->angle));
        if(!_data->threholdFrame.empty()){
            imageView_threhold->setSize({300,200});
//            std::cout << "imageview size " << imageView->size() << std::endl;
            GLuint texture = matToTexture(_data->threholdFrame.front(), GL_LINEAR_MIPMAP_LINEAR,   GL_LINEAR, GL_CLAMP);
            imageView_threhold->bindImage(texture);
            _data->threholdFrame.pop();

        }
    });
    //显示第二种阈值化算法(OTSU)结果
    nanogui::Window *window_otsu= new nanogui::Window(this, "Method:OTSU");
    window_otsu->setPosition(Eigen::Vector2i(1100, 320));
    window_otsu->setLayout(new nanogui::GridLayout());
    window_otsu->setSize(Eigen::Vector2i(500,300));

    new nanogui::Label(window_otsu, "Angle :", "sans-bold",20);
    auto textBox_otsu = new nanogui::TextBox(window_otsu);
    textBox_otsu->setEditable(false);
    textBox_otsu->setFixedSize(Eigen::Vector2i(300, 50));
//        textBox->setValue();
    textBox_otsu->setUnits("degree");
    textBox_otsu->setDefaultValue("0.0");
    textBox_otsu->setFontSize(18);

    /* imageView */
    auto imageView_otsu = new nanogui::ImageView(window_otsu, NULL);//mImagesData[0].first.texture());
//    performLayout();
    imageView_otsu->setCallback([this,imageView_otsu,textBox_otsu] {
        textBox_otsu->setValue(std::to_string(_data->mean_angle[1]));
        if(!_data->threholdFrame2.empty()){
            imageView_otsu->setSize({300,200});
            GLuint texture = matToTexture(_data->threholdFrame2.front(), GL_LINEAR_MIPMAP_LINEAR,   GL_LINEAR, GL_CLAMP);
            imageView_otsu->bindImage(texture);
            _data->threholdFrame2.pop();
        }
    });

    //显示第三种阈值化算法(Lab颜色空间)结果
    nanogui::Window *window_Lab= new nanogui::Window(this, "Method:Lab");
    window_Lab->setPosition(Eigen::Vector2i(1520, 0));
    window_Lab->setLayout(new nanogui::GridLayout());
    window_Lab->setSize(Eigen::Vector2i(500,300));

    new nanogui::Label(window_Lab, "Angle :", "sans-bold",20);
    auto textBox_lab = new nanogui::TextBox(window_Lab);
    textBox_lab->setEditable(false);
    textBox_lab->setFixedSize(Eigen::Vector2i(300, 50));
//        textBox->setValue();
    textBox_lab->setUnits("degree");
    textBox_lab->setDefaultValue("0.0");
    textBox_lab->setFontSize(18);

    /* imageView */
    auto imageView_lab = new nanogui::ImageView(window_Lab, NULL);//mImagesData[0].first.texture());
//    performLayout();
    imageView_lab->setCallback([this,imageView_lab,textBox_lab] {
        textBox_lab->setValue(std::to_string(_data->mean_angle[2]));
        if(!_data->threholdFrame3.empty()){
            imageView_lab->setSize({300,200});
            GLuint texture = matToTexture(_data->threholdFrame3.front(), GL_LINEAR_MIPMAP_LINEAR,   GL_LINEAR, GL_CLAMP);
            imageView_lab->bindImage(texture);
            _data->threholdFrame3.pop();
        }
    });

    //显示第四种阈值化算法(HSV和XYZ颜色空间)结果
    nanogui::Window *window_hsv= new nanogui::Window(this, "Method:hsv");
    window_hsv->setPosition(Eigen::Vector2i(1520, 320));
    window_hsv->setLayout(new nanogui::GridLayout());
    window_hsv->setSize(Eigen::Vector2i(500,300));

    new nanogui::Label(window_hsv, "Angle :", "sans-bold",20);
    auto textBox_hsv = new nanogui::TextBox(window_hsv);
    textBox_hsv->setEditable(false);
    textBox_hsv->setFixedSize(Eigen::Vector2i(300, 50));
//        textBox->setValue();
    textBox_hsv->setUnits("degree");
    textBox_hsv->setDefaultValue("0.0");
    textBox_hsv->setFontSize(18);

    /* imageView */
    auto imageView_hsv = new nanogui::ImageView(window_hsv, NULL);//mImagesData[0].first.texture());
    performLayout();
    imageView_hsv->setCallback([this,imageView_hsv,textBox_hsv] {
        textBox_hsv->setValue(std::to_string(_data->mean_angle[3]));
        if(!_data->threholdFrame4.empty()){
            imageView_hsv->setSize({300,200});
            GLuint texture = matToTexture(_data->threholdFrame4.front(), GL_LINEAR_MIPMAP_LINEAR,   GL_LINEAR, GL_CLAMP);
            imageView_hsv->bindImage(texture);
            _data->threholdFrame4.pop();
        }
    });
//    createGUI(window);

}


// Function turn a cv::Mat into a texture, and return the texture ID as a GLuint for use
GLuint Application::matToTexture(cv::Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter)
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
        std::cout << "You can't use MIPMAPs for magnification - setting filter to GL_LINEAR" << std::endl;
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

/******************************************************
 * Destructor
 *****************************************************/

/******************************************************
 * Public Functions
 *****************************************************/

bool Application::keyboardEvent(int key, int scancode, int action, int modifiers) {
//    if (Screen::keyboardEvent(key, scancode, action, modifiers))
//        return true;
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//        setVisible(false);
//        return true;
//    } else {
//        m_canvas->keyboardEvent(key, scancode, action, modifiers);
//    }
//    return false;
}

void Application::draw(NVGcontext *ctx) {
    /* Draw the user interface */
    Screen::draw(ctx);
}

/******************************************************
 * Private Functions
 *****************************************************/

void Application::createGUI(nanogui::Window *window) {
    Widget *tools = new Widget(window);
    tools->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal,
                                            nanogui::Alignment::Middle, 0, 5));

    nanogui::Button *b0 = new nanogui::Button(tools, "Random Color");
    b0->setCallback([this]() { m_canvas->setBackgroundColor(Eigen::Vector4i(rand() % 256, rand() % 256, rand() % 256, 255)); });

    nanogui::Button *btn_pan = new nanogui::ToolButton(tools, ENTYPO_ICON_HAND);
    btn_pan->setChangeCallback([this](bool active) { m_canvas->setInteractionMode(1, active); });
    nanogui::Button *btn_zoom= new nanogui::ToolButton(tools, ENTYPO_ICON_MAGNIFYING_GLASS);
    btn_zoom->setChangeCallback([this](bool active) { m_canvas->setInteractionMode(2, active); });
    nanogui::Button *btn_rotate = new nanogui::ToolButton(tools, ENTYPO_ICON_CW);
    btn_rotate->setChangeCallback([this](bool active) { m_canvas->setInteractionMode(3, active); });
}
