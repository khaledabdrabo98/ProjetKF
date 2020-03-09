#version 330



// #define USE_NORMAL
// #define USE_LIGHT
// #define USE_ALPHATEST

// #define USE_TEXCOORD
// #define USE_COLOR


#ifdef VERTEX_SHADER

    uniform mat4 mvpMatrix;

    uniform mat4 mvMatrix;
    out vec3 vertex_position;

    #ifdef USE_TEXCOORD
        layout(location= 1) in vec2 texcoord;
        out vec2 vertex_texcoord;
    #endif

    #ifdef USE_NORMAL
        layout(location= 2) in vec3 normal;
        uniform mat4 normalMatrix;
        out vec3 vertex_normal;
    #endif

    #ifdef USE_COLOR
        layout(location= 3) in vec4 color;
        out vec4 vertex_color;
    #endif

    //\\//\\//\\//\\//\\//\\//\\//\\ Partie Blenshape
    layout(location= 0) in vec3 p_neutral;
    layout(location= 1) in vec3 p_jawOpen;
    layout(location= 2) in vec3 p_jawLeft;
    layout(location= 3) in vec3 p_jawRight;
    layout(location= 4) in vec3 p_eyeBrowsRaised;

    in vec3 neutral_vp;
    in vec3 happy_vp;
    uniform vec3 angry_vp;

    uniform float w1;
    
    uniform float w_neutral;
    uniform float w_jawOpen;
    uniform float w_jawLeft;
    uniform float w_jawRight;
    uniform float w_eyeBrowsRaised;
    //\\//\\////\\//\\////\\//\\////\\//\\////\\//\\//


    void main()
    {

        //\\//\\//\\//\\//\\//\\//\\//\\ Partie Blenshape

        // get a sum of weights and work out factors for each target
        float sum_w = w_neutral + w_jawOpen + w_jawLeft + w_jawRight + w_eyeBrowsRaised;
        float f_neutral = w_neutral /sum_w;
        float f_jawOpen = w_jawOpen / sum_w;
        float f_jawLeft = w_jawLeft / sum_w;
        float f_jawRight = w_jawRight / sum_w;
        float f_eyeBrowsRaised = w_eyeBrowsRaised / sum_w;
        


        // interpolate targets to give us current pose
        // clamp(w0, 0.0, 1.0);
        // vec3 pos = (1-w_jawOpen)*p_neutral + w_jawOpen*p_jawOpen;

        vec3 pos = (f_neutral * p_neutral) + (f_jawOpen * p_jawOpen) + (f_jawLeft * p_jawLeft) + (f_jawRight * p_jawRight) + (f_eyeBrowsRaised * p_eyeBrowsRaised) ;
        

        //\\//\\////\\//\\////\\//\\////\\//\\////\\//\\//


        gl_Position= mvpMatrix * vec4(pos, 1);
        
        vertex_position= vec3(mvMatrix * vec4(pos, 1));

        #ifdef USE_TEXCOORD
            vertex_texcoord= texcoord;
        #endif

        #ifdef USE_NORMAL
            vertex_normal= mat3(normalMatrix) * normal;
        #endif

        #ifdef USE_COLOR
            vertex_color= color;
        #endif
    }

#endif



#ifdef FRAGMENT_SHADER

#ifdef USE_TEXCOORD
    in vec2 vertex_texcoord;
    uniform sampler2D diffuse_color;
#endif

#ifdef USE_ALPHATEST
    uniform float alpha_min= 0.3;
#endif

in vec3 vertex_position;

#ifdef USE_NORMAL
    in vec3 vertex_normal;
#endif

#ifdef USE_COLOR
    in vec4 vertex_color;
#endif

#ifdef USE_LIGHT
uniform vec3 light;
uniform vec4 light_color;
#endif

uniform vec4 mesh_color= vec4(1, 1, 1, 1);

out vec4 fragment_color;

void main( )
{
    vec4 color= mesh_color;
#ifdef USE_COLOR
    color= vertex_color;
#endif

#ifdef USE_TEXCOORD
    color= color * texture(diffuse_color, vertex_texcoord);
    
    #ifdef USE_ALPHATEST
        if(color.a < alpha_min)
        //~ if(length(color.rgb) < alpha_min)
            discard;
    #endif
    
    if(color.r + color.g + color.b == 0)    // noir
    {
        // fixer une couleur debug pour indiquer qu'il faut utiliser une texture avec cet objet
        vec3 p= vertex_position * 8;
	float d= length( p - (floor(p) + 0.5));
	if(d > 1) d= 0;
        color=  vec4(d*0.8*2, d*0.4*2, 0, 1);
    }
#endif

    vec3 normal= vec3(0, 0, 1);
#ifdef USE_NORMAL
    normal= normalize(vertex_normal);
#else
    vec3 t= normalize(dFdx(vertex_position));
    vec3 b= normalize(dFdy(vertex_position));
    normal= normalize(cross(t, b));
#endif

#ifndef USE_ALPHATEST
    float cos_theta= 1;
    #ifdef USE_LIGHT
        cos_theta= max(0, dot(normal, normalize(light - vertex_position)));         // eclairage, uniquement des faces bien orientees
        color= color * light_color;
    #else
        cos_theta= normal.z; //abs(dot(normal, normalize(vertex_position)));
    #endif
    
    // hachure les triangles mal orientes
    if(gl_FrontFacing == false) // if(!gl_FrontFacing) bug sur mac ?!
    {
        ivec2 pixel= ivec2(gl_FragCoord.xy / 4) % ivec2(2, 2);
        if((pixel.x ^ pixel.y) == 0)
            color= vec4(0.8, 0.4, 0, 1);
    }
    
    color.rgb= color.rgb * cos_theta;
#endif
    
    fragment_color= color;
}
#endif
