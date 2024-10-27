#ifndef CHART_H
#define CHART_H

#include "Widget.h"
#include <vector>
#include <array>

class Chart : public Widget {
public:
    // Add a new data point with both x and y values
    void AddDataPoint(float x, float y);

    // Setter methods for line color and thickness
    void SetLineColor(float r, float g, float b);
    void SetLineThickness(float thickness);

    // Method to render the chart
    void Render() override;

private:
    std::vector<float> xData;      // X values
    std::vector<float> yData;      // Y values
    std::array<float, 3> lineColor = {0.0f, 0.5f, 1.0f}; // Default line color (light blue)
    float lineThickness = 1.0f;    // Default line thickness
};

#endif // CHART_H
