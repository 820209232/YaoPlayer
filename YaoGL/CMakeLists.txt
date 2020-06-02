include_directories(../3rdpart/glad/include/)
include_directories(../3rdpart/glfw/include/)

add_library(
	YaoGL
	YaoGLShader.cpp
	YaoGLProgram.cpp
	YaoVAO.cpp

	../3rdpart/glad/src/glad.c
)

