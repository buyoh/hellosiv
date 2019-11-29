#pragma once
#include <Siv3D.hpp>
#include "IController.h"

class ICarBase {
public:
    virtual void setPos(const Vec2&) = 0;
    virtual void setAngle(double) = 0;
    virtual void apply() = 0;
    // virtual void assignController(std::unique_ptr<IController>) = 0;
};