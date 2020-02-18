#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include <ViewerBasic.h>


using namespace std;

#define SCREEN_W 1024
#define SCREEN_H 768


/////////////////////////////
//! Gkit init functions 
/////////////////////////////  

ViewerBasic::ViewerBasic() : App(SCREEN_W, SCREEN_H), mb_cullface(true), mb_wireframe(false), b_draw_grid(true), b_draw_axe(true)
{
}


void ViewerBasic::help()
{
    printf("HELP:\n");
    printf("\th: help\n");
    printf("\tc: (des)active GL_CULL_FACE\n");
    printf("\tw: (des)active wireframe\n");
    printf("\ta: (des)active l'affichage de l'axe\n");
    printf("\tg: (des)active l'affichage de la grille\n");
    printf("\tz: (des)active l'affichage de la courbe d'animation\n");
    printf("\tfleches/pageUp/pageDown: bouge la camra\n");
    printf("\tCtrl+fleche/pageUp/pageDown: bouge la source de lumire\n");
    printf("\tSouris+bouton gauche: rotation\n");
    printf("\tSouris mouvement vertical+bouton droit: (de)zoom\n");
}



int ViewerBasic::init()
{
	SDL_SetWindowTitle(m_window, "gKit");
    cout<<"==>ViewerBasic"<<endl;

	int major = 0;
	int minor = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << "OpenGL version " << major << " " << minor << endl;
	const GLubyte* txt;
	
	txt = glGetString(GL_VENDOR);
	if (txt) cout << "OpenGl Vendor "<< (const char*)txt<< endl;
	
	txt = glGetString(GL_RENDERER);
	if (txt) cout << "OpenGl Renderer " << (const char*)txt << endl;
	
	txt = glGetString(GL_VERSION);
	if (txt) cout << "OpenGl Version " << (const char*)txt << endl;

	txt = glGetString(GL_SHADING_LANGUAGE_VERSION);
	if (txt) cout << "OpenGl Shading Language Version " << (const char*)txt << endl;

	// etat par defaut openGL
    glClearColor(0.5f, 0.5f, 0.9f, 1);
   
    glEnable(GL_DEPTH_TEST);

    m_camera.lookat( Point(0,0,0), 30 );
    m_camera.move(99);
    
    gl.light( Point(0, 20, 20), White() );

    init_axe();
    init_grid();
    init_cube();
    init_quad();

    m_tex_debug = read_texture(3, "../data/debug2x2red.png");
    // OpenCV & dLib
    
    loadFaceDetectionModels();
    initFBO(texID);
    initCvCapture();
    
    
    //! Blendshapes
    init_BSShader();
    
    //                 [0]         [1]
    //               w0   w1     w0   w1
    tab_weights = {{0.0, 0.0}, {0.0, 0.0}};
    
    
    return 1;
}

int ViewerBasic::initFBO(GLuint &id){
    // setup FBO
    glGenFramebuffers(1, &fboID);
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return 0;
}

void ViewerBasic::init_axe()
{
    m_axe = Mesh(GL_LINES);
    m_axe.color( Color(1, 0, 0));
    m_axe.vertex( 0,  0, 0);
    m_axe.vertex( 1,  0, 0);

    m_axe.color( Color(0, 1, 0));
    m_axe.vertex( 0,  0, 0);
    m_axe.vertex( 0,  1, 0);

    m_axe.color( Color( 0, 0, 1));
    m_axe.vertex( 0,  0, 0);
    m_axe.vertex( 0,  0, 1);
}

void ViewerBasic::init_grid()
{
    m_grid = Mesh(GL_LINES);

    m_grid.color( Color(1, 1, 1));
    int i,j;
    for(i=-5;i<=5;++i)
        for(j=-5;j<=5;++j)
        {
            m_grid.vertex( -5, 0, j);
            m_grid.vertex( 5, 0,  j);

            m_grid.vertex( i, 0, -5);
            m_grid.vertex( i, 0, 5);

        }
}


