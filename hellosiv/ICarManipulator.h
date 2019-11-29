#pragma once
#include <Siv3D.hpp>

class ICarManipulator {
public:
    virtual void manipulate(ControllerMessage) = 0; // TODO: remove
    // virtual void setController(std::unique_ptr<IController>) = 0;
    // virtual const IController& getController() const = 0;
};