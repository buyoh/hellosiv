#pragma once
#include <Siv3D.hpp>
#include "Field.h"


class Car {
    double engine_ = 0.0;
	double accsel_;
	double steer_;
	P2Body body_;
    static constexpr double CEngineForce = 1.0;
    static constexpr double CEngineDump = 0.99;
    static constexpr double CAccselEngine = 0.1;
    static constexpr double CSteerFront = 0.4;
    static constexpr double CSteerRear = -0.1;
public:

    void initialize() {
        body_.setDamping(1.4);
        body_.setAngularDamping(2);
    }

	void setAccsel(double _accsel) {
		accsel_ = _accsel;
	}
	void setSteer(double _steer) {
		steer_ = _steer;
	}
	const P2Body& body() const {
		return body_;
	}

    void apply() {
        // const auto t = Transformer2D(Mat3x2::Rotate(body_.getAngle()).translated(body_.getPos()));

        engine_ += CAccselEngine *accsel_;
        engine_ *= CEngineDump;
        //if (body_.getVelocity().lengthSq() != 0)
        //    engine_ *= Math::Pow(Math::Abs(body_.getVelocity().normalized().dot(Vec2::UnitY().rotated(body_.getAngle()))), 4);

        auto side = body_.getVelocity().dot(-Vec2::UnitX().rotated(body_.getAngle()));
        body_.applyForce(0.05*side* Vec2::UnitX().rotated(body_.getAngle()));

        Print << engine_ << U" " << side;

        body_.applyForce(
            Vec2{ 0, CEngineForce * engine_ }.rotate(body_.getAngle() + CSteerRear*steer_),
            Vec2{ 0, -0.5 }.rotate(body_.getAngle())
        );
        body_.applyForce(
            Vec2{ 0, CEngineForce * engine_ }.rotate(body_.getAngle()+ CSteerFront *steer_),
            Vec2{ 0, 0.5 }.rotate(body_.getAngle())
        );
        // body_.applyTorque(2.0*steer_);
    }
    int getSensor(const Field& field, Vec2 point) const {
        return field.polygon().contains(body_.getPos() + point.rotated(body_.getAngle()));
    }

    Car(P2Body&& _body) : body_(_body) { initialize(); }
};
