#include "Gauge.h"
#include "imgui.h"
#include <string>

Gauge::Gauge(float initialValue) : value(initialValue) {}

void Gauge::SetValue(float newValue) {
    value = newValue;
}

void Gauge::Render() {
    ImGui::SetCursorPos(ImVec2(posX, posY));

    // Format the display text with the current value
    std::string displayText = std::to_string(static_cast<int>(value)) + "%";
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(color[0], color[1], color[2], 1.0f));
    ImGui::ProgressBar(value / 100.0f, ImVec2(width, height), displayText.c_str());
    ImGui::PopStyleColor();
}
