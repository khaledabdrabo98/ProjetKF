#ifndef GUI_H
#define GUI_H

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "SDL.h"

#include <algorithm>

const int MAX_CUBEMAP_ID = 3;
const int MAX_EXPR = 5;

class Gui 
{
    public:
        Gui();
        ~Gui();
        
        void init(SDL_Window *window, SDL_GLContext context);
        void draw();

        //!Contient l'état d'une expression (sauvegardée ou non)
        bool expr[MAX_EXPR];   
        //! Id de la cubemap actuellement affichée
        unsigned int cubemap_id; 
        //! Permet de notifier au prog. principal le changement 
        bool cubemapChanged;   
        //!Valeurs du color picker 
        float color[4] = { 1.0f,1.0f,1.0f,1.0f }; 
        //!Valeurs du slider de translation
        float translation[3] = {0.0, 0.0, 0.0};

        //!Active ou desactive le tracking du visage
        bool translationEnabled;
         //!Sensibilié de l'interpolation
        float pow_interp;  
        //!Facteur de diminution de la resolution de capture
        float downsample_ratio;
        //!Active ou desactive la cubemap
        bool enable_cbp;    

    protected:
        
        void set_expr(unsigned int id);
        void ButtonSetExpr(const char* label,  unsigned int id );
        

    SDL_Window *m_window;
    SDL_GLContext m_context;
};



#endif