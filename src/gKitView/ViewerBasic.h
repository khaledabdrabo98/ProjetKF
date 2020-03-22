#ifndef VIEWERBASIC_H
#define VIEWERBASIC_H


#include "glcore.h"

#include "window.h"
#include "program.h"
#include "uniforms.h"
#include "texture.h"
#include "mesh.h"
#include "draw.h"
#include "vec.h"
#include "mat.h"
#include "orbiter.h"
#include "app.h"
#include "wavefront.h"
#include "text.h"

#include <vector>

#include "../videoCapture/cameraWin.h"

#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
// pour les projections 2d/3d
#include <opencv2/calib3d/calib3d.hpp>
// fonctions de dessin 
#include <opencv2/imgproc/imgproc.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>


//TODO : modifier la fonction create de Buffer pour initialiser d'un seul coup un tableau de mesh 


// struct Buffers
// {
//     // https://perso.univ-lyon1.fr/jean-claude.iehl/Public/educ/M1IMAGE/html/group__tuto4GL.html
//     GLuint vao;
//     GLuint vertex_buffer;
//     GLuint vertex_buffer1;
    
//     int vertex_count;
//     Buffers( ) : vao(0), vertex_buffer(0), vertex_count(0) {}
    
//     void create( const Mesh& mesh, const Mesh& mesh1)
//     {
//         if(!mesh.vertex_buffer_size()) return;

//         // cree et configure un vertex array object: conserve la description des attributs de sommets
//         glGenVertexArrays(1, &vao);
//         glBindVertexArray(vao);
        
//          /* 1er Mesh */

//         // creer, initialiser le buffer : positions + normals + texcoords du mesh
//         glGenBuffers(1, &vertex_buffer);
//         glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        
//         // taille totale du buffer
//         size_t size = mesh.vertex_buffer_size() + mesh.texcoord_buffer_size() + mesh.normal_buffer_size() + mesh.color_buffer_size();
//         glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

//         // transfere les positions des sommets
//         size_t offset = 0;
//         size = mesh.vertex_buffer_size();
//         glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.vertex_buffer());
//         // et configure l'attribut 0, vec3 position
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
//         glEnableVertexAttribArray(0);

//         // transfere les texcoords des sommets
//         offset = offset + size;
//         size = mesh.texcoord_buffer_size();
//         glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.texcoord_buffer());
//         // et configure l'attribut 1, vec2 texcoord
//         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
//         glEnableVertexAttribArray(1);

//         // transfere les normales des sommets
//         offset = offset + size;
//         size = mesh.normal_buffer_size();
//         glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.normal_buffer());
//         // et configure l'attribut 2, vec3 normal
//         glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
//         glEnableVertexAttribArray(2);

//         // transfere les couleurs des sommets
//         offset = offset + size;
//         size = mesh.color_buffer_size();
//         glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.color_buffer());
//         // et configure l'attribut 3, vec3 normal
//         glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
//         glEnableVertexAttribArray(3);

        
//         /* 2eme Mesh */

//         // cree et initialise le buffer stockant les positions des sommets
//         glGenBuffers(1, &vertex_buffer1);
//         glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer1);

//         size_t size1 = mesh1.vertex_buffer_size() + mesh1.texcoord_buffer_size() + mesh1.normal_buffer_size();
//         glBufferData(GL_ARRAY_BUFFER, size1, nullptr, GL_STATIC_DRAW);

//         glBufferData(GL_ARRAY_BUFFER, size1, nullptr, GL_STATIC_DRAW);

//         // transfere les positions des sommets
//         offset = 0;
//         size1 = mesh.vertex_buffer_size();
//         glBufferSubData(GL_ARRAY_BUFFER, offset, size1, mesh1.vertex_buffer());

//         // et configure l'attribut 4, vec3 position
//         glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
//         glEnableVertexAttribArray(4);




//         // conserve le nombre de sommets
//         vertex_count = mesh.vertex_count();
//         vertex_count += mesh1.vertex_count();
//     }

//     void release( )
//     {
//         glDeleteVertexArrays(1, &vao);
//         glDeleteBuffers(1, &vertex_buffer);
//     }
// };



struct Buffers
{
    // https://perso.univ-lyon1.fr/jean-claude.iehl/Public/educ/M1IMAGE/html/group__tuto4GL.html
    GLuint vao;
    GLuint vertex_buffer;
    GLuint tab_vertex_buffer[100];
    GLuint vertex_normals_buffer;
    
    int vertex_count;
    Buffers( ) : vao(0), vertex_buffer(0), vertex_count(0) {}
    
    void create(const std::vector<Mesh> &tabMeshes)
    {
            size_t id = 0;
            size_t offset = 0;

            // cree et configure un vertex array object: conserve la description des attributs de sommets
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            for (unsigned int i = 0; i < tabMeshes.size(); i++)
            {
                Mesh mesh = tabMeshes.at(i);

                id = i;

                if (!mesh.vertex_buffer_size()) return;

                // creer, initialiser le buffer : positions + normals + texcoords du mesh
                glGenBuffers(1, &tab_vertex_buffer[i]);
                glBindBuffer(GL_ARRAY_BUFFER, tab_vertex_buffer[i]);

                // taille totale du buffer
                size_t size = mesh.vertex_buffer_size();
                glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

                // transfere les positions des sommets

                glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.vertex_buffer());
                // et configure l'attribut 0, vec3 position
                glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
                glEnableVertexAttribArray(id);

                std::cout << "id : " << id << "\n";
                vertex_count = mesh.vertex_count();
            }

                // ajout des normales
                id += 1;
                glGenBuffers(1, &vertex_normals_buffer);
                glBindBuffer(GL_ARRAY_BUFFER, vertex_normals_buffer);

                // taille totale du buffer
                size_t size = tabMeshes.at(0).normal_buffer_size();
                glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
                
                glBufferSubData(GL_ARRAY_BUFFER, offset, size, tabMeshes.at(0).vertex_buffer());

                glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
                glEnableVertexAttribArray(id);

                std::cout << "id : " << id << "\n";


    }

    void release(){
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vertex_buffer);
    }
};


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

    CameraWin cam;

    Orbiter m_camera;
    DrawParam gl,gl1;
    bool mb_cullface;
    bool mb_wireframe;

    Mesh m_axe;
    Mesh m_grid;
    Mesh m_cube;
    Mesh m_cubemap;
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

    GLuint texID;
    GLuint fboID;

    GLuint m_env_map;
    void init_cubemap();
    void draw_cubemap(const Transform& T);

   
    int initFBO(GLuint &id);
    int renderToFBO(cv::Mat &cvImage);

    int doCapture(cv::Mat &out);

    float val;

    float w_neutral, w_jawOpen, w_jawLeft, w_jawRight, w_eyeBrowsRaised;
    
    //! dLib
    void loadFaceDetectionModels();
    std::vector<cv::Point2f> faceKeyPoints;
    

    bool faceDetected;
    std::vector<vec2> neutral_FaceCoordinates;
    std::vector<vec2> jawOpen_FaceCoordinates;
    
    dlib::shape_predictor pose_model;
    dlib::frontal_face_detector detector;


    //! Draw des models 3D avec un shader custom
    GLuint program;
    void init_BSShader();

    void getModelKeyPoints();
    std::vector<cv::Point3f> modelKeyPoints;
    Transform mvp;
    cv::Mat camMatrix;
    void draw_blendshapes();
    

    //vectors for face rotation, PnP functions (Points and Prespective)
    std::vector<cv::Point2d> image_points;
    std::vector<cv::Point3d> model_points;
    // variables qui appliquent la rotation et la translation sur le modele 3D
    Transform transformModel;
    Transform rotationModel;
    void computePnP();

    // coordonnées des 68 points dans chaque expression
    std::vector<cv::Point2f> p_neutral;
    std::vector<cv::Point2f> p_jawOpen;
    std::vector<cv::Point2f> p_jawLeft;
    std::vector<cv::Point2f> p_jawRight;
    std::vector<cv::Point2f> p_eyeBrowsRaised;
    std::vector<cv::Point2f> currentPose;
    std::vector<std::vector<double>> tab_weights;

    double distance(cv::Point2f a,cv::Point2f b );
    void displayTab2D(std::vector<std::vector<double>> tab_weights);
    void getPose(std::vector<dlib::full_object_detection> shapes,  std::vector<cv::Point2f> &out);
    double computeWeight(std::vector<cv::Point2f> currentPose, std::vector<cv::Point2f> expression );
    void inputWeights(std::vector<dlib::full_object_detection> tab_shapes);


    double offsetNum;   

    Mesh m_neutral,m_jawOpen,m_jawRight,m_jawLeft, m_eyeBrowsRaised;
    //Vertex arrays
    Buffers mVA1, mVA2, mVA3;
    cv::Mat rotation_vector; // Rotation in axis-angle form
    cv::Mat translation_vector;
    
};

#endif

