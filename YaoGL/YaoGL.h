#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum YaoGLShaderType
{
	YAOGL_SHADER_VERTEX = 1,
	YAOGL_SHADER_FRAGMENT = 2
};

class YaoGLShader
{
public:
	YaoGLShader(char * shaderStr, YaoGLShaderType type);
	~YaoGLShader();
public:
	GLuint shader = 0;
};

class YaoGLProgram
{
public:
	YaoGLProgram(char* vertexShaderStr, char* fragmentShaderStr);
	~YaoGLProgram();
private:
	GLuint program = 0;
};

