#pragma once
#include <Siv3D.hpp>
#include "Interfaces.h"
#include "Field.h"

class Car : public ICarBase, public ICarManipulator, public ICarPresenter, public IDrawable {
    double engine_ = 0.0;
    ControllerMessage ctrl_;
	P2Body body_;
    Texture texture_;
    // unique_ptr<Controller> controller_;

    static constexpr double CEngineForceFront = 1.0;
    static constexpr double CEngineForceRear = 1.0;
    static constexpr double CEngineDump = 0.99;
    static constexpr double CAccselEngine = 0.1;
    static constexpr double CSteerFront = 0.4;
    static constexpr double CSteerRear = -0.1;

    void initialize(P2World& world) {
        const MultiPolygon carPolygon = Emoji::CreateImage(U"⬇").alphaToPolygonsCentered().simplified(0.8).scale(0.04);
        body_ = P2Body{ world.createPolygons({0, 0}, carPolygon, P2Material(0.1, 0.0, 1.0)) };
        texture_ = Texture(Emoji(U"⬇"));

        body_.setDamping(1.4);
        body_.setAngularDamping(2);
    }
public:

    void setAngle(double angle) override {
        body_.setAngle(angle);
    }
    void setPos(const Vec2& pos) override {
        body_.setPos(pos);
    }

    void manipulate(ControllerMessage cm) override { // TODO: 要らない
        ctrl_ = cm;
    }

	const P2Body& body() const override {
		return body_;
	}
    int getSensor(const IFieldPresenter& field, const Vec2& point) const override {
        return field.isOnRoad(body_.getPos() + point.rotated(body_.getAngle()));
    }

    void apply() override {
        engine_ += CAccselEngine * ctrl_.accsel();
        engine_ *= CEngineDump;
        //if (body_.getVelocity().lengthSq() != 0)
        //    engine_ *= Math::Pow(Math::Abs(body_.getVelocity().normalized().dot(Vec2::UnitY().rotated(body_.getAngle()))), 4);

        auto side = body_.getVelocity().dot(-Vec2::UnitX().rotated(body_.getAngle()));
        body_.applyForce(0.05*side* Vec2::UnitX().rotated(body_.getAngle()));

        body_.applyForce(
            Vec2{ 0, CEngineForceFront * engine_ }.rotate(body_.getAngle() + CSteerRear * ctrl_.steer()),
            Vec2{ 0, -0.5 }.rotate(body_.getAngle())
        );
        body_.applyForce(
            Vec2{ 0, CEngineForceRear * engine_ }.rotate(body_.getAngle()+ CSteerFront * ctrl_.steer()),
            Vec2{ 0, 0.5 }.rotate(body_.getAngle())
        );
    }
    Mat3x2 transformer() const override {
        return Mat3x2::Rotate(body_.getAngle()).translated(body_.getPos());
    }

    void draw() const override {
        texture_.scaled(0.04).rotated(body_.getAngle()).drawAt(body_.getPos());
    }

    inline explicit Car(P2World& world) { initialize(world); }
};
