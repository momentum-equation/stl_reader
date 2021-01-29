#pragma once
#include <cassert>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Vertex.h"
#include "Triangle.h"

class TesselationData{
private:
	std::string path;
	std::vector<Triangle> data;


public:
	TesselationData ()
	{}

	TesselationData(std::string f_path) :
		path(f_path)
	{}

	TesselationData(const TesselationData& T_Data):
		data(T_Data.data),
		path(T_Data.path)
	{}
	
	TesselationData& operator= (const TesselationData& T_Data) {
		data = T_Data.data;
		path = T_Data.path;

		return *this;
	}

	TesselationData& operator= (TesselationData&& T_Data) noexcept {
		data = std::move(T_Data.data);
		path = T_Data.path;

		return *this;
	}

	void push_back(const Triangle& tri) {
		data.push_back(tri);
	}

private:
	bool repeat(const Triangle& Tri) {

	}

	//std::unordered_map<Vertex, Vertex> hash_map()
	//{
	//	for (const auto& tri : data) {
	//		hash_table.insert(std::make_pair(tri.get_normal(), tri.get_points()[0]));
	//		hash_table.insert(std::make_pair(tri.get_normal(), tri.get_points()[1]));
	//		hash_table.insert(std::make_pair(tri.get_normal(), tri.get_points()[2]));
	//	}
	//	return hash_table;
	//}
};

float parse_coordinate(std::ifstream& s) {
	char f_buf[sizeof(float)];
	s.read(f_buf, 4);
	float* fptr = (float*)f_buf;
	return *fptr;
}

Vertex parse_point(std::ifstream& s) {
	float x = parse_coordinate(s);
	float y = parse_coordinate(s);
	float z = parse_coordinate(s);
	return Vertex(x, y, z);
}

TesselationData parse_stl(const std::string& filename) {
	std::ifstream stl_file(filename, std::ios::in | std::ios::binary);
	if (!stl_file) {
		std::cout << "ERROR: COULD NOT READ FILE" << std::endl;
		assert(false);
	}

	char header_info[80] = "";
	char n_triangles[4];
	stl_file.read(header_info, 80);
	stl_file.read(n_triangles, 4);
	std::string h(header_info);
	TesselationData info(h);
	unsigned int* r = (unsigned int*)n_triangles;
	unsigned int num_triangles = *r;
	for (unsigned int i = 0; i != num_triangles; i++) {
		auto normal = parse_point(stl_file);
		auto v1 = parse_point(stl_file);
		auto v2 = parse_point(stl_file);
		auto v3 = parse_point(stl_file);
		info.push_back(Triangle(normal, v1, v2, v3));
		char dummy[2];
		stl_file.read(dummy, 2);
	}
	return info;
}
