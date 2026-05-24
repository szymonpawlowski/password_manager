#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Vault.h"
#include "Gui.h"

#include <string>
#include <iostream>
#include <filesystem>
#include <GLFW/glfw3.h>

using namespace std;

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void esc_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);


    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    GLFWwindow* window = glfwCreateWindow(
        mode->width,
        mode->height,
        "Password Manager",
        monitor,
        nullptr);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    Vault vault;
    Gui gui(vault);

    glfwSetKeyCallback(window, esc_key_callback);   // ESC callback

    glfwMakeContextCurrent(window);

    // imGUI setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr;
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/segoeui.ttf", 22.0f);
    io.FontGlobalScale = 1.5f;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int displayW, displayH;
        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        gui.render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // gui clear
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}