#pragma once
#include <utility>

class Vertex{
private:
	float x_, y_, z_;

public:
	Vertex() :
		x_(0), y_(0), z_(0)		
	{}

	Vertex(float x, float y, float z) :
		x_(x), y_(y), z_(z)
	{}

	Vertex(Vertex&& Other) noexcept :
		x_(std::move(Other.x_)), y_(std::move(Other.y_)), z_(std::move(Other.z_))
	{}

	Vertex(const Vertex& Other) :
		Vertex(Other.x_, Other.y_, Other.z_)
	{}

	Vertex& operator= (const Vertex& Other) {
		x_ = Other.x_;
		y_ = Other.y_;
		z_ = Other.z_;

		return *this;
	}

	Vertex& operator= (Vertex&& Other) noexcept {
		x_ = std::move(Other.x_);
		y_ = std::move(Other.y_);
		z_ = std::move(Other.z_);

		return *this;
	}

	bool operator== (const Vertex& P) {
		return (x_ == P.x_ && y_ == P.y_ && z_ == P.z_);
	}

	bool operator== (const Vertex& P) const {
		return (x_ == P.x_ && y_ == P.y_ && z_ == P.z_);
	}


	bool operator!= (const Vertex& P) {
		return !(*this == P);
	}

	bool operator!= (const Vertex& P) const {
		return !(*this == P);
	}

	float dot(const Vertex& Other){
		return (x_ * Other.x_ + y_ * Other.y_ + z_ * Other.z_);
	}
};