void ViewerBasic::init_cube()
{
    //                          0           1           2       3           4           5       6           7
    static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
    static int f[6][4] = {    {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
    int i;

    m_cube = Mesh(GL_TRIANGLE_STRIP);
    m_cube.color( Color(1, 1, 1) );

    for (i=0;i<6;i++)
    {
        m_cube.normal(  n[i][0], n[i][1], n[i][2] );

        m_cube.texcoord( 0,0 );
        m_cube.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

        m_cube.texcoord( 1,0);
        m_cube.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

        m_cube.texcoord(0,1);
        m_cube.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

        m_cube.texcoord(1,1);
        m_cube.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

        m_cube.restart_strip();
    }
}

void ViewerBasic::init_quad()
{
    m_quad = Mesh(GL_TRIANGLE_STRIP);
    m_quad.color( Color(1, 1, 1));

    m_quad.normal(  0, 0, 1 );

    m_quad.texcoord(0,0 );
    m_quad.vertex(-1, -1, 0 );

    m_quad.texcoord(1,0);
    m_quad.vertex(  1, -1, 0 );

    m_quad.texcoord(0,1);
    m_quad.vertex( -1, 1, 0 );

    m_quad.texcoord( 1,1);
    m_quad.vertex(  1,  1, 0 );
}

Mesh ViewerBasic::init_OBJ(const char *filename){
    return read_mesh(filename);
}


/////////////////////////////
//! Gkit Render functions 
/////////////////////////////  
int ViewerBasic::render()
{
    // thread t1(&ViewerBasic::doCvCapture, this, std::ref(this->cvMatCam));
    
    // Efface l'ecran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Deplace la camera, lumiere, etc.
    manageCameraLight();

    // Donne notre camera au shader
    gl.camera(m_camera);

    // Lance la capture webcam avec openCV
    doCvCapture(cvMatCam);
    
    draw_quad(Scale(5,5,5)*Translation(10,0,0), m_tex_debug);

    draw_blendshapes();

    //renderToFBO(cvMatCam);

    // t1.join();
    


    return 1;
}

int ViewerBasic::renderToFBO(cv::Mat& cvImage){

    glBindFramebuffer(GL_FRAMEBUFFER, fboID);
    //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    
    // glBindTexture(GL_TEXTURE_2D, texID);

    // fixe les parametres de filtrage par defaut
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // transfere les donnees dans la texture
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 cvImage.cols,
                 cvImage.rows,
                 0,
                 GL_BGR,
                 GL_UNSIGNED_BYTE,
                 cvImage.ptr());

    // prefiltre la texture
    glGenerateMipmap(GL_TEXTURE_2D);

    
   // glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return 0;
    
}

/////////////////////////////
//! Gkit draw functions
/////////////////////////////  

void ViewerBasic::draw(const Transform& T,  Mesh &mesh ){
    gl.model(T);
    gl.texture(0);
    gl.lighting(false);
    gl.draw(mesh);
    gl.lighting(true);

}

void ViewerBasic::draw_axe(const Transform& T)
{
    gl.model(T);
    gl.texture(0);
    gl.lighting(false);
    gl.draw(m_axe);
    gl.lighting(true);
}


void ViewerBasic::draw_grid(const Transform& T)
{
	gl.lighting(false);
	gl.texture(0);
	gl.model(T);
	gl.draw(m_grid);
}

void ViewerBasic::draw_cube(const Transform& T)
{
	gl.lighting(true);
	gl.texture(0);
	gl.model(T);
	gl.draw(m_cube);
}

void ViewerBasic::draw_quad(const Transform& T, const GLuint &Tex)
{
	gl.lighting(true);
	gl.texture(Tex);
	gl.model(T);
	gl.draw(m_quad);
}

/////////////////////////////
//! Gkit camera functions
///////////////////////////// 

void ViewerBasic::manageCameraLight()
{
    // recupere les mouvements de la souris pour deplacer la camera, cf tutos/tuto6.cpp
    int mx, my;
    unsigned int mb= SDL_GetRelativeMouseState(&mx, &my);
    // deplace la camera
    if((mb & SDL_BUTTON(1)) &&  (mb& SDL_BUTTON(3)))                 // le bouton du milieu est enfonce
        m_camera.translation( (float) mx / (float) window_width(), 
                              (float) my / (float) window_height());         // deplace le point de rotation
    else if(mb & SDL_BUTTON(1))                      // le bouton gauche est enfonce
        m_camera.rotation( mx, my);       // tourne autour de l'objet
    else if(mb & SDL_BUTTON(3))                 // le bouton droit est enfonce
        m_camera.move( my);               // approche / eloigne l'objet
	if (key_state(SDLK_PAGEUP) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT))) { m_camera.translation(0, 0.01); }
	if (key_state(SDLK_PAGEDOWN) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT))) { m_camera.translation(0, -0.01); }
	if (key_state(SDLK_LEFT) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT))) { m_camera.translation(0.01, 0); }
	if (key_state(SDLK_RIGHT) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT))) { m_camera.translation(-0.01, 0); }
	if (key_state(SDLK_UP) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT))) { m_camera.move(1); }
	if (key_state(SDLK_DOWN) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT))) { m_camera.move(-1); }


    // Deplace la lumiere
    const float step = m_camera.radius()*0.005f;
    if (key_state(SDLK_RIGHT) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(step,0,0)); }
    if (key_state(SDLK_LEFT) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(-step,0,0)); }
    if (key_state(SDLK_UP) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(0,0,-step)); }
    if (key_state(SDLK_DOWN) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(0,0,step)); }
    if (key_state(SDLK_PAGEUP) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(0,step,0)); }
    if (key_state(SDLK_PAGEDOWN) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(0,-step,0)); }



    // (De)Active la grille / les axes
    if (key_state('h')) help();
    if (key_state('c')) { clear_key_state('c'); mb_cullface=!mb_cullface; if (mb_cullface) glEnable(GL_CULL_FACE);else glDisable(GL_CULL_FACE); }
    if (key_state('w')) { clear_key_state('w'); mb_wireframe=!mb_wireframe; if (mb_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
    if (key_state('g')) { b_draw_grid = !b_draw_grid; clear_key_state('g'); }
    if (key_state('a')) { b_draw_axe = !b_draw_axe; clear_key_state('a'); }

    gl.camera(m_camera);
    //draw(cube, Translation( Vector( gl.light()))*Scale(0.3, 0.3, 0.3), camera);
    //draw_param.texture(quad_texture).camera(camera).model(Translation( 3, 5, 0 )).draw(quad);

    // AXE et GRILLE
    gl.model( Scale(10.*step,10.0*step,10.0*step) );
    if (b_draw_grid) gl.draw(m_grid);
    if (b_draw_axe) gl.draw(m_axe);

    //  LIGHT
    gl.texture( 0 );
    gl.lighting(false);
	gl.model(Translation(Vector(gl.light()))*Scale(step, step, step));
    gl.draw(m_cube);
    gl.lighting(true);
}

/////////////////////////////
//! openCV & dlib
///////////////////////////// 


int ViewerBasic::initCvCapture(){
    cap = cv::VideoCapture(0);
    
    faceDetected = false;
    cap.set(CV_CAP_PROP_BRIGHTNESS, .5);
    
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 512);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 512);
    if(!cap.isOpened()){
        cerr << "Unable to connect to camera" << endl;
        return 1;
    }
    
    return 0;
    
}

