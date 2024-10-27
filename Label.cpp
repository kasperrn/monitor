#include "Label.h"
#include "imgui.h"

Label::Label(const std::string &text) : text(text) {}

void Label::SetText(const std::string &newText) {
    text = newText;
}

void Label::Render() {
    ImGui::SetCursorPos(ImVec2(posX, posY));
    ImGui::TextColored(ImVec4(color[0], color[1], color[2], 1.0f), "%s", text.c_str());
}
