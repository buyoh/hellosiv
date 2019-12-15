#pragma once
#include <Siv3D.hpp>
#include "IController.h"

class ICarManipulator {
public:
    virtual void setController(std::unique_ptr<IController>) = 0;
    virtual const IController& getController() const = 0;
    virtual bool hasController() const = 0;
};