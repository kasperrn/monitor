#ifndef GAUGE_H
#define GAUGE_H

#include "Widget.h"

class Gauge : public Widget {
public:
    Gauge(float initialValue = 50.0f);

    // Method to update the gauge value
    void SetValue(float value);
    void Render() override;

private:
    float value;
};

#endif // GAUGE_H
