// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how to find frontal human faces in an image and
    estimate their pose.  The pose takes the form of 68 landmarks.  These are
    points on the face such as the corners of the mouth, along the eyebrows, on
    the eyes, and so forth.  
    

    This example is essentially just a version of the face_landmark_detection_ex.cpp
    example modified to use OpenCV's VideoCapture object to read from a camera instead 
    of files.


    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.  
*/

#include <dlib/opencv.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>


int main()
{
    std::cout << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION;
    try
    {
        cv::VideoCapture cap(0);
        if (!cap.isOpened())
        {
            std::cerr << "Unable to connect to camera" << std::endl;
            return 1;
        }


        dlib::image_window win;

        // Load face detection and pose estimation models.
        dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
        dlib::shape_predictor pose_model;
        dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

        // Grab and process frames until the main window is closed by the user.
        while(!win.is_closed())
        {
            // Grab a frame
            cv::Mat temp;
           // cv::Mat temp_grey; 
            
            
            if (!cap.read(temp))
            {
                break;
            }
            
            //Debug stats
            int fps = cap.get(cv::CAP_PROP_FPS);
            
            
            // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
            // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
            // long as temp is valid.  Also don't do anything to temp that would cause it
            // to reallocate the memory which stores the image as that will make cimg
            // contain dangling pointers.  This basically means you shouldn't modify temp
            // while using cimg.
            
            dlib::cv_image<dlib::bgr_pixel> cimg(temp);

 
            // Detect faces 
            std::vector<dlib::rectangle> faces = detector(cimg);

            

            // Find the pose of each face.
            std::vector<dlib::full_object_detection> shapes;
            
            
                
            for (unsigned long i = 0; i < faces.size(); ++i)
                shapes.push_back(pose_model(cimg, faces[i]));

            

            std::vector<cv::Point2i> points;
            std::vector<cv::Point2i> convexHull;

            //Get each landmark's position
            for(unsigned int i=0 ; i < shapes.size(); ++i)
            {
                for(unsigned int j=0 ; j < shapes[i].num_parts(); ++j)
                {
                int x = shapes[i].part(j).x();
                int y = shapes[i].part(j).y();
                
                points.push_back(cv::Point2i(x,y));
                cv::convexHull(points, convexHull);
                
                cv::circle(temp, cv::Point2i(x,y), 1, cv::Scalar(255,255,0), 2);
                
                }
            }

            unsigned int convexHullSize = convexHull.size();
            for(unsigned int i=1 ; i < convexHullSize ; ++i)
            {
                cv::polylines(temp, convexHull, true, cv::Scalar( 255,255,255 ), 2 );
            }

            
                      
            // Display it all on the screen
            win.clear_overlay();
            win.set_image(cimg);
            
            win.add_overlay(render_face_detections(shapes));
        }
    }
    catch(dlib::serialization_error& e)
    {
        std::cout << "You need dlib's default face landmarking model file to run this example." << std::endl;
        std::cout << "You can get it from the following URL: " << std::endl;
        std::cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << std::endl;
        std::cout << std::endl << e.what() << std::endl;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

