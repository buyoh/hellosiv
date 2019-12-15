#pragma once
#include <utility>
#include <algorithm>

class ControllerMessage : public std::pair<double, double> {
    static constexpr double validate(double v) { return std::max(-1.0, std::min(1.0, v)); }
public:
    constexpr void setAccsel(double a) { this->first = validate(a); }
    constexpr void setSteer(double s) { this->second = validate(s); }
    constexpr double accsel() const { return this->first; }
    constexpr double steer() const { return this->second; }
    constexpr ControllerMessage(double _accsel = 0, double _steer = 0)
        :std::pair<double, double>(validate(_accsel), validate(_steer)) {}
};