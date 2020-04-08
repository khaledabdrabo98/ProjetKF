#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include <ViewerBasic.h>

using namespace std;

#define SCREEN_W 1024
#define SCREEN_H 768

#define MAX_POSES 5


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
    m_camera.move(50);
    
    gl.light( Point(0, 0, 10), White() );
    
    init_axe();
    init_grid();
    init_cube();
    init_quad();
    init_skybox();
    init_tex_cubemap();

    m_tex_debug = read_texture(3, "../data/debug2x2red.png");
    
    pnp_currentPose = 0;
    iteration_doCapture = 0;

    // OpenCV & dLib
    loadFaceDetectionModels();

    //! Blendshapes
    init_blendshapes();

    // 3D model points.
    model_points.push_back(cv::Point3d(0.0f, 0.0f, 0.0f));            // Nose tip
    model_points.push_back(cv::Point3d(0.0f, -33.0f, -6.5f));         // Chin
    model_points.push_back(cv::Point3d(-22.5f, 17.0f, -13.5f));       // Left eye left corner
    model_points.push_back(cv::Point3d(22.5f, 17.0f, -13.5f));        // Right eye right corner
    model_points.push_back(cv::Point3d(-15.0f, -15.0f, -12.5f));      // Left Mouth corner
    model_points.push_back(cv::Point3d(15.0f, -15.0f, -12.5f));       // Right mouth corner
    
    return 1;
}

void ViewerBasic::init_axe(){
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

void ViewerBasic::init_grid(){
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
                             
    static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
    static int f[6][4] = {    {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    
    static float n[6][3] = { {0,1,0}, {0,-1,0}, {-1,0,0}, {1,0,0}, {0,0,-1}, {0,0,1} };
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

void ViewerBasic::init_skybox(){

    m_skybox = read_mesh("../data/cube.obj");//Mesh(GL_TRIANGLES);
    m_skybox.color( Color(1, 1, 1) );

    //VAO
    std::vector<Mesh> tab_mesh;
    tab_mesh.push_back(m_skybox);
    cubemap_buffer.create(tab_mesh);
    
}

void ViewerBasic::init_tex_cubemap()
{  
    // m_skybox = Mesh(GL_TRIANGLE_STRIP);

    std::string id = to_string(win.cur_cubemap_id);
    
    std::vector<std::string> faces = 
    {
        "../data/cubemap/0"+id+"/x_pos.jpg",
        "../data/cubemap/0"+id+"/x_neg.jpg",
        "../data/cubemap/0"+id+"/y_pos.jpg",
        "../data/cubemap/0"+id+"/y_neg.jpg",
        "../data/cubemap/0"+id+"/z_neg.jpg",
        "../data/cubemap/0"+id+"/z_pos.jpg"
    };
    
    // cubemap split in 6 faces 
    m_env_map = make_texture_cubemap(faces) ;
    
    
    program_cubemap = read_program("../data/shaders/cubemap.glsl");
    program_print_errors(program_cubemap);


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

/////////////////////////////
//! Gkit Render functions 
/////////////////////////////  
int ViewerBasic::render()
{
    // Efface l'ecran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Deplace la camera, lumiere, etc.
    manageCameraLight();

    // Donne notre camera au shader
    gl.camera(m_camera);

    // Lance la capture webcam avec openCV
    doCapture(win.getCVMatCam());
    
    draw_skybox(Scale(20,20,20));

    draw_blendshapes();

    return 1;
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

/*int ViewerBasic::initCvCapture(){
    cap = cv::VideoCapture(-1); 
    
    faceDetected = false;
    cap.set(10, .5); 
    
    cap.set(4, 512);
    cap.set(3, 512);
    if(!cap.isOpened()){
        cerr << "Unable to connect to camera" << endl;
        return 1;
    }
    
    return 0;
}*/

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

void ViewerBasic::computePnP(){
    
    //need to make sure that there is at least 1 face present to use the PnP function
    if(faceDetected){

        image_points.push_back((currentPose_stabilizer0[33] + currentPose_stabilizer1[33] + currentPose_stabilizer2[33])/3);    // Nose tip
        image_points.push_back((currentPose_stabilizer0[8]  + currentPose_stabilizer1[8]  + currentPose_stabilizer2[8])/3 );    // Chin
        image_points.push_back((currentPose_stabilizer0[45] + currentPose_stabilizer1[45] + currentPose_stabilizer2[45])/3);    // Left eye left corner
        image_points.push_back((currentPose_stabilizer0[36] + currentPose_stabilizer1[36] + currentPose_stabilizer2[36])/3);    // Right eye right corner
        image_points.push_back((currentPose_stabilizer0[54] + currentPose_stabilizer1[54] + currentPose_stabilizer2[54])/3);    // Left Mouth corner
        image_points.push_back((currentPose_stabilizer0[48] + currentPose_stabilizer1[48] + currentPose_stabilizer2[48])/3);    // Right mouth corner
        
        // PnP functions
        // Camera internals
        double focal_length = win.getCVMatCam().cols; // Approximate focal length
        cv::Point2d center = cv::Point2d(win.getCVMatCam().cols/2, win.getCVMatCam().rows/2);
        cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << focal_length, 0, center.x, 0 , focal_length, center.y, 0, 0, 1);
        cv::Mat dist_coeffs = cv::Mat::zeros(4,1,cv::DataType<double>::type); // Assuming no lens distortion
        
        rotation_vector; // Rotation in axis-angle form
        translation_vector;

        std::vector<cv::Mat> rotation_mean;
        
        // Solve for pose
        solvePnP(model_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector);

        
        // Project a 3D point (0, 0, 1000.0) onto the image plane.
        // We use this to draw a line sticking out of the nose
        
        std::vector<cv::Point3d> nose_end_point3D;
        std::vector<cv::Point2d> nose_end_point2D;
        nose_end_point3D.push_back(cv::Point3d(0,0,1000));
        
        projectPoints(nose_end_point3D, rotation_vector, translation_vector, camera_matrix, dist_coeffs, nose_end_point2D);
        
        
        for(int i=0; i < image_points.size(); i++){
            circle(win.getCVMatCam(), image_points[i], 3, cv::Scalar(0,0,255), -1);
        }
        
        cv::line(win.getCVMatCam(),image_points[0], nose_end_point2D[0], cv::Scalar(255,0,0), 2);
        
        transformModel = Translation(translation_vector.at<double>(0)/1000.0 , translation_vector.at<double>(1)/1000.0 , translation_vector.at<double>(2)/1000.0); 
             
        rotationModel = RotationX(rotation_vector.at<double>(0)*180.0/M_PI) * RotationY(rotation_vector.at<double>(1)*180.0/M_PI) * RotationZ(rotation_vector.at<double>(2)*180.0/M_PI);
    }

    image_points.clear();
}

void ViewerBasic::inputWeights(std::vector<dlib::full_object_detection> tab_shapes){
    // Capture des expression
    if(win.is_expression_active(0)){
        std::cout << "[saving neutral pose...]\n";
        getPose(tab_shapes, p_neutral, 0);
        win.set_active_expression(0, false);

    }

    if(win.is_expression_active(1)){
        std::cout << "[Saving pose : Jaw Open]\n";
        getPose(tab_shapes, p_jawOpen, 1);
        win.set_active_expression(1, false);
        
    }

    if(win.is_expression_active(2)){
        std::cout << "[Saving pose : Jaw Left]\n";
        getPose(tab_shapes, p_jawLeft, 2);
        win.set_active_expression(2, false);
        
    }

    if(win.is_expression_active(3)){
        std::cout << "[Saving  jaw right pose]\n";
        getPose(tab_shapes, p_jawRight, 3);
        win.set_active_expression(3, false);
        
    }

    if(win.is_expression_active(4)){
        std::cout << "[Saving eyebrows up]\n";
        getPose(tab_shapes, p_eyeBrowsRaised, 4);
        win.set_active_expression(4, false);
        
    }

    if(win.cubemapChanged){
        std::cout << "[Changing cubemap]\n";
        id_cubemap = win.cur_cubemap_id;
        init_tex_cubemap();
        win.cubemapChanged = false;
    }

    
    if (!p_neutral.empty() && !p_jawOpen.empty() &&
        !p_jawLeft.empty() && !p_jawRight.empty() && !p_eyeBrowsRaised.empty()){
        w_neutral = compute_weight(currentPose, p_neutral);
        w_jawOpen = compute_weight(currentPose, p_jawOpen);
        w_jawLeft = compute_weight(currentPose, p_jawLeft);
        w_jawRight = compute_weight(currentPose, p_jawRight);
        w_eyeBrowsRaised = compute_weight(currentPose, p_eyeBrowsRaised);   
    }
}

int ViewerBasic::doCapture(cv::Mat &out)
{
    // Lance la capture webcam et stocke le résultat dans une matrice openCV (cv::Mat)
    try
    {
        // Grab a frame
        if (!win.getCap().read(win.getCVMatCam())){
            return -1;
        }
        
        dlib::cv_image<dlib::bgr_pixel> cimg(win.getCVMatCam());
        
        // Detect faces
        std::vector<dlib::rectangle> faces = detector(cimg);
        std::vector<dlib::full_object_detection> shapes;
        
        // Find the pose of each face.
        faceDetected = faces.size() > 0;

        for (unsigned long i = 0; i < faces.size(); ++i){
            shapes.push_back(pose_model(cimg, faces[i]));
            
            cv::Rect boundingBox = cv::Rect2f(faces.at(i).left(), faces.at(i).top(), faces.at(i).width(),  faces.at(i).height());
            cv::rectangle(win.getCVMatCam(), boundingBox, cv::Scalar(255,0,0), 2);
        }

        getPose(shapes, currentPose, 5);
        for(unsigned int i=0 ; i < currentPose.size() ; i++){
            cv::Point2i keyPoint = cv::Point2i(currentPose.at(i).x,currentPose.at(i).y );
            drawMarker(win.getCVMatCam(), keyPoint, cv::Scalar(0,0,255), 0, 11, 1);  
        }

        if(faceDetected){
            inputWeights(shapes);
            
            if(iteration_doCapture == 0){
                currentPose_stabilizer0 = currentPose;
                currentPose_stabilizer1 = currentPose;
                currentPose_stabilizer2 = currentPose;
            }
            iteration_doCapture++;
            switch (pnp_currentPose){
                case 0:
                    currentPose_stabilizer0 = currentPose;
                    pnp_currentPose++;
                    break;
                case 1:
                    currentPose_stabilizer1 = currentPose;
                    pnp_currentPose++;
                    break;
                case 2:
                    currentPose_stabilizer2 = currentPose;
                    pnp_currentPose = 0;
                    break;
            }
            computePnP();

            faceKeyPoints.clear();
            currentPose.clear();
        }
        // Display it all on the screen
        win.displayWin(cimg, shapes);

        // Display debug messages on screen for poses
        for(unsigned int i=0 ; i < MAX_POSES ; ++i){
            if(pose_taken[i]) {
                print_pose_debug(i);
            }
        }
        

    }catch (exception &e){
        cout << e.what() << endl;
    }
    
    return 0;
}

double ViewerBasic::compute_weight(std::vector<cv::Point2f> currentPose, std::vector<cv::Point2f> expression){
    double sum_w, sum_dist = 0;
    double weight = 0;
    double prec = 0;
    for (unsigned int i = 0; i < 68; i++){

        double x_offset = currentPose.at(27).x - expression.at(27).x;
        double y_offset = currentPose.at(27).y - expression.at(27).y;

        double dist = distance(cv::Point2d(currentPose.at(i).x, currentPose.at(i).y),
                               cv::Point2d(expression.at(i).x + x_offset, expression.at(i).y + y_offset));

        // smooth
        
        dist = pow(dist, .20);
    
        sum_dist += dist;
        if (dist == 0.0) dist = 0.01;
            
        sum_w += 1 / (dist);

        weight = (sum_w / (sum_dist)) - 0.2;
        if (weight > 1.0) weight = 1.0;
        if (weight < 0.1) weight = 0.01;

        // std::cout << "Sum of distances | Sum of Weights | Weight value : " << sum_dist << " | " << sum_w << " | " << val << "\n";
        drawMarker(win.getCVMatCam(), cv::Point2d(expression.at(i).x + x_offset, expression.at(i).y + y_offset) , cv::Scalar(255, 255, 0), 0, 10);
        sum_w = 0;
        sum_dist = 0;
    }

    return weight;

}

double ViewerBasic::distance(cv::Point2f a,cv::Point2f b ){
    return sqrtf( std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2) );
}

void ViewerBasic::print_pose_debug(unsigned int id){
    // Afficge à l'écran un message de debug pour la capture des poses.
    dlib::rgb_pixel WHITE(255,255,255);
    dlib::rgb_pixel GREEN(0,255,0);
    win.dlibDrawText(dlib::point(10,10), WHITE, "projetkf - demo lifprojet");
    switch(id) {
            case 0:
                win.dlibDrawText(dlib::point(10,35 + id*15),GREEN, "SAVED : neutral_pose");
            break;

            case 1:
                win.dlibDrawText(dlib::point(10,35 + id*15),GREEN, "SAVED : jaw_open pose");
            break;

            case 2:
                win.dlibDrawText(dlib::point(10,35 + id*15),GREEN, "SAVED : jaw_left pose");
            break;
            case 3:
                win.dlibDrawText(dlib::point(10,35 + id*15),GREEN, "SAVED : jaw_right pose");
            break;
            
            case 4:
                win.dlibDrawText(dlib::point(10,35 + id*15),GREEN, "SAVED : eyebrows_up pose");
            break;
                
    }
}

void ViewerBasic::getPose(std::vector<dlib::full_object_detection> shapes, std::vector<cv::Point2f> &out, unsigned int id){
    // Récupère les coordonnées des point caractéristique du visage (2D)
    
    if(faceDetected){
        for (unsigned long j = 0; j < 68; j++){
            cv::Point2f point(shapes[0].part(j).x(), shapes[0].part(j).y());
            out.push_back(point);            
        }
    }

    if(id < MAX_POSES) {
        pose_taken[id] = true;
    }
    
         
}


////////////////////////////
//! Blendshapes functions
////////////////////////////

void ViewerBasic::init_blendshapes(){
    // //! https://perso.univ-lyon1.fr/jean-claude.iehl/Public/educ/M1IMAGE/html/group__tuto__mesh__buffer.html
    program_blendshape = 0;
    program_blendshape = read_program("../data/shaders/blendshape.glsl");
    program_print_errors(program_blendshape);

    //! chargement des differentes poses
    m_neutral = read_mesh("../data/blendshapes/Neutral.obj");
    m_jawOpen = read_mesh("../data/blendshapes/jawOpen.obj");
    m_jawLeft = read_mesh("../data/blendshapes/mouthSmileLeft.obj");
    m_jawRight = read_mesh("../data/blendshapes/mouthSmileRight.obj");
    m_eyeBrowsRaised = read_mesh("../data/blendshapes/browInnerUp.obj");


    if(m_neutral.normal_buffer_size() == 0)
        std::cout << "ERREUR, pas de vertex normals...";

    std::vector<Mesh> tabMesh;
    tabMesh.push_back(m_neutral);
    tabMesh.push_back(m_jawOpen);
    tabMesh.push_back(m_jawLeft);
    tabMesh.push_back(m_jawRight);
    tabMesh.push_back(m_eyeBrowsRaised);
    
    // cree un VAO qui va contenir la position des sommet de nos mesh 
    mesh_buffer.create(tabMesh);
    m_neutral.release(); 
    m_jawOpen.release();
    m_jawLeft.release();
    m_jawRight.release();
    m_eyeBrowsRaised.release();
 
}

void ViewerBasic::draw_blendshapes(){
    //pour l'instant, les obj n'ont pas de vertex normal/color/texcoord 
    glUseProgram(program_blendshape);
    
    Transform model = Identity() * Scale(80,80,80);
    
    Transform view = m_camera.view() ;
    Transform projection = m_camera.projection(window_width(), window_height(), 45);

    Transform mv = view * model * transformModel * rotationModel;
    mvp = projection * mv;

    program_uniform(program_blendshape, "normalMatrix", mv.normal()); // transforme les normales dans le repere camera.
    program_uniform(program_blendshape, "mvpMatrix", mvp);
    program_uniform(program_blendshape, "mvMatrix", mv);
    
    program_uniform(program_blendshape, "mesh_color", m_neutral.default_color());
    program_uniform(program_blendshape, "light", view(gl.light()));
    program_uniform(program_blendshape, "light_color", White());

    program_uniform(program_blendshape, "w_jawOpen", w_jawOpen);
    program_uniform(program_blendshape, "w_jawLeft", w_jawLeft);
    program_uniform(program_blendshape, "w_jawRight", w_jawRight);
    program_uniform(program_blendshape, "w_eyeBrowsRaised", w_eyeBrowsRaised);

    //! CUBEMAP
    program_uniform(program_blendshape, "cameraPos", m_camera.position());

    glBindVertexArray(mesh_buffer.vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_env_map);
    glDrawArrays(GL_TRIANGLES, 0, mesh_buffer.vertex_count);
    glBindVertexArray(0);
    
}

void ViewerBasic::removeTranslationInMat44(float mat[4][4] ) {
    for (int i = 0; i < 3; i++)
    {
        mat[i][3] = 1.0;
    }
}

void ViewerBasic::draw_skybox(const Transform& T)
{   
    
    glDepthMask(GL_FALSE);
    
	glUseProgram(program_cubemap);

    // VIEW
    //Transform remove_translation = Transform( Vector(0.,0.,0.), Vector(0.,0.,0.), Vector(0.,0.,0.), -1.0*m_camera.view()[3] );

    Transform model = Identity()  * T;
    Transform view = m_camera.view();
    
    // On fixe la translation dans la matrice de vue
    // La camera ne s'approchera/s'éloignera jamais
    // => Donne l'impression que la skybox est très grande
    removeTranslationInMat44(view.m);

    Transform projection = m_camera.projection(window_width(), window_height(), 45);
    Transform mv = view * model; //* transformModel * rotationModel;
    Transform mvp = projection * mv;


    //std::cout << mvp << std::endl;

    program_uniform(program_cubemap, "mvpMatrix", mvp);
    program_uniform(program_cubemap, "normalMatrix", mv.normal()); // transforme les normales dans le repere camera.

    program_uniform(program_cubemap, "mvMatrix", mv);

    program_uniform(program_cubemap, "light", view(gl.light()));
    program_uniform(program_cubemap, "light_color", White());

    glBindVertexArray(cubemap_buffer.vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP_SEAMLESS, m_env_map);
    glDrawArrays(GL_TRIANGLES, 0, cubemap_buffer.vertex_count);
    glBindVertexArray(0);

    glDepthMask(GL_TRUE);
}



