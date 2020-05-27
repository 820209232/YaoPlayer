#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class YaoGLShader
{
public:
	YaoGLShader(char * shaderStr, int type);
	~YaoGLShader();
private:
	GLuint shader = 0;
};

