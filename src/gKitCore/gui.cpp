/**
 * @file gui.cpp
 *
 * @brief Classe representant l'interface graphique
 *
 * @author Féras Ghandouri
 * 
 */

#include "gui.h"

Gui::Gui() 
{
    cubemap_id = 0;
    translationEnabled = false;
    downsample_ratio = 1.0;
    pow_interp = 1.5;
    enable_cbp = false;
     
}

/** Initialise ImGui
*
*   @brief Initialise ImGui avec le contexte OpenGL et fenêtre SDL
*
*   @param window  Fenêtre SDL
*   @param context Contexte OpenGL
*/


void Gui::init(SDL_Window *window, SDL_GLContext context)
{
    m_window = window;
    m_context = context;
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsClassic();
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 330");
}

/** Setter 
*
*   @brief Fonction de callback : enregistre le choix de l'utilisateur
*
*   @param id  Id de l'expression à choisir
*
*/


void Gui::set_expr(unsigned int id)
{
    if(id >= 0 && id < MAX_EXPR)
        expr[id] = true;
}


/** Setter 
*
*   @brief Bouton ImGui
*
*   @param label  Texte du bouton
*   @param id     Id de l'element choisi
*/


void Gui::ButtonSetExpr(const char* label, unsigned int id ) {
    static bool isToggled = false;

    int pushedColors = 0;

    ImGui::SetCursorPosX(ImGui::GetWindowWidth()/4.0);
    if(ImGui::Button(label, ImVec2(200, 25))) {
       
        isToggled = true;
        set_expr(id);
    }

    ImGui::PopStyleColor(pushedColors);

    
    
}

/**  
*
*   @brief Affichage de l'interface ImGui
*
*/

void Gui::draw()
{

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_window);
    
    ImGui::NewFrame();
    ImGui::SetWindowSize(ImVec2(400, 400));

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Configutateur"); // Create a window called "Hello, world!" and append into it.
        // Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
        ImGui::NewLine();
        ImGui::Text("Set Expressions");
        ImGui::NewLine();

        
        ButtonSetExpr("Neutral", 0);
        ButtonSetExpr("Mouth Open", 1);
        ButtonSetExpr("Jaw Left", 2);
        ButtonSetExpr("Jaw Right", 3);
        ButtonSetExpr("Eyebrows Up", 4);

        ImGui::NewLine();
        ImGui::NewLine();

        
        if (ImGui::Button("Enable/Disable Cubemap")) enable_cbp = !enable_cbp;
        // Cubemap selector
        if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { cubemap_id = std::max(0, (int)cubemap_id-1); cubemapChanged=true; }
        ImGui::SameLine();
        ImGui::Text("Cubemap selected = %d", cubemap_id);
        ImGui::SameLine();
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { cubemap_id = std::min(MAX_CUBEMAP_ID, (int)cubemap_id+1); cubemapChanged=true;}

        ImGui::NewLine();
        ImGui::NewLine();

        // Sliders
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(9/7.0f, 0.6f, 0.6f));
        ImGui::SliderFloat3(" Mesh position", translation, -10.0, 10.0);
        ImGui::NewLine();
        // color picker
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(2/7.0f, 0.6f, 0.6f));
        ImGui::ColorEdit3(" Light color", color);

        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(3/7.0f, 0.6f, 0.6f));
        if(ImGui::Button("Enable Translation")) translationEnabled = true;
        ImGui::NewLine();
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(4/7.0f, 0.6f, 0.6f));
        ImGui::SliderFloat("Interpolation power", &pow_interp, 0, 10.0);
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(5/7.0f, 0.6f, 0.6f));
        ImGui::SliderFloat("Downsampling", &downsample_ratio, 1, 10);

        ImGui::PopStyleColor(5);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::SetCursorPosY(500);
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}



Gui::~Gui()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

