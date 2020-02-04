#ifndef VIEWERBASIC_H
#define VIEWERBASIC_H


#include "glcore.h"

#include "window.h"
#include "program.h"
#include "texture.h"
#include "mesh.h"
#include "draw.h"
#include "vec.h"
#include "mat.h"
#include "orbiter.h"
#include "app.h"
#include "wavefront.h"


#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

class ViewerBasic : public App
{
public:
	ViewerBasic();

    //! Initialise tout : compile les shaders et construit le programme + les buffers + le vertex array. renvoie -1 en cas d'erreur.
    int init();

    //! La fonction d'affichage
    int render();

    void help();

	int quit() { return 1;  }

protected:

    Orbiter m_camera;
    DrawParam gl;
    bool mb_cullface;
    bool mb_wireframe;

    Mesh m_axe;
    Mesh m_grid;
    Mesh m_cube;
    std::vector<Mesh> blendshapes;

    GLuint m_tex_debug;

    bool b_draw_grid;
    bool b_draw_axe;
    void init_axe();
    void init_grid();
    void init_cube();
    Mesh init_OBJ(const char *filename);

    Mesh m_quad;
    void init_quad();

    void draw(const Transform& T, Mesh &mesh);

    void draw_axe(const Transform& T);
	void draw_grid(const Transform& T);
	void draw_cube(const Transform& T);
	void draw_quad(const Transform& T, const GLuint &Tex);

    void manageCameraLight();

    //! OpenCV
    cv::Mat cvMatCam;
    cv::VideoCapture cap;
    int initCvCapture();
    int doCapture(cv::Mat &out);

    //! dLib
    void loadFaceDetectionModels();
    dlib::shape_predictor pose_model;
    dlib::frontal_face_detector detector;
    
    GLuint texID;
    GLuint fboID;
    int initFBO(GLuint &id);
    int renderToFBO(cv::Mat &cvImage);

    //! Fonctions mathematiques
    Vector lerpV3(const Vector &a, const Vector &b, double alpha);
    Mesh interpolateMeshes(const Mesh &a, const Mesh &b, double alpha);
    Mesh interp;




    
    
};



#endif

