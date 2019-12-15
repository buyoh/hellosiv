#pragma once
#include "Interfaces.h"

class KeyController : public IController {
public:
    ControllerMessage apply(const ICarPresenter& car, const IFieldPresenter& field) override {
        ControllerMessage cm;
        cm.setAccsel(KeyUp.pressed() ? 1 : KeyDown.pressed() ? -1 : 0);
        cm.setSteer(KeyLeft.pressed() ? -1 : KeyRight.pressed() ? 1 : 0);
        return cm;
    }
    inline KeyController() : IController() { }
};