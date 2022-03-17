#include "VisualProgram.h"


VisualProgram::VisualProgram(SDL_Window* window, bool renderParam) :
    window{ window }, clock{ new Clock(renderParam) }, input{ new Input() }, renderParam{ renderParam } {

        cameraController = new UserCameraController(this->window, this->clock, this->input);
        scene = new Scene(this->window, this->clock, this->input, this->cameraController);
        
        // Enable text input
        SDL_StartTextInput();

        if (this->renderParam) {

            time_t now = time(0);
            struct tm tstruct;
            char buf[80];
            tstruct = *localtime(&now);
            strftime(buf, sizeof(buf), "%Y-%m-%dT%H%M%S", &tstruct);

            std::ostringstream oss;

            oss << "ffmpeg -r " << render_consts::SCREEN_FPS << " -f rawvideo -pix_fmt rgba -s " << 
                render_consts::SCREEN_WIDTH << "x" << render_consts::SCREEN_HEIGHT << 
                " -i - -threads 4 -y -pix_fmt yuv420p -loglevel 8 -crf 8 -vf vflip output\\" <<
                buf << ".mp4";

            std::string stringCmd = oss.str();

            // printf(stringCmd.c_str());

            const char* cmd = stringCmd.c_str();

            this->ffmpeg = _popen(cmd, "wb");

            frameBuffer = new int[render_consts::SCREEN_WIDTH*render_consts::SCREEN_HEIGHT];
        }
}

VisualProgram::~VisualProgram() {

    if ( this->renderParam ) {
        _pclose(this->ffmpeg);
    }   
}