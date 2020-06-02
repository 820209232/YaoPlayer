#include "YaoGL/YaoGL.h"

#define STRINGIZE(x) #x
#define SHADER(shader) "" STRINGIZE(shader)

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

    float vertexs[] =
    {
          0.0f,   1.0f,   0.0f,
          -1.0f,  -1.0f,  0.0f,
          1.0f,   -1.0f,  0.0f
    };
    
    //初始化glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //顶点几个就执行几次，几乎同时执行 
    char* vertexShaderStr = SHADER(
        #version 330\n
        layout(location = 0) in vec3 pos;
        out vec3 outPos;
        void main()
        {
            outPos = pos;
            gl_Position = vec4(pos, 1.0);
        }
    );

    //光栅化之后，有多少像素，就执行几次
    //outPos是每个像素经过插值之后的点
    char* fragmentShaderStr = SHADER(
        #version 330\n

        out vec4 rgbaColor;
        in vec3 outPos;
        void main()
        {
            rgbaColor = vec4(outPos, 1.0);
        }
    );

    //printf("vertexShaderStr:%s\n", vertexShaderStr);
    
    //VAO
    YaoVAO * VAO = new YaoVAO();
    VAO->addVertex3D(vertexs, 3, 0);

    YaoGLProgram* program = new  YaoGLProgram(vertexShaderStr, fragmentShaderStr);
    

    while (!glfwWindowShouldClose(window)) {
        //todo 绘制操作
        glClear(GL_COLOR_BUFFER_BIT);
        program->useProgram();
        VAO->bindVAO();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete VAO;
    delete program;
    glfwTerminate();
    return 0;
}