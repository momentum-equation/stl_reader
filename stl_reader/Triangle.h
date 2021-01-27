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

	// Triangles sharing vertices but having opposite normals 
	// are considered as equal
	bool operator== (const Triangle& Other) const {
		return (v1_ == Other.v1_ && v2_ == Other.v2_
			&& v3_ == Other.v3_);
	}

	bool operator!= (const Triangle& Other) const {
		return !(*this == Other);
	}

	bool operator< (const Triangle& Other) const {
		// sort on the basis of angle with positive x-axis
		Vertex xHat = { 1, 0, 0 };
		Vertex nThis = normal_;
		Vertex nOther = Other.normal_;

		if (xHat.dot(nThis) > xHat.dot(nOther) && *this != Other) {
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

	bool operator== (const Triangle& Other) {
		return (normal_ == Other.normal_ && v1_ == Other.v1_ &&
			v2_ == Other.v2_ && v3_ == Other.v3_);
	}
};