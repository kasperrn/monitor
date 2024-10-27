#ifndef WIDGET_H
#define WIDGET_H

#include "imgui.h"

class Widget {
public:
    virtual void Render() = 0;
    void SetPosition(float x, float y) { posX = x; posY = y; }
    void SetSize(float width, float height) { this->width = width; this->height = height; }
    void SetColor(float r, float g, float b) { color[0] = r; color[1] = g; color[2] = b; }

protected:
    float posX = 0, posY = 0;
    float width = 100, height = 50;
    float color[3] = {1.0f, 1.0f, 1.0f}; // default color (white)
};

#endif // WIDGET_H
