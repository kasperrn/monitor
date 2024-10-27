#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <vector>
#include <memory>
#include <string>
#include "Widget.h"
#include <GLFW/glfw3.h>

class Dashboard {
public:
    // Constructor with optional kioskMode parameter (default is false)
    Dashboard(const std::string &title, int width, int height, bool kioskMode = false);
    ~Dashboard();

    bool Initialize();
    void SetBackgroundColor(float r, float g, float b);
    void AddWidget(std::shared_ptr<Widget> widget);
    void Run();
    GLFWwindow* GetWindow() const { return window; }

private:
    std::string title;
    int width, height;
    float bgColor[3];
    bool kioskMode;  // New attribute for kiosk mode
    GLFWwindow* window;
    std::vector<std::shared_ptr<Widget>> widgets;

    void Cleanup();
    void RenderWidgets();
};

#endif // DASHBOARD_H
