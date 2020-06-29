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

class YaoGLTexture {
public:
	YaoGLTexture();
	~YaoGLTexture();
	int loadImg(char* imgPath);
	int createTexImage2D();
	int bindTexture();
	int setImgData(unsigned char* _imgData);

public:
	unsigned char* imgData = nullptr;

private:
	GLuint texture = 0;
	int width = 0;
	int height = 0;
	int nrChannels = 0;
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
	int setInt(const char* name, int value);
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
	int setIndex(unsigned int * index, int indexCount);
	int bindTexture(char * imgPath);
	int bindTextureWidthData(unsigned char* imgData);
	int draw();
private:
	YaoGLTexture * yaoGlTexture = nullptr;
	GLuint vao = 0;
	GLuint ebo = 0;
	std::vector<GLuint> vboList;
	int indexCount = 0;
};

