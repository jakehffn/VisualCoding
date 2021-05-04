#pragma once

#include <GL/gl.h>

namespace render_consts {
    //Screen dimension constants
    static const int SCREEN_WIDTH = 1920;
    static const int SCREEN_HEIGHT = 1080;
    
    // static const int SCREEN_WIDTH = 800;
    // static const int SCREEN_HEIGHT = 800;

    //Color modes
    static const int COLOR_MODE_CYAN = 0;
    static const int COLOR_MODE_MULTI = 1;

    static const int SCREEN_FPS = 60;
}

namespace input_consts {

    static const float MOUSE_SPEED = 0.003f;
    static const float KEY_SPEED = 3.0f;
}

namespace objects {
    
    static const int cubeSize = 108;

    static const GLfloat cube[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    static const int cube8size = 24;

    static const GLfloat cube8[] {
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, 
        1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 
        -1.0f, 1.0f ,1.0f, 
        1.0f, 1.0f, 1.0f
    };

    static const int cube8indicessize = 12;

    static const GLuint cube8indices[] {
        0, 2, 3,
        0, 3, 1,
        0, 1, 5,
        0, 5, 4,
        0, 4, 6,
        0, 6, 2,
        1, 3, 7,
        1, 7, 5,
        2, 6, 7,
        2, 7, 3,
        4, 5, 7,
        4, 7, 6,
    };

    static const GLfloat cube8vnorms[] {
        -0.577350, -0.577350, -0.577350,
        0.816497, -0.408248, -0.408248,
        -0.408248, 0.816497, -0.408248,
        0.408248, 0.408248, -0.816497,
        -0.408248, -0.408248, 0.816497,
        0.408248, -0.816497, 0.408248,
        -0.816497, 0.408248, 0.408248,
        0.577350, 0.577350, 0.577350,
    };
}