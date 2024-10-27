#include "Dashboard.h"
#include "Gauge.h"
#include "Chart.h"
#include "Label.h"
#include <memory>
#include <random>
#include <sstream>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    bool kioskMode = false;

    if (argc > 1 && std::strcmp(argv[1], "--kiosk") == 0) {
        kioskMode = true;
    }

    Dashboard dashboard("My Dashboard", 800, 600, kioskMode);
    if (!dashboard.Initialize()) {
        std::cerr << "Failed to initialize dashboard.\n";
        return -1;
    }

    dashboard.SetBackgroundColor(0.2f, 0.2f, 0.3f);

    auto gauge = std::make_shared<Gauge>(50.0f);
    gauge->SetPosition(10, 10);
    gauge->SetSize(200, 30);
    gauge->SetColor(0.8f, 0.0f, 0.0f);
    dashboard.AddWidget(gauge);

    auto chart = std::make_shared<Chart>();
    chart->SetPosition(10, 50);
    chart->SetSize(900, 450);
    
    // Customize line color and thickness
    chart->SetLineColor(1.0f, 0.0f, 0.0f);  // Red color
    chart->SetLineThickness(2.0f);          // Thicker line
    dashboard.AddWidget(chart);

    auto label = std::make_shared<Label>("Initial Value");
    label->SetPosition(10, 520);
    label->SetColor(0.0f, 1.0f, 0.0f);
    dashboard.AddWidget(label);

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0, 100.0);

    std::thread updateThread([&]() {
        float x = 0.0f;
        while (!glfwWindowShouldClose(dashboard.GetWindow())) {
            static float gaugeValue = 50.0f;
            gaugeValue += 0.1f;
            if (gaugeValue > 100.0f) gaugeValue = 0.0f;
            gauge->SetValue(gaugeValue);

            float newY = distribution(generator);
            chart->AddDataPoint(x, newY);
            x += 0.1f;

            std::ostringstream oss;
            oss << "Gauge Value: " << static_cast<int>(gaugeValue) << "%";
            label->SetText(oss.str());

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    dashboard.Run();
    updateThread.join();

    return 0;
}
