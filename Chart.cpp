#include "Chart.h"
#include "implot.h"
#include <algorithm>

void Chart::AddDataPoint(float x, float y) {
    // Maintain a maximum number of data points (e.g., 100 points)
    if (xData.size() >= 100) {
        xData.erase(xData.begin());
        yData.erase(yData.begin());
    }
    xData.push_back(x);
    yData.push_back(y);
}

void Chart::SetLineColor(float r, float g, float b) {
    lineColor = {r, g, b};
}

void Chart::SetLineThickness(float thickness) {
    lineThickness = thickness;
}

void Chart::Render() {
    ImGui::SetCursorPos(ImVec2(posX, posY));

    // Automatically adjust axes based on data range
    if (!xData.empty() && !yData.empty()) {
        float xMin = *std::min_element(xData.begin(), xData.end());
        float xMax = *std::max_element(xData.begin(), xData.end());
        float yMin = *std::min_element(yData.begin(), yData.end());
        float yMax = *std::max_element(yData.begin(), yData.end());

        if (ImPlot::BeginPlot("Data Chart", ImVec2(width, height))) {
            ImPlot::SetupAxesLimits(xMin, xMax, yMin, yMax, ImPlotCond_Always);
            
            // Set plot style (line color and thickness)
            ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, lineThickness);
            ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(lineColor[0], lineColor[1], lineColor[2], 1.0f));

            ImPlot::PlotLine("Data", xData.data(), yData.data(), xData.size());

            // Restore plot style
            ImPlot::PopStyleColor();
            ImPlot::PopStyleVar();

            ImPlot::EndPlot();
        }
    }
}
