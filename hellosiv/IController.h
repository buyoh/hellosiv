#pragma once
#include "ICarManipulator.h"
#include "ICarPresenter.h"
#include "IFieldPresenter.h"
#include "ControllerMessage.h"

class IController {
protected:
public:
    virtual ControllerMessage apply(const ICarPresenter& car, const IFieldPresenter& field) = 0;
};
