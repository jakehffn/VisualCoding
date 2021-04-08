#include <fstream>
#include <string>
#include <iostream>
#include "ShaderLoader.h"

ShaderLoader::ShaderLoader(GLuint gProgramID, GLuint vertexShader, GLuint fragmentShader) 
    : programID_{ gProgramID }, vertexShader_{ vertexShader }, fragmentShader_{ fragmentShader } {}

bool ShaderLoader::loadShaders(std::string vertexPath, std::string fragmentPath) {

    bool success = true;

    const GLchar* vertexSource{ getShaderSource(vertexPath) };
    const GLchar* fragmentSource{ getShaderSource(fragmentPath) };

    if (compileShader(vertexShader_, vertexSource) != GL_TRUE) {

        printf("Unable to compile vertex shader %d!\n", vertexShader_);
        printLog(vertexShader_);
        success = false;

    } else {
        // Attach vertex shader to program
		glAttachShader(programID_, vertexShader_);

        if (compileShader(fragmentShader_, fragmentSource) != GL_TRUE) {

            printf("Unable to compile fragment shader %d!\n", fragmentShader_);
            printLog(fragmentShader_);
            success = false; 

        } else {
            // Attach fragment shader to program
            glAttachShader(programID_, fragmentShader_);
            // Link program
			glLinkProgram(programID_);
            // Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(programID_, GL_LINK_STATUS, &programSuccess);

			if(programSuccess != GL_TRUE) {

				printf("Error linking program %d!\n", programID_);
				printLog(programID_);
				success = false;

            } 
        }
    }
    return success;
}

char* ShaderLoader::getShaderSource(std::string shaderPath) {

    std::ifstream file;
    char* src;
    GLsizei length;

    file.open(shaderPath.c_str());

    if (!file.is_open()) {

        printf("ShaderLoader: Failed to open file: %s\n", shaderPath.c_str());

    } else {

        // Find length of shaderSource
        file.seekg(0, std::ios::end);
        length = file.tellg();

        // Read shaderSource into src
        src = new char[length];
        file.seekg(0, std::ios::beg);
        file.read(src, length);
        file.close();
    }

    return src;
}

GLint ShaderLoader::compileShader(GLuint shader,const GLchar* shaderSource) {
    // Set source
    glShaderSource(shader, 1, &shaderSource, NULL);

    // Compile source
    glCompileShader(shader);

    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

    return shaderCompiled;
}

void ShaderLoader::printLog(GLuint glComp) {
    // Log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

	// Make sure name is shader
	if(glIsProgram(glComp)) {
		// Get info string length
		glGetProgramiv(glComp, GL_INFO_LOG_LENGTH, &maxLength);
		
		// Allocate string
		char* infoLog = new char[maxLength];
		
		// Get info log
		glGetProgramInfoLog(glComp, maxLength, &infoLogLength, infoLog);

		if( infoLogLength > 0 ) {
			// Print Log
			printf("%s\n", infoLog);
		}
		
		// Deallocate string
		delete[] infoLog;

	} else if(glIsShader(glComp)) {
		
		// Get info string length
		glGetShaderiv(glComp, GL_INFO_LOG_LENGTH, &maxLength);
		
		// Allocate string
		char* infoLog = new char[maxLength];
		
		// Get info log
		glGetShaderInfoLog(glComp, maxLength, &infoLogLength, infoLog);

		if(infoLogLength > 0) {
			// Print Log
			printf("%s\n", infoLog);
		}

		// Deallocate string
		delete[] infoLog;

	} else {
		printf("Name %d is not a shader or a program\n", glComp);
	}
}
