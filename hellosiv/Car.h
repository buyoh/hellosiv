#pragma once
#include <Siv3D.hpp>


class Car {
	double accsel_;
	double steer_;
	P2Body body_;
public:
	
	Car(P2Body&& _body) : body_(_body) {}

	void setAccsel(double _accsel) {
		accsel_ = _accsel;
	}
	void setSteer(double _steer) {
		steer_ = _steer;
	}
	const P2Body& body() const {
		return body_;
	}

	void apply();
	int getSensor(void* field, Vec2 point) const;
};