void ViewerBasic::loadFaceDetectionModels(){
    // Load face detection and pose estimation models.
    std::cout << "dlib detector load\n";

    try
    {
        detector = dlib::get_frontal_face_detector();
        dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
    }
    catch (dlib::serialization_error &e)
    {
        cout << "You need dlib's default face landmarking model file to run this example." << endl;
        cout << "You can get it from the following URL: " << endl;
        cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        cout << endl
             << e.what() << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }

    
    
}

int ViewerBasic::doCvCapture(cv::Mat &out)
{
    using namespace dlib;
    using namespace cv;

    // Lance la capture webcam et stocke le résultat dans une matrice openCV (cv::Mat)
    try
    {
          
        // Grab a frame
        if (!cap.read(cvMatCam))
        {
            return -1;
        }
        
        //cv::flip(cvMatCam, cvMatCam, 0);

        // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
        // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
        // long as temp is valid.  Also don't do anything to temp that would cause it
        // to reallocate the memory which stores the image as that will make cimg
        // contain dangling pointers.  This basically means you shouldn't modify temp
        // while using cimg.
        cv_image<bgr_pixel> cimg(cvMatCam);
        
        // Detect faces
        std::vector<dlib::rectangle> faces = detector(cimg);;
        std::vector<dlib::full_object_detection> shapes;
        // Find the pose of each face.
        
        faceDetected = faces.size() > 0;
        for (unsigned long i = 0; i < faces.size(); ++i){
            shapes.push_back(pose_model(cimg, faces[i]));
            
            cv::Rect boundingBox = cv::Rect2f(faces.at(i).left(), faces.at(i).top(), faces.at(i).width(),  faces.at(i).height());
            cv::rectangle(cvMatCam, boundingBox, cv::Scalar(255,0,0), 2);
            drawMarker(cvMatCam, cv::Point(shapes.at(0).part(30).x(), shapes.at(0).part(30).y()), cv::Scalar(255,255,0) );

        }

        getCurrentPose(shapes, currentPose);
        for(unsigned int i=0 ; i < faceKeyPoints.size() ; i++){
            cv::Point2i keyPoint = cv::Point2i(faceKeyPoints.at(i).x,faceKeyPoints.at(i).y );
            drawMarker(cvMatCam, keyPoint, cv::Scalar(0,0,255), 0, 11, 1);  
        }

    
        // Capture des expression
        if(key_state(SDLK_1)){

            std::cout << "[saving neutral pose...]\n";

            //stockage des poids
            getCurrentPose(shapes, neutralPose);
            tab_weights[0][0] = 100.0;
            tab_weights[0][1] = 0.0;
            std::cout << "[weights for neutral pose saved !]\n";
            
            displayTab2D(tab_weights);

        }   


        if(key_state(SDLK_2)){
            std::cout << "[saving mouth open pose]\n";
            getCurrentPose(shapes, mouthOpenPose);
            tab_weights[1][0] = 0.0;
            tab_weights[1][1] = 100.0;
            std::cout << "[weights for mouth open pose saved !]\n";
            // std::cout << tab_weights[1][0]  << tab_weights[1][1];

            // for(int i=0; i < tab_weights.size() ; i++)
            //     for(int j=0; j < tab_weights[i].size(); j++){
            //         std::cout << "[" << i << "," << j << "] : " << tab_weights.at(i).at(j) << std::endl;
            // }
            displayTab2D(tab_weights);           
        }

        // Calcul des distances inverses
        
        double x_offset = faces.at(0).bl_corner().x();
        double y_offset = faces.at(0).bl_corner().y();
        double p = 2.0;
        if (!mouthOpenPose.empty())
        {
            for (unsigned int i = 0; i < 68; i++)
            {
                double dist = distance(currentPose.at(i), mouthOpenPose.at(i));
                std::cout << "d" << i << " => " <<  1 / std::pow(dist, p) << "\n";
            }
        }

        faceKeyPoints.clear();
        
        

        // Display it all on the screen
        win.clear_overlay();
        win.set_image(cimg);
        
        //affichage des coordonnes de la bounding box
        dlibDrawText(dlib::point(faces.at(0).left(), faces.at(0).top()), std::to_string(faces.at(0).tl_corner().x()) + ";" + std::to_string(faces.at(0).tl_corner().y()));
        dlibDrawText(dlib::point(faces.at(0).left(), faces.at(0).bottom()), std::to_string(faces.at(0).bl_corner().x()) + ";" + std::to_string(faces.at(0).bl_corner().y()));
        dlibDrawText(dlib::point(faces.at(0).right(), faces.at(0).top()), std::to_string(faces.at(0).tr_corner().x()) + ";" + std::to_string(faces.at(0).tr_corner().y()));
        dlibDrawText(dlib::point(faces.at(0).right(), faces.at(0).bottom()), std::to_string(faces.at(0).br_corner().x()) + ";" + std::to_string(faces.at(0).br_corner().y()));
        
        //DEBUG
        dlibDrawText(dlib::point(shapes.at(0).part(51).x(), shapes.at(0).part(51).y()), 
        std::to_string(shapes.at(0).part(51).x() - x_offset) + ";" + 
    
        std::to_string(y_offset - shapes.at(0).part(51).y()));
        
        
        
        
        win.add_overlay(render_face_detections(shapes));
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }

    
    return 0;
}

double ViewerBasic::distance(cv::Point2f a,cv::Point2f b ){
    return sqrtf(((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y)));
}


void ViewerBasic::dlibDrawText(const dlib::point &p, const string &s){
    win.add_overlay(dlib::image_window::overlay_rect(dlib::rectangle(p), dlib::rgb_pixel(255,255,0), s));
}

void ViewerBasic::displayTab2D(std::vector<std::vector<double>> tab_weights){
            for(int i=0; i < tab_weights.size() ; i++){
                for(int j=0; j < tab_weights[i].size(); j++){
                    std::cout << "[" << i << "," << j << "] : " << tab_weights.at(i).at(j) << std::endl;
                }
            }
                

}

void ViewerBasic::getCurrentPose(std::vector<dlib::full_object_detection> shapes, std::vector<cv::Point2f> &out)
{
    
    // Récupère les coordonnées des point caractéristique du visage (2D)
    if(faceDetected){
        
        for (unsigned long j = 0; j < 68; j++)
        {
            cv::Point2f point(shapes[0].part(j).x(), shapes[0].part(j).y());
            out.push_back(point);

            
        }
        // std::cout <<"[points saved]\n";
    }
         
}


////////////////////////////
//! Blendshapes functions
////////////////////////////
void ViewerBasic::init_BSShader(){
    // //! https://perso.univ-lyon1.fr/jean-claude.iehl/Public/educ/M1IMAGE/html/group__tuto__mesh__buffer.html
    program = 0;
    program = read_program("../data/shaders/blendshape.glsl");
    program_print_errors(program);

    //! chargement des differentes poses 
    m_default = read_mesh("../data/blendshapes/Neutral.obj");
    m_mouth_CL = read_mesh("../data/blendshapes/jawOpen.obj");

    //! Initialisation du tableau de position clés 
    getModelKeyPoints();

    if(m_default.normal_buffer_size() == 0)
        std::cout << "ERREUR, pas de vertex normals...";

    // cree un VAO qui va contenir la position des sommet de nos mesh 
    mVA1.create(m_default, m_mouth_CL);
    m_default.release(); 
    m_mouth_CR.release();
    
}

