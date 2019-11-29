#pragma once

class IFieldPresenter {
public:
    virtual Vec2 getStartPos() const = 0;
    virtual double getStartAngle() const = 0;
    virtual bool isOnRoad(const Vec2& vec) const = 0;
};