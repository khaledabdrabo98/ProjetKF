#include <dlib/opencv.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

#include "ViewerBasic.h"
#include "program.h"
#include <thread>



int main()
{   
   
   ViewerBasic v;
   v.run();
   
}

