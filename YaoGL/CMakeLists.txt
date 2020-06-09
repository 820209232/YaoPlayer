include_directories(../3rdpart/glad/include/)
include_directories(../3rdpart/glfw/include/)
include_directories(../)

add_library(
	YaoGL
	YaoGLShader.cpp
	YaoGLProgram.cpp
	YaoVAO.cpp
	YaoGLTexture.cpp

	../3rdpart/glad/src/glad.c)

