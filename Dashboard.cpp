#include "Dashboard.h"
#include "imgui.h"
#include "implot.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

Dashboard::Dashboard(const std::string &title, int width, int height, bool kioskMode)
    : title(title), width(width), height(height), kioskMode(kioskMode), window(nullptr) {
    bgColor[0] = 0.1f;
    bgColor[1] = 0.1f;
    bgColor[2] = 0.1f;
}

Dashboard::~Dashboard() {
    Cleanup();
}

bool Dashboard::Initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    if (kioskMode) {
   	// Get primary monitor for full-screen mode
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

        // Set width and height to match the monitor's resolution
        width = mode->width;
        height = mode->height;

        // Create a full-screen window without decorations
        window = glfwCreateWindow(width, height, title.c_str(), primaryMonitor, NULL);
    } else {
        // Create a windowed mode window with decorations
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    }

    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return true;
}

void Dashboard::Cleanup() {
    if (window) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void Dashboard::SetBackgroundColor(float r, float g, float b) {
    bgColor[0] = r;
    bgColor[1] = g;
    bgColor[2] = b;
}

void Dashboard::AddWidget(std::shared_ptr<Widget> widget) {
    widgets.push_back(widget);
}

void Dashboard::RenderWidgets() {
    // Get the size of the entire display area
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);  // Full-screen size
    ImGui::SetNextWindowPos(ImVec2(0, 0));     // Position at top-left corner

    // Begin a full-screen ImGui window without scroll bars
    ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(bgColor[0], bgColor[1], bgColor[2], 1.0f));

    // Render each widget
    for (auto& widget : widgets) {
        widget->Render();
    }

    ImGui::PopStyleColor();
    ImGui::End();
}

void Dashboard::Run() {
    if (!window) {
        std::cerr << "Window is not initialized.\n";
        return;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            std::cout << "Q key pressed, exiting..." << std::endl;
            break;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderWidgets();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    Cleanup();
}
