
#ifndef VIEWERBASIC_H
#define VIEWERBASIC_H

#include <vector>

// gKit
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

// Dlib
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

// OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// ImGui
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "../videoCapture/cameraWin.h"


struct Buffers
{
    // https://perso.univ-lyon1.fr/jean-claude.iehl/Public/educ/M1IMAGE/html/group__tuto4GL.html
    GLuint vao;
    GLuint vertex_buffer;
    GLuint tab_vertex_buffer[100];
    GLuint vertex_normals_buffer;
    GLuint texcoords_buffer;
    
    int vertex_count;
    Buffers( ) : vao(0), vertex_buffer(0), vertex_count(0) {}
    
    void create(const std::vector<Mesh> &tabMeshes)
    {
            size_t id = 0;
            size_t offset = 0;
            size_t size = 0;
            // cree et configure un vertex array object: conserve la description des attributs de sommets
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            for (unsigned int i = 0; i < tabMeshes.size(); i++)
            {
                Mesh mesh = tabMeshes.at(i);

                id = i;

                if (!mesh.vertex_buffer_size()) return;

                // creer, initialiser le buffer : positions
                glGenBuffers(1, &tab_vertex_buffer[i]);
                glBindBuffer(GL_ARRAY_BUFFER, tab_vertex_buffer[i]);

                // taille totale du buffer
                size = mesh.vertex_buffer_size();
                glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

                // transfere les positions des sommets

                glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.vertex_buffer());
                // et configure l'attribut id, vec3 position
                glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
                glEnableVertexAttribArray(id);

                std::cout << "id : " << id << "\n";
                vertex_count += mesh.vertex_count();
            }
                
                // Ajout des normales
                if (tabMeshes.at(0).normal_buffer_size()){
                    id += 1;
                    glGenBuffers(1, &vertex_normals_buffer);
                    glBindBuffer(GL_ARRAY_BUFFER, vertex_normals_buffer);

                    // taille totale du buffer
                    size = tabMeshes.at(0).normal_buffer_size();

                    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

                    glBufferSubData(GL_ARRAY_BUFFER, offset, size, tabMeshes.at(0).normal_buffer());

                    glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
                    glEnableVertexAttribArray(id);
                    std::cout << "id : " << id << "\n";
                }
                
                // Ajout des texcoords
                if (!tabMeshes.at(0).texcoord_buffer_size()){

                    // ajout des texcoords
                    id += 1;
                    glGenBuffers(1, &texcoords_buffer);
                    glBindBuffer(GL_ARRAY_BUFFER, texcoords_buffer);

                    // taille totale du buffer
                    size = tabMeshes.at(0).texcoord_buffer_size();
                    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

                    glBufferSubData(GL_ARRAY_BUFFER, offset, size, tabMeshes.at(0).texcoord_buffer());

                    glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
                    glEnableVertexAttribArray(id);

                    std::cout << "id : " << id << "\n";
                }
                



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
    
    CameraWin win;

    Orbiter m_camera;
    DrawParam gl,gl1;
    bool mb_cullface;
    bool mb_wireframe;

    Mesh m_axe, m_grid, m_cube, m_skybox, m_quad;

    GLuint m_tex_debug;

    
    bool b_draw_grid;
    bool b_draw_axe;
    //! Init modeles gKit
    void init_axe();
    void init_grid();
    void init_cube();
    void init_skybox();
    void init_quad();

    //! Draw modeles gKit
    void draw(const Transform& T, Mesh &mesh);
    void draw_axe(const Transform& T);
	void draw_grid(const Transform& T);
	void draw_cube(const Transform& T);
	void draw_quad(const Transform& T, const GLuint &Tex);
    void manageCameraLight();

    Buffers bs_buffer,
    cubemap_buffer;

    ///@{
        /** Partie cubemap **/
    GLuint m_env_map;
    GLuint program_cubemap;
    void init_tex_cubemap(GLuint &cubemap_tex);
    void draw_skybox(const Transform &T);
    ///@}

    ///@{
        /** Partie reconnance faciale **/
    dlib::shape_predictor pose_model;
    dlib::frontal_face_detector detector;
    void loadFaceDetectionModels();
    int doCapture(cv::Mat &out);
    bool faceDetected;
    std::vector<cv::Point2f> faceKeyPoints;

    ///@}

    /** Pour le calcul de la rotation et translation du visage **/
    void computePnP();
    ///@{
        /** Partie PnP**/
    std::vector<cv::Point2f> image_points;
    std::vector<cv::Point3d> model_points;
    cv::Mat rotation_vector;
    cv::Mat translation_vector;
    // Variables qui appliquent la rotation et la translation sur le modele 3D
    Transform transformModel;
    Transform rotationModel;
    ///@}


    void init_blendshapes();
    /** Affichage des blendshapes avec un shader custom **/
    void draw_blendshapes();

    //! POSES

    GLuint program_blendshape;
    Transform mvp;
    cv::Mat camMatrix;


    ///@{
        /** Partie capture expressions **/
    // Stocke l'état d'une pose (capturée ou non)
    bool pose_taken[5] = {false};
    // Coordonnées des 68 points dans chaque expression
    std::vector<cv::Point2f> p_neutral,p_jawOpen,p_jawLeft,p_jawRight,p_eyeBrowsRaised;


    Mesh m_neutral, m_jawOpen, m_jawRight, m_jawLeft, m_eyeBrowsRaised;

    float w_neutral, w_jawOpen, w_jawLeft, w_jawRight, w_eyeBrowsRaised;
    // Stocke la pose filmée
    std::vector<cv::Point2f> currentPose;

    void getPose(std::vector<dlib::full_object_detection> shapes, std::vector<cv::Point2f> &out, unsigned int id);
    double compute_weight(std::vector<cv::Point2f> currentPose, std::vector<cv::Point2f> expression);
    void savePoseForCalibration(std::vector<dlib::full_object_detection> tab_shapes);
    ///@}
    // Fonction utilitaires
    void removeTranslationInMat44(float mat[4][4] );
    double distance(cv::Point2f a, cv::Point2f b);
    void print_pose_debug(unsigned int id);
    

    
};

#endif

