#pragma once
#include "IController.h"
#include "IDrawable.h"

class HandAiController : public IController, public IDrawable {
public:
    ControllerMessage apply(const ICarPresenter& car, const IFieldPresenter& field) override {
        const auto t = Transformer2D(car.transformer());
        double ap = 0;
        for (int i = 5; i <= 15; ++i) {
            double a = Math::Pi * i / 20;
            ap += cos(a) * car.getSensor(field, { Math::Cos(a) * 30, Math::Sin(a) * 30 });
        }
        return ControllerMessage{ 1, -ap };
    }

    void draw() const override {
        for (int i = 5; i <= 15; ++i) {
            double a = Math::Pi * i / 20;
            Circle(Math::Cos(a) * 20, Math::Sin(a) * 20, 0.3).draw();
        }
    }
    inline HandAiController() : IController() { }
};