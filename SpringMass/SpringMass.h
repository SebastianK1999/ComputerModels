#pragma once

#include <vector>
#include <utility>
#include <string>
#include <iostream>

#include "ofMain.h"
#include "Vertex.h"

class SpringMass
{
private:
	std::vector<Vertex> points;
	std::vector<std::pair<Vertex&, Vertex&>> links;
	std::vector<float> linksLength;
	size_t x;
	size_t y;
	size_t z;
	size_t xy;
	float mass;
	//float l;
	float k;

public:
	SpringMass(ofVec3f startPos,float  mass, float l, float k, size_t xs);
	SpringMass(ofVec3f startPos,float  mass, float l, float k, size_t xs, size_t ys);
	SpringMass(ofVec3f startPos,float  mass, float l, float k, size_t xs, size_t ys, size_t zs);

	void draw();
	void run(float dt);
	void link(Vertex& vert0, Vertex& vert1);
	Vertex& getVertex(size_t i);
	//Vertex& getVertex(size_t x, size_t y);
	//Vertex& getVertex(size_t x, size_t y, size_t z);

	void gravityForce();
	void springForce();
	void floor();
};

