#version 330 core

#define USE_CUBEMAP

#ifdef VERTEX_SHADER


    #ifdef USE_CUBEMAP
        layout (location = 0) in vec3 skybox_pos;
        out vec3 skybox_texcoords;
    #endif

   

    layout (location = 0) in vec3 aPos;
    out vec3 TexCoords;
    uniform mat4 mvpMatrix;

    uniform mat4 mvMatrix;  
    out vec3 vertex_position;

    layout(location= 1) in vec3 normal;
    uniform mat4 normalMatrix;
    out vec3 vertex_normal;

    layout(location= 2) in vec2 texcoord;
    out vec2 vertex_texcoord;


    void main()
    {
        TexCoords = aPos;
        vec4 pos = mvpMatrix * vec4(aPos, 1.0);
        

        vertex_normal= mat3(normalMatrix) * normal;
        vertex_position = vec3(mvMatrix * vec4(aPos, 1.0));
        vertex_texcoord= texcoord;

        #ifdef USE_CUBEMAP
            skybox_texcoords = skybox_pos;
        #endif

        gl_Position = pos.xyzw;

        

    }  

#endif

//------------------------------------------------------FRAGMENT SHADER

#ifdef FRAGMENT_SHADER

    out vec4 FragColor;
    in vec3 TexCoords;
    uniform samplerCube skybox;

    in vec3 vertex_position;

    in vec3 vertex_normal;

    in vec2 vertex_texcoord;
    uniform sampler2D diffuse_color;
    

    uniform vec3 light;
    uniform vec4 light_color;

    uniform vec4 mesh_color= vec4(1, 1, 1, 1);

    #ifdef USE_CUBEMAP
        uniform vec3 cameraPos; 
    #endif

    void main()
    {   
        // vec3 normal= vec3(0, 0, 1);
        //! COLOR
        vec4 color= mesh_color;

        

        #ifdef USE_CUBEMAP
            // vec3 I = normalize(vertex_position - cameraPos); //vecteur incident
            // vec3 R = reflect(I, normalize(vertex_normal)); //reflection

            // color = color * vec4(texture(skybox, R).rgb, 1.0);

            color= color * texture(skybox, TexCoords);
        #endif

        //! TEXTURE ERROR CHECKING
        if(color.r + color.g + color.b == 0)    // noir
        {
            // fixer une couleur debug pour indiquer qu'il faut utiliser une texture avec cet objet
            vec3 p= vertex_position * 8;
            float d= length( p - (floor(p) + 0.5));
            if(d > 1) d= 0;
            color=  vec4(d*0.8*2, d*0.4*2, 0, 1);
        }

        //! NORMAL
        // normal= normalize(vertex_normal);

        // //! LIGHT
        // float cos_theta= 1;
        // cos_theta= max(0, dot(normal, normalize(light - vertex_position)));         // eclairage, uniquement des faces bien orientees
        // color= color * light_color;
        // color.rgb= color.rgb * cos_theta;


        
    
        
        
        //! OUT
        FragColor = color;//texture(skybox, TexCoords);
        

    }


#endif