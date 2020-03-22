#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

class CameraWin{
   
   public:
        CameraWin();
        ~CameraWin();
        int initCvCapture(); 
        void dlibDrawText(const dlib::point &p, const std::string &s, 
                        const dlib::rgb_pixel& color);
        cv::Mat& getCVMatCam();
        cv::VideoCapture getCap();
        void displayWin(const dlib::cv_image<dlib::bgr_pixel> &img, 
                    const std::vector<dlib::full_object_detection> &shapes); 

    private:
        cv::Mat cvMatCam;
        cv::VideoCapture cap;
        dlib::image_window win;
};

#endif