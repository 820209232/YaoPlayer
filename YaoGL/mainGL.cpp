#include "YaoGL/YaoGL.h"

int main() {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    int windowWidth = 1280;
    int windowHeight = 720;
    //todo core_profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //创建窗口
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "YaoGL", NULL, NULL);

    //OpenGL是单线程运行模式
    //不允许多个线程同时调用
    glfwMakeContextCurrent(window);

    //初始化glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(window)) {
        //todo 绘制操作

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}