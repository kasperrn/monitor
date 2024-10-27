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

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    if (kioskMode) {
        // Disable window decorations and make full-screen on the primary monitor
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
        width = mode->width;
        height = mode->height;
        window = glfwCreateWindow(width, height, title.c_str(), primaryMonitor, NULL);
    } else {
        // Windowed mode with decorations
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    }

    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 100");

    // Hide the cursor if in kiosk mode
    if (kioskMode) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    // Load a default font as fallback
    LoadFont(16.0f);

    return true;
}

ImFont* Dashboard::LoadFont(float size, const std::string& fontPath) {
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = nullptr;

    if (!fontPath.empty()) {
        font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), size);
        if (!font) {
            std::cerr << "Failed to load font from " << fontPath << ", using default font.\n";
            font = io.Fonts->AddFontDefault();
        }
    } else {
        font = io.Fonts->AddFontDefault();
    }

    ImGui_ImplOpenGL3_DestroyFontsTexture();
    ImGui_ImplOpenGL3_CreateFontsTexture();
    return font;
}

void Dashboard::SetBackgroundColor(float r, float g, float b) {
    bgColor[0] = r;
    bgColor[1] = g;
    bgColor[2] = b;
}

void Dashboard::AddWidget(std::shared_ptr<Widget> widget) {
    widgets.push_back(widget);
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

void Dashboard::RenderWidgets() {
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(bgColor[0], bgColor[1], bgColor[2], 1.0f));

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

        // Ensure the cursor remains hidden if in kiosk mode
/*        if (kioskMode) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//GLFW_CURSOR_HIDDEN);
        }
*/
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