void ViewerBasic::draw_blendshapes(){
    //pour l'instant, les obj n'ont pas de vertex normal/color/texcoord 

    glUseProgram(program);

    Transform model = Identity() * Scale(1,1,1);
    
    Transform view = m_camera.view();
    Transform projection = m_camera.projection(window_width(), window_height(), 45);

    Transform mv = m_camera.view() * model;
    mvp = projection * mv;

    program_uniform(program, "normalMatrix", mv.normal()); // transforme les normales dans le repere camera.
    program_uniform(program, "mvpMatrix", mvp);
    program_uniform(program, "mvMatrix", mv);
    
    program_uniform(program, "mesh_color", m_default.default_color());
    program_uniform(program, "color", Red());

    program_uniform(program, "light", view(gl.light()));
    

    //weights

    float val = 0.0;

    if (key_state(SDLK_UP)) val += 1.0;
        program_uniform(program, "w0", val);
    

    // On selection notre VAO pour le vertex shader
    glBindVertexArray(mVA1.vao);
    
    
    glDrawArrays(GL_TRIANGLES, 0, mVA1.vertex_count);
  
}


void ViewerBasic::getModelKeyPoints(){
    // Initialise le tableau modelKeyPoints avec les position des sommets clés

    // Positions pour la pose Neutre

    //-----  Left Eye v1077   -----//
    modelKeyPoints.push_back(cv::Point3f(0.0312433, 0.0286743, 0.0420298));

    //-----  Left Right Eye v1095   -----//
    modelKeyPoints.push_back(cv::Point3f(-0.0312433, 0.0286743, 0.0420298));

    //-----  Left Ear v1095  -----//
    modelKeyPoints.push_back(cv::Point3f(-0.0312433, 0.0286743, 0.0420298));

    //-----    Nose   v8     -----//
    modelKeyPoints.push_back(cv::Point3f(0.0, -0.00980007, 0.0778864));

    //-----  Right Ear v58   -----//
    modelKeyPoints.push_back(cv::Point3f(-0.0716188, 0.0130347, -0.0271589));

    //-----  Left Mouth v640 -----//
    modelKeyPoints.push_back(cv::Point3f(0.0246458, -0.0419488, 0.0466527));

    //-----  Right Mouth v189 -----//
    modelKeyPoints.push_back(cv::Point3f(-0.0262095, -0.0423298, 0.0460978));

}
