#pragma once
#include "Interfaces.h"

class KeyController : public IController {
public:
    void apply(ICarManipulator& manipulator, const ICarPresenter& car, const IFieldPresenter& field) override {
        manipulator.setAccsel(KeyUp.pressed() ? 1 : KeyDown.pressed() ? -1 : 0);
        manipulator.setSteer(KeyLeft.pressed() ? -1 : KeyRight.pressed() ? 1 : 0);
    }
    inline KeyController() : IController() { }
};