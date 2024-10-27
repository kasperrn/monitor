#ifndef LABEL_H
#define LABEL_H

#include "Widget.h"
#include <string>

class Label : public Widget {
public:
    Label(const std::string &text);

    // Method to update the label text
    void SetText(const std::string &text);
    void Render() override;

private:
    std::string text;
};

#endif // LABEL_H
