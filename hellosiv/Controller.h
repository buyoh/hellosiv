#pragma once
#include "Car.h"
#include "Field.h"

class Controller {
public:
    virtual void apply(Car& car, const Field& field) = 0;
};
