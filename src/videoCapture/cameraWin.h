#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

#define MAX_CUBEMAP_COUNT 3

class CameraWin : public dlib::drawable_window{
   
   public:
        CameraWin();
        ~CameraWin();
        int initCvCapture(); 
        void dlibDrawText(const dlib::point &p, const dlib::rgb_pixel& color,
                        const std::string &s);
        cv::Mat& getCVMatCam();
        cv::VideoCapture getCap();
        void displayWin(const dlib::cv_image<dlib::bgr_pixel> &img, 
                    const std::vector<dlib::full_object_detection> &shapes); 

        unsigned int cur_cubemap_id;
        bool cubemapChanged;
        bool is_expression_active(unsigned int id);
        void set_active_expression(unsigned int id, bool val);

    private:
        cv::Mat cvMatCam;
        cv::VideoCapture cap;
        dlib::image_window win;

        // Interaction
        std::vector<dlib::button> buttons;
        dlib::toggle_button b0,b1,b2,b3,b4;
        dlib::button b_left, b_right;
        dlib::label label_cubemap;
        std::vector<bool> active_expressions;
        
        void setButtons();
       
        void on_click(dlib::toggle_button& self);

        
        // Click handlers
        void set_neutral();
        void set_jaw_open();
        void set_jaw_left();
        void set_jaw_right();
        void set_eyebrows();
        void decr_cubemap();
        void incr_cubemap();
};

#endif