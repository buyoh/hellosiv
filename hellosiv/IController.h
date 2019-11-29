#pragma once
#include "ICarPresenter.h"
#include "IFieldPresenter.h"
#include "ControllerMessage.h"

class IController {
public:
    virtual ControllerMessage apply(const ICarPresenter& car, const IFieldPresenter& field) = 0;
};
