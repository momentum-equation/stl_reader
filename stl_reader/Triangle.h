#pragma once
#include "Vertex.h"
#include <utility>
#include <vector>
#include <math.h>

class Triangle {
private:
	Vertex normal_;
	Vertex v1_;
	Vertex v2_;
	Vertex v3_;

	bool are_close (Vertex P1, Vertex P2) const {
		if ((P1 - P2).magnitude() <= 1e-8) {
			return true;
		}
	}


public:
	Triangle() :
		normal_(),
		v1_(),
		v2_(),
		v3_()
	{}

	Triangle(Vertex normal, Vertex v1, Vertex v2, Vertex v3) :
		normal_(normal),
		v1_(v1),
		v2_(v2),
		v3_(v3)
	{}

	Triangle(const Triangle& Other) :
		Triangle(Other.normal_, Other.v1_, Other.v2_, Other.v3_)
	{}

	Triangle(Triangle&& Other) noexcept :
		Triangle(std::move(Other.normal_), 
			std::move(Other.v1_), 
			std::move(Other.v2_), 
			std::move(Other.v3_))
	{}

	Triangle& operator= (const Triangle& Other) {
		normal_ = Other.normal_;
		v1_ = Other.v1_;
		v2_ = Other.v2_;
		v3_ = Other.v3_;
		return *this;
	}

	Triangle& operator= (Triangle&& Other) noexcept {
		normal_ = std::move(Other.normal_);
		v1_ = std::move(Other.v1_);
		v2_ = std::move(Other.v2_);
		v3_ = std::move(Other.v3_);
		return *this;
	}

	bool operator== (const Triangle& Other) const {
		// all vertices should be equal
		// normals should have angle greater than some
		// threshold

		bool close_normals{ false };
		if (get_normal().cos_angle(Other.normal_) >= (1 - 1e-7)) {
			close_normals = true;
		}

		return (are_close(v1_, Other.v1_) && are_close(v2_, Other.v2_)
			&& are_close(v3_, Other.v3_) && close_normals);
	}

	bool operator!= (const Triangle& Other) const {
		return !(*this == Other);
	}

	bool operator< (const Triangle& Other) const {
		// sort on the basis of angle with positive x-axis
		Vertex xHat = { 1, 0, 0 };
		Vertex nThis = normal_;
		Vertex nOther = Other.normal_;

		if (xHat.cos_angle(nThis) > xHat.cos_angle(nOther) && *this != Other) {
			return true;
		}
		return false;
	}

	Vertex get_normal() const {
		return normal_;
	}

	std::vector<Vertex> get_points() const {
		return std::vector<Vertex> {v1_, v2_, v3_};
	}
};