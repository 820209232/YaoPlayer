#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>

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
	int useProgram();
private:
	GLuint program = 0;
};

class YaoVAO
{
public:
	YaoVAO();
	~YaoVAO();
	int addVertex3D(float* vertexs, int vertexCount, int layout);
	int bindVAO();
private:
	GLuint vao = 0;
	std::vector<GLuint> vboList;
};