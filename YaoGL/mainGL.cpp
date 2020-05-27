#include "YaoGL/YaoGL.h"

int main() {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    int windowWidth = 1280;
    int windowHeight = 720;
    //todo core_profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //��������
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "YaoGL", NULL, NULL);

    //OpenGL�ǵ��߳�����ģʽ
    //���������߳�ͬʱ����
    glfwMakeContextCurrent(window);

    //��ʼ��glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(window)) {
        //todo ���Ʋ���

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}