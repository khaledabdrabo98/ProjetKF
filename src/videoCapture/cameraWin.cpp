#include "cameraWin.h"

CameraWin::CameraWin()
{
    initCvCapture();
}




int CameraWin::initCvCapture(){
    cap = cv::VideoCapture(0); //-1
    
    cap.set(10, .5); //10
    
    cap.set(4, 512); //4
    cap.set(3, 512); //3
    if(!cap.isOpened()){
        std::cerr << "Unable to connect to camera" << std::endl;
        return 1;
    }
    
    return 0;
} 

void CameraWin::dlibDrawText(const dlib::point &p, const dlib::rgb_pixel& color ,const std::string &s){
    win.add_overlay(dlib::image_window::overlay_rect(dlib::rectangle(p), color, s));
}

void CameraWin::displayWin(const dlib::cv_image<dlib::bgr_pixel> &img, const std::vector<dlib::full_object_detection> &shapes){
    win.clear_overlay();
    win.set_image(img);
    win.add_overlay(render_face_detections(shapes));
}

cv::Mat& CameraWin::getCVMatCam(){
    return cvMatCam;
}

cv::VideoCapture CameraWin::getCap(){
    return cap;
}

CameraWin::~CameraWin(){
    
}