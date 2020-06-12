#include "YaoGL/YaoGL.h"
#include "YaoImg/stb_image.h"

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

    /*float vertexs[] =
    {
          0.0f,   1.0f,   0.0f,
          -1.0f,  -1.0f,  0.0f,
          1.0f,   -1.0f,  0.0f
    };*/
    //四边形顶点位置坐标
    float vertexs[] =
    {
        //     ---- 位置 ----
          1.0f,   1.0f,   0.0f, 
          -1.0f,  1.0f,  0.0f,
          -1.0f,   -1.0f,  0.0f,
          1.0f,   -1.0f,  0.0f,
    };

    //纹理坐标
    float vertexsUV[] =
    {
          1.0f,  1.0f, 0.0f,
          0.0f,  1.0f, 0.0f,
          0.0f,  0.0f, 0.0f,
          1.0f,   0.0f, 0.0f,
    };

    unsigned int index[] =
    {
        0,1,2,
        2,0,3
    };
      
    //初始化glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //顶点几个就执行几次，几乎同时执行 
    char* vertexShaderStr = SHADER(
        #version 330\n
        layout(location = 0) in vec3 pos;
        layout(location = 1) in vec3 aTexCoord;
        out vec3 outPos;
        out vec3 TexCoord;
        void main()
        {
            outPos = pos;
            gl_Position = vec4(pos, 1.0);
            TexCoord = aTexCoord;
        }
    );

    //光栅化之后，有多少像素，就执行几次
    //outPos是每个像素经过插值之后的点
    char* fragmentShaderStr = SHADER(
        #version 330\n

        out vec4 rgbaColor;
        in vec3 outPos;
        in vec3 TexCoord;

        uniform sampler2D t;
        void main()
        {
            vec2 uv = vec2(TexCoord.x, TexCoord.y);
            rgbaColor = texture(t, uv);
        }
    );
    //rgbaColor = vec4(outPos, 1.0);
    //printf("vertexShaderStr:%s\n", vertexShaderStr);

    //VAO
    YaoVAO * VAO = new YaoVAO();
    VAO->addVertex3D(vertexs, 4, 0);
    VAO->addVertex3D(vertexsUV, 4, 1);
    VAO->setIndex(index, 6);
    VAO->bindTexture("1.jpg");

    YaoGLProgram* program = new  YaoGLProgram(vertexShaderStr, fragmentShaderStr);
    
    //program->useProgram();
    //program->setInt("t", 0);  
    //program->setInt("texture2", 1);
    while (!glfwWindowShouldClose(window)) {
        //todo 绘制操作
        glClear(GL_COLOR_BUFFER_BIT);

       /* glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        */

        program->useProgram();
        VAO->draw();

        glfwSwapBuffers(window); 
        glfwPollEvents();
    }

    delete VAO;
    delete program;
    glfwTerminate();
    return 0;
}