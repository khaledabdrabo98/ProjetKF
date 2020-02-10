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

#include <vector>


#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>


//TODO : modifier la fonction create de Buffer pour initialiser d'un seul coup un tableau de mesh 

struct Buffers
{
    // https://perso.univ-lyon1.fr/jean-claude.iehl/Public/educ/M1IMAGE/html/group__tuto4GL.html
    GLuint vao;
    GLuint vertex_buffer;
    GLuint vertex_buffer1;
    
    int vertex_count;
    Buffers( ) : vao(0), vertex_buffer(0), vertex_count(0) {}
    
    void create( const Mesh& mesh, const Mesh& mesh1)
    {
        if(!mesh.vertex_buffer_size()) return;

        // cree et configure un vertex array object: conserve la description des attributs de sommets
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
         /* 1er Mesh */

        // creer, initialiser le buffer : positions + normals + texcoords du mesh
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        
        // taille totale du buffer
        size_t size = mesh.vertex_buffer_size() + mesh.texcoord_buffer_size() + mesh.normal_buffer_size() + mesh.color_buffer_size();
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

        // transfere les positions des sommets
        size_t offset = 0;
        size = mesh.vertex_buffer_size();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.vertex_buffer());
        // et configure l'attribut 0, vec3 position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
        glEnableVertexAttribArray(0);

        // transfere les texcoords des sommets
        offset = offset + size;
        size = mesh.texcoord_buffer_size();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.texcoord_buffer());
        // et configure l'attribut 1, vec2 texcoord
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
        glEnableVertexAttribArray(1);

        // transfere les normales des sommets
        offset = offset + size;
        size = mesh.normal_buffer_size();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.normal_buffer());
        // et configure l'attribut 2, vec3 normal
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
        glEnableVertexAttribArray(2);

        // transfere les couleurs des sommets
        offset = offset + size;
        size = mesh.color_buffer_size();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, mesh.color_buffer());
        // et configure l'attribut 3, vec3 normal
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
        glEnableVertexAttribArray(3);

        
        /* 2eme Mesh */

        // cree et initialise le buffer stockant les positions des sommets
        glGenBuffers(1, &vertex_buffer1);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer1);

        size_t size1 = mesh1.vertex_buffer_size() + mesh1.texcoord_buffer_size() + mesh1.normal_buffer_size();
        glBufferData(GL_ARRAY_BUFFER, size1, nullptr, GL_STATIC_DRAW);

        glBufferData(GL_ARRAY_BUFFER, size1, nullptr, GL_STATIC_DRAW);

        // transfere les positions des sommets
        offset = 0;
        size1 = mesh.vertex_buffer_size();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size1, mesh1.vertex_buffer());

        // et configure l'attribut 4, vec3 position
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
        glEnableVertexAttribArray(4);

        // conserve le nombre de sommets
        vertex_count = mesh.vertex_count();
        vertex_count += mesh1.vertex_count();
    }

    // void create(std::vector<Mesh> meshes){

    //     // cree et configure un vertex array object: conserve la description des attributs de sommets
    //     glGenVertexArrays(1, &vao);
    //     glBindVertexArray(vao);

    //     // creer, initialiser le buffer : positions + normals + texcoords du mesh
    //     glGenBuffers(1, &vertex_buffer);
    //     glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    //     // taille totale du buffer
    //     Mesh first = meshes.at(0);
    //     size_t size = first.vertex_buffer_size() + first.texcoord_buffer_size() + first.normal_buffer_size() + first.color_buffer_size();
    //     glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

    //     // transfere les positions des sommets
    //     size_t offset = 0;
    //     size = first.vertex_buffer_size();
    //     glBufferSubData(GL_ARRAY_BUFFER, offset, size, first.vertex_buffer());
    //     // et configure l'attribut 0, vec3 position
    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
    //     glEnableVertexAttribArray(0);

    //     for(int i=0 ; i < meshes.size() ; i++){
    //         if(!meshes.at(i).vertex_buffer_size()) return;

    //         // transfere les positions des sommets
    //         offset = offset + size;
    //         size = meshes.at(i).vertex_buffer_size();
    //         glBufferSubData(GL_ARRAY_BUFFER, offset, size, meshes.at(i).vertex_buffer());
    //         // et configure l'attribut 0, vec3 position
    //         glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, /* stride */ 0, (const GLvoid *)offset);
    //         glEnableVertexAttribArray(i);

    //         vertex_count = meshes.at(i).vertex_count();
    //     }
    // }



    void release( )
    {
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
    void init_BSShader();
    void draw_blendshapes();
    void createVAO(GLuint );
    GLuint program;
    Transform mvp;

    Mesh m_default,m_mouth_CL,m_mouth_CR;
    //Vertex arrays
    Buffers mVA1, mVA2, mVA3;



    
    
};



#endif

