#include "cameraWin.h"

CameraWin::CameraWin() : b0(*this), b3(*this),
                         b1(*this), b4(*this),
                         b2(*this), b_left(*this), 
                         b_right(*this), label_cubemap(*this),
                         cur_cubemap_id(0),
                         cubemapChanged(false),
                         active_expressions(5, false)
{
    initCvCapture();
    set_size(250,250);
    setButtons();
}

void CameraWin::setButtons(){
    
    set_title("Barre d'interaction");

    int padding = 30;
    for(size_t i=0; i<7;++i) {
        switch (i) {
            case 0:
                b0.set_name("Set Neutral Expression");
                b0.set_pos(10,20);
                b0.set_size(200, b0.height());
                b0.set_click_handler(*this, &CameraWin::set_neutral);
   
                break;
            case 1:
                b1.set_name("Set Jaw Open Expression");
                b1.set_pos(10,20+i*padding);
                b1.set_size(200, b1.height());
                b1.set_click_handler(*this,&CameraWin::set_jaw_open);

                break;
            case 2:
                b2.set_name("Set Jaw Left Expression");
                b2.set_pos(10,20+i*padding);
                b2.set_size(200, b2.height());
                b2.set_click_handler(*this,&CameraWin::set_jaw_left);
                break;
            case 3:
                b3.set_name("Set Jaw Right Expression");
                b3.set_pos(10,20+i*padding);
                b3.set_size(200, b3.height());
                b3.set_click_handler(*this,&CameraWin::set_jaw_right);
                break;
            case 4:
                b4.set_name("Set Eyebrows Up Expression");
                b4.set_pos(10,20+i*padding);
                b4.set_size(200, b4.height());
                b4.set_click_handler(*this,&CameraWin::set_eyebrows);
                break;
            case 5:
                b_left.set_name("<=");
                b_left.set_pos(10,20+i*padding);
                b_left.set_click_handler(*this,&CameraWin::decr_cubemap);

                label_cubemap.set_text("Using Envmap with id : " +std::to_string(cur_cubemap_id) + ".");
                label_cubemap.set_pos(10+b_left.width() * 1.5, 20+i*padding);
                
                b_right.set_name("=>");
                b_right.set_pos(10+b_left.width() + label_cubemap.width() + padding, 20+i*padding);
                b_right.set_click_handler(*this,&CameraWin::incr_cubemap);
                break;
            default:
                break;
        }
            
    }
    
    show();
}

// Click handlers
void CameraWin::set_neutral()   {active_expressions.at(0) = true; b0.disable();}
void CameraWin::set_jaw_open()  {active_expressions.at(1) = true; b1.disable(); }
void CameraWin::set_jaw_left()  {active_expressions.at(2) = true; b2.disable(); }
void CameraWin::set_jaw_right() {active_expressions.at(3) = true; b3.disable(); }
void CameraWin::set_eyebrows()  {active_expressions.at(4) = true; b4.disable(); }
void CameraWin::decr_cubemap()  {(cur_cubemap_id == 0 ? cur_cubemap_id=MAX_CUBEMAP_COUNT-1 : cur_cubemap_id--); 
                                  label_cubemap.set_text("Using Envmap with id : "+std::to_string(cur_cubemap_id));
                                  cubemapChanged=true;}
void CameraWin::incr_cubemap () { cur_cubemap_id = (cur_cubemap_id + 1)%MAX_CUBEMAP_COUNT; 
                                  label_cubemap.set_text("Using Envmap with id : "+std::to_string(cur_cubemap_id));                  
                                   cubemapChanged = true;
                                }

void CameraWin::set_active_expression(unsigned int id, bool val) {
    if(id < active_expressions.size()) {
        active_expressions.at(id) = val;
        
    }
}

bool CameraWin::is_expression_active(unsigned int id){
    if(id < active_expressions.size()) {
        return active_expressions.at(id);
    }
    return false;
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