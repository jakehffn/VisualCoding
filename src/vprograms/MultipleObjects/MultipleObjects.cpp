#include "MultipleObjects.h"

MultipleObjects::~MultipleObjects() {
    // Deallocate program
    glDeleteProgram(programID);
}

void MultipleObjects::init(SDL_Window* window) {

    this->window = window;

    this->clock = new Clock();
    this->input = new Input();

    this->controller = new UserCameraController(window, clock, input);
    // CirclePath* path = new CirclePath(glm::vec3(0, 0, 0), 30, 10, 0.001);

    // this->controller = new PathCameraController(window, clock, path);
    this->camera = new Camera(window, controller);

    std::string vertexPath = "./src/vprograms/MultipleObjects/shaders/vertexShader.glsl";
    std::string fragmentPath = "./src/vprograms/MultipleObjects/shaders/fragmentShader.glsl";

    programID = LoadShaders(vertexPath.c_str(), fragmentPath.c_str());

    // Enable text input
    SDL_StartTextInput();

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void MultipleObjects::run() {
    
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    GLfloat g_vertex_buffer_data[objects::cubeSize];
    std::copy(objects::cube, objects::cube + objects::cubeSize, g_vertex_buffer_data);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };

    for (int xx = 0; xx < 108 / 9; xx++) {
        int triangle = 9 * xx;
        if (xx % 2 == 0) {
            for (int yy = 0; yy < 9; yy++) {
                g_color_buffer_data[triangle + yy] = 0.0f;
            }
        } else {
            for (int yy = 0; yy < 9; yy++) {
                g_color_buffer_data[triangle + yy] = 1.0f;
            }
        }
        
    }

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    Scene scene = Scene(MatrixID);
    Object* cube = new Object(g_vertex_buffer_data, g_color_buffer_data, sizeof(g_color_buffer_data));
    
    Instance* box1 = new Instance(cube, glm::mat4(1));
    // Instance* box2 = new Instance(cube, glm::translate(glm::mat4(1), glm::vec3(0,2,0)));
    Instance* box2 = new Instance(cube, glm::vec3(0, -2, 0));

    scene.addInstance(box1);
    scene.addInstance(box2);

    // While application is running
    while(!input->quitProgram()) {

        clock->tick();

        camera->update();
        input->update();

        glm::mat4 ProjectionMatrix = camera->getProjectionMatrix();
        glm::mat4 ViewMatrix = camera->getViewMatrix();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);


        scene.render(ProjectionMatrix, ViewMatrix);

        // Update screen
        SDL_GL_SwapWindow(window);
    }

    SDL_StopTextInput();
}