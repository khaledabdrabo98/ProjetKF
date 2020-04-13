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

        bool expr[MAX_EXPR];
        unsigned int cubemap_id;
        bool cubemapChanged;
        float color[4] = { 1.0f,1.0f,1.0f,1.0f };
        float translation[3] = {0.0, 0.0, 0.0}; 

        bool translationEnabled;
        float pow_interp;
        float downsample_ratio;
        bool enable_cbp;

    protected:
        
        void set_expr(unsigned int id);
        void ButtonSetExpr(const char* label,  unsigned int id );
        

    SDL_Window *m_window;
    SDL_GLContext m_context;
};



#endif