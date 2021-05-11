#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
using namespace std;

class Shader{
public:
    int program;
    Shader(const char* vertexPath, const GLchar *fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filepath
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;
        // ensures ifstream objects can throw exceptions
        vShaderFile.exceptions(ifstream::badbit);
        fShaderFile.exceptions(ifstream::badbit);
        
        try{
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(ifstream::failure e)
        {
            cout << "ERROR:SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
        }
        
        // vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexShaderSource = vertexCode.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentShaderSource = fragmentCode.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
        // link shaders
        this->program = glCreateProgram();
        glAttachShader(this->program, vertexShader);
        glAttachShader(this->program, fragmentShader);
        glLinkProgram(this->program);
        
        // check for linking errors
        glGetProgramiv(this->program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(this->program, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        
        
        
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
    }
    
    // use the current shader
    void use()
    {
        glUseProgram(this->program);
    }
};

#endif
