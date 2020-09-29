#include <iostream>
#include <GLFW/glfw3.h>
#include <string>

void error_callback(int error, const char* msg);

int main()
{
    glfwSetErrorCallback(error_callback);

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    std::printf("Running against GLFW %i.%i.%i\n", major, minor, revision);

    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    /* Create a windowed mode window and its OpenGl Context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

    if (nullptr == window)
    {
        int code = glfwGetError(NULL);
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render Here*/
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f,  0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        
        /* Swap front and check buffers */
        glfwSwapBuffers(window);

        /* poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
#if 0 
    std::cout << "Hello World" << std::endl;
    std::cin.get();
#endif

    return 0;
}

void error_callback(int error, const char* msg) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}