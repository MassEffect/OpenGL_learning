#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderClass.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
float offsetX = 0.05f;
float offsetY = 0.05f;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices [] = {
       -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,  0.5f, 0.5f, 0.0f
        };

float vertices2Triangle [] = {
        -0.85f,  0.65f, 0.f,
        -0.61f,  0.65f, 0.f,
        -0.73f,  1.0f,  0.f,

        0.85f,  0.65f, 0.f,
        0.61f,  0.65f, 0.f,
        0.73f,  1.0f,  0.f
        };

unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
        };

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("..\\source\\vertex.vs", "..\\source\\fragment.fs");
    Shader shaderTriangle("..\\source\\vertexYellow.vs", "..\\source\\fragmentYellow.fs");

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 *  sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int VAOTriangle;
    glGenVertexArrays(1, &VAOTriangle);
    glBindVertexArray(VAOTriangle);

    unsigned int VBOTriangle;
    glGenBuffers(1, &VBOTriangle);
    glBindBuffer(GL_ARRAY_BUFFER, VBOTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2Triangle), vertices2Triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 *  sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

        // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // ------
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
        glBindVertexArray(0);


        shaderTriangle.use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(VAOTriangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        shaderTriangle.setFloat("offsetX", offsetX);
        shaderTriangle.setFloat("offsetY", offsetY);
        glDrawArrays(GL_TRIANGLES, 3, 3);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VAOTriangle);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VBOTriangle);

    glfwTerminate();
    return 0;
};

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        offsetX += 0.01;
        if(offsetX > 0.15)
        {
            offsetX = 0.15;
        };
    };

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        offsetX -= 0.01;
        if(offsetX < -1.3)
        {
            offsetX = -1.3;
        };
    };

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        offsetY += 0.01;
        if(offsetY > 1.6)
        {
            offsetY = 1.6;
        };
    };

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        offsetY -= 0.01;
        if(offsetY < 0)
        {
            offsetY = 0;
        };
    };
};

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
