#include <iostream>
#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int SCR_WIDTH = 1000;
unsigned int SCR_HEIGHT = 1000;
double X_center = 0;
double Y_center = 0;
double Scale = 0;
double frame_d = 0;
float loop_time = 100;
float Gamma = 1.0;


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "complex", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    float vertices[] = {
    1.0f, 1.0f, 0.0f,   // 右上角
    1.0f, -1.0f, 0.0f,  // 右下角
    -1.0f, -1.0f, 0.0f, // 左下角
    -1.0f, 1.0f, 0.0f   // 左上角
    };

    unsigned int indices[] = { // 注意索引从0开始! 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    Shader ourShader("shader.vert", "shader_set.frag");
    ourShader.use();
    ourShader.setFloat("PI", 3.1415926);

    float time_start = glfwGetTime();

    auto time_last = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        ourShader.setInt("SCR_WIDTH", SCR_WIDTH);
        ourShader.setInt("SCR_HEIGHT", SCR_HEIGHT);
        float time_now = glfwGetTime() * 0.1;

        long time_s = (std::chrono::high_resolution_clock::now() - time_last).count();
        time_last = std::chrono::high_resolution_clock::now();
        frame_d = (double)(time_s) / 1000000000;
        std::cout << 1000000000.0 / (double)(time_s) << std::endl;

        ourShader.setVec2("c", glm::vec2(sin(time_now), cos(time_now)));
        ourShader.setVec2("Center", glm::vec2(X_center, Y_center));
        ourShader.setFloat("Scale", powf(1.1, Scale));
        ourShader.setFloat("time_len", glfwGetTime()-time_start);
        ourShader.setInt("loop_time", floor(loop_time));
        ourShader.setFloat("Gamma", Gamma);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
}

void processInput(GLFWwindow* window)
{
    // 窗口关闭
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // WASD视角移动
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Y_center += powf(1.1, Scale) * frame_d;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Y_center -= powf(1.1, Scale) * frame_d;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        X_center -= powf(1.1, Scale) * frame_d;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        X_center += powf(1.1, Scale) * frame_d;

    // -+ 循环次数
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        loop_time -= 100 * frame_d;
        if (loop_time < 1) loop_time = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        loop_time += 100 * frame_d;
        if (loop_time > 500) loop_time = 500;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        loop_time = 100;
    }

    // QE控制Gamma
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        Gamma -= 0.7 * frame_d;
        if (Gamma < 0.1) Gamma = 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        Gamma += 0.7 * frame_d;
        if (Gamma > 2.3) Gamma = 2.3;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Scale -= static_cast<float>(yoffset);
    if (Scale > 20) Scale = 20;
    if (Scale < -300) Scale = -300;
}