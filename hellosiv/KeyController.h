#pragma once

#include "Controller.h"

class KeyController : public Controller {
public:
    virtual void apply(Car& car, const Field& field) override {
        car.setAccsel(KeyUp.pressed() ? 1 : KeyDown.pressed() ? -1 : 0);
        car.setSteer(KeyLeft.pressed() ? -1 : KeyRight.pressed() ? 1 : 0);
    }
    inline KeyController() : Controller() { }
};