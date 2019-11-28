#pragma once
#include <Siv3D.hpp>
#include "Field.h"

class Car {
    double engine_ = 0.0;
	double accsel_;
	double steer_;
	P2Body body_;
    static constexpr double CEngineForceFront = 1.0;
    static constexpr double CEngineForceRear = 1.0;
    static constexpr double CEngineDump = 0.99;
    static constexpr double CAccselEngine = 0.1;
    static constexpr double CSteerFront = 0.4;
    static constexpr double CSteerRear = -0.1;
	// unique_ptr<Controller> controller_;
public:

    void initialize() {
        body_.setDamping(1.4);
        body_.setAngularDamping(2);
    }

    void setAngle(double angle) {
        body_.setAngle(angle);
    }
    void setPos(const Vec2& pos) {
        body_.setPos(pos);
    }

	void setAccsel(double _accsel) {
		accsel_ = std::min<double>(1.0, std::max<double>(-1.0, _accsel));
	}
	void setSteer(double _steer) {
		steer_ = std::min<double>(1.0, std::max<double>(-1.0, _steer));
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

        body_.applyForce(
            Vec2{ 0, CEngineForceFront * engine_ }.rotate(body_.getAngle() + CSteerRear*steer_),
            Vec2{ 0, -0.5 }.rotate(body_.getAngle())
        );
        body_.applyForce(
            Vec2{ 0, CEngineForceRear * engine_ }.rotate(body_.getAngle()+ CSteerFront *steer_),
            Vec2{ 0, 0.5 }.rotate(body_.getAngle())
        );
        // body_.applyTorque(2.0*steer_);
    }
    int getSensor(const Field& field, Vec2 point) const {
        return field.polygon().contains(body_.getPos() + point.rotated(body_.getAngle()));
    }
    Mat3x2 transformer() const {
        return Mat3x2::Rotate(body_.getAngle()).translated(body_.getPos());
    }

    Car(P2Body&& _body) : body_(_body) { initialize(); }
};
