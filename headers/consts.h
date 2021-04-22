#pragma once

#include <bitset>

namespace render_consts {
    //Screen dimension constants
    // static const int SCREEN_WIDTH = 1920;
    // static const int SCREEN_HEIGHT = 1080;
    
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 800;

    //Color modes
    static const int COLOR_MODE_CYAN = 0;
    static const int COLOR_MODE_MULTI = 1;

    static const int SCREEN_FPS = 60;
}

namespace input_consts {
    enum Inputs {
        XPOS,
        YPOS,
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    static const float MOUSE_SPEED = 0.005f;
    static const float KEY_SPEED = 0.005f;
}