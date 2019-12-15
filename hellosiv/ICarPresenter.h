#pragma once
#include <Siv3D.hpp>
#include "IFieldPresenter.h"

class ICarPresenter {
public:
    virtual const P2Body& body() const = 0;
    virtual int getSensor(const IFieldPresenter& field, const Vec2& point) const = 0;
    virtual Mat3x2 transformer() const = 0;
};