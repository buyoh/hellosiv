#pragma once
#include "Controller.h"

class HandAiController : public Controller {
public:
    virtual void apply(Car& car, const Field& field) override {
        const auto t = Transformer2D(car.transformer());
        double ap = 0;
        for (int i = 5; i <= 15; ++i) {
            double a = Math::Pi * i / 20;
            ap += cos(a) * car.getSensor(field, { Math::Cos(a) * 30, Math::Sin(a) * 30 });
            Circle(Math::Cos(a) * 20, Math::Sin(a) * 20, 0.3).draw();
        }
        car.setAccsel(1);
        car.setSteer(-ap);
    }
    inline HandAiController() : Controller() { }
};