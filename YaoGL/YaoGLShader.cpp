#include "YaoGL.h"

YaoGLShader::YaoGLShader(char* shaderStr, int type)
{
	shader = glCreateShader(type);

}

YaoGLShader::~YaoGLShader()
{
	if (shader != 0) {
		glDeleteShader(shader);
		shader = 0;
	}
} 