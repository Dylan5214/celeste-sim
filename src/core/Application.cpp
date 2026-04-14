#include "core/Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

Application::Application(const std::string& title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height) {
    Init();
}

Application::~Application() {
    Shutdown();
}

void Application::Init() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        m_Running = false;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        m_Running = false;
        return;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1); // vsync, same as yours

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        m_Running = false;
        return;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "Renderer: "       << glGetString(GL_RENDERER) << "\n";

    glViewport(0, 0, m_Width, m_Height);
}

void Application::Run() {
    float lastTime = (float)glfwGetTime();

    while (m_Running && !glfwWindowShouldClose(m_Window)) {
        float now = (float)glfwGetTime();
        float deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents();
        Update(deltaTime);
        Render();
        glfwSwapBuffers(m_Window);
    }
}

void Application::Update(float deltaTime) {
    (void)deltaTime;
}

void Application::Render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Application::Shutdown() {
    if (m_Window) glfwDestroyWindow(m_Window);
    glfwTerminate();
}