#include "VisualPrograms.h"

class OpenGLTutorial : public VisualProgram {
public:
    ~OpenGLTutorial();
    bool init(SDL_Window* window);
    void run();
    
private:
    GLuint gProgramID = 0;
    SDL_Window* window = NULL;

    Clock* clock;
    Input* input;
    Camera* camera;
    CameraController* controller;
};