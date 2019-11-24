#pragma once
#include <Siv3D.hpp>


class Car {
	double accsel_;
	double steer_;
	P2Body body_;
    static constexpr double CAccselForce = 10;
public:

    void initialize() {
        body_.setDamping(0.9);
        body_.setAngularDamping(0.8);
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
        const auto t = Transformer2D(Mat3x2::Rotate(body_.getAngle()).translated(body_.getPos()));

        body_.applyForce(Vec2{ 0, CAccselForce*accsel_ }.rotate(body_.getAngle()));
        body_.applyTorque(2.0*steer_);
    }
	int getSensor(void* field, Vec2 point) const;

    Car(P2Body&& _body) : body_(_body) { initialize(); }
};
