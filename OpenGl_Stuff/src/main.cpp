#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>

void error_callback(int error, const char* msg);

struct ShaderProgramSource
{
    std::string VertexShader;
    std::string FragmentShader;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    
    std::string line;
    std::stringstream ss[2];
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT =1
    };
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

static uint32_t CompileShader(uint32_t type, const std::string& source)
{
    uint32_t id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int32_t result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int32_t length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static int32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    uint32_t program = glCreateProgram();
    uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW Error" << std::endl;

    float positions[] = {
        -0.5f, -0.5f, //0 
         0.5f, -0.5f, //1
         0.5f,  0.5f, //2
        -0.5f,  0.5f, //3
    };
    
    uint32_t indices[] = {0, 1, 2,
                          2, 3, 0};

    uint32_t buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
    uint32_t ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    ShaderProgramSource source = ParseShader("res/Shaders/Basic.shader");
    uint32_t shader = CreateShader(source.VertexShader, source.FragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render Here*/
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and check buffers */
        glfwSwapBuffers(window);

        /* poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
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