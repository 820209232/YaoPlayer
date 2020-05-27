#include "YaoGL.h"

YaoGLProgram::YaoGLProgram(char* vertexShaderStr, char* fragmentShaderStr)
{
	program = glCreateProgram();
	YaoGLShader vertexShader(vertexShaderStr, YaoGLShaderType::YAOGL_SHADER_VERTEX);
	YaoGLShader fragmentShader(fragmentShaderStr, YaoGLShaderType::YAOGL_SHADER_FRAGMENT);

	glAttachShader(program, vertexShader.shader);
	glAttachShader(program, fragmentShader.shader);

	glLinkProgram(program);

	GLint logLen = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
	if (logLen > 0) {
		char* log = (char*)malloc(logLen);
		glGetProgramInfoLog(program, logLen, NULL, log);
		printf("program log:%s", log);
		free(log);
	}

}

YaoGLProgram::~YaoGLProgram()
{
	if (program != 0) {
		glDeleteProgram(program);
		program = 0;
	}
}