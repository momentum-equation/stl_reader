#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TesselationData.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

int main() {
	TesselationData Cube;
	Cube = parse_stl("Ender3-Zmotormount.stl");
	return 0;
}

//struct ShaderProgramSource
//{
//    std::string VertexSource;
//    std::string FragmentSource;
//};
//
//static ShaderProgramSource ParseShader(const std::string& filepath) {
//    std::ifstream fin(filepath);
//
//    enum class ShaderType {
//        NONE = -1,
//        VERTEX = 0,
//        FRAGMENT = 1
//    };
//
//    std::string line;
//    std::stringstream ss[2];
//
//    ShaderType type = ShaderType::NONE;
//    while (getline(fin, line)) {
//        if (line.find("#shader") != std::string::npos) {
//            if(line.find("vertex") != std::string::npos)
//                type = ShaderType::VERTEX;
//            else if(line.find("fragment") != std::string::npos)
//                type = ShaderType::FRAGMENT;
//        } 
//        else {
//            ss[(int)type] << line << '\n';
//        }
//    }
//
//    return { ss[0].str(), ss[1].str() };
//}
//
//static unsigned int CompileShader(unsigned int type, const std::string& source) {
//    unsigned int id = glCreateShader(type); // create shader object of given type
//    const char* src = source.c_str();
//
//    glShaderSource(id, 1, &src, nullptr); // macro for replacing source code in shader object
//    // id : handle, count : number of entries in string and string length array
//    // string : array of pointers to strings (double ptr)
//    // pointer to array of length of strings in string array
//
//    glCompileShader(id); // compiles source code strings stored inside 
//    // error handling: glGetShaderiv(id_of_shader_obj, *object parameter* GL_COMPILE_STATUS, 
//    // *returns the object inside* params)
//
//    int result;
//    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//    if (result == GL_FALSE) {
//        int length;
//        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//        char* message = (char*)alloca(length*sizeof(char)); // alloca allocates dynamically on the stack
//
//        glGetShaderInfoLog(id, length, &length, message);
//
//        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")<<'\n';
//        std::cout << message << std::endl;
//    }
//
//    return id;
//}
//
//static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
//    // create program
//    unsigned int program = glCreateProgram();
//    unsigned int vertex_shader = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    glAttachShader(program, vertex_shader);
//    glAttachShader(program, fragment_shader);
//    glLinkProgram(program);
//    glValidateProgram(program);
//
//    glDeleteShader(vertex_shader);
//    glDeleteShader(fragment_shader);
//
//    return program;
//}
//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    // create opengl context with the core profile
//    // setting opengl window with opengl version 3.3
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
//
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    /* Create a windowed mode window and its OpenGL context */
//    if (!window)
//    {
//        GLCall(glfwTerminate());
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    glfwSwapInterval(1); // smoothing transition
//
//    if (glewInit() != GLEW_OK)
//        std::cout << "Error!\n";
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//
//        float positions[] = {
//            0.5f, 0.5f,
//            0.5f, -0.5f,
//            -0.5f, -0.5f,
//            -0.5f,0.5f
//        };
//
//        unsigned int index_array[] = {
//            0,1,2,
//            2,3,0
//        };
//
//        // vertex array object and bind it to vertex array
//        unsigned int vao;
//        GLCall(glGenVertexArrays(1, &vao));
//        GLCall(glBindVertexArray(vao));
//
//        VertexArray va;
//        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
//
//        VertexBufferLayout layout;
//        layout.Push<float>(2);
//        va.AddBuffer(vb, layout);
//        va.Bind();
//        IndexBuffer ib(index_array, 6);
//
//        //GLCall(glEnableVertexAttribArray(0)); // index of generic vertex attribute
//        //// attributes include dimensionality, color, texture, etc
//        //// connects buffer to core vertex array object (buffer connects to vao)
//        //GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
//
//        Shader shader("res/shaders/Basic.shader");
//        shader.Bind();
//        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
//
//        va.Unbind();
//        vb.Unbind();
//        ib.Unbind();
//        shader.Unbind();
//
//        // id for the uniform in shader file
//        //GLCall(glBindVertexArray(0));
//        //GLCall(glUseProgram(0)); // un-bind shader
//        //GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // un-bind to array to be plotted
//        //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // un-bind to array to be plotted
//
//        float r = 0.0f; // modify color
//        float increment = 0.05f;
//
//        /* Loop until the user closes the window */
//        while (!glfwWindowShouldClose(window))
//        {
//            /* Render here */
//            GLCall(glClear(GL_COLOR_BUFFER_BIT));
//
//            shader.Bind();
//            shader.SetUniform4f("u_Color", 0.5f, r, 1.0, 1.0);
//
//            // vertex attrib array and attrib pointer bind array buffer and vertex buffer
//            // vertex array 
//            va.Bind();
//            ib.Bind();
//            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
//
//            if (r > 1.0f)
//                increment -= 0.05f;
//            else if (r < 0.0f)
//                increment += 0.05f;
//
//            r += increment;
//
//            glEnd();
//
//            /* Swap front and back buffers */
//            GLCall(glfwSwapBuffers(window));
//
//            /* Poll for and process events */
//            glfwPollEvents();
//        }
//    glfwTerminate();
//    return 0;
//}