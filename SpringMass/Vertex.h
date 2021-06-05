#pragma once
#include "ofMain.h"
#include <vector>
#include <iostream>

class Vertex
{
	friend class SpringMass;
	ofVec3f position;
	ofVec3f lastPosition;
	ofVec3f force;
	float mass;
public:
	Vertex(ofVec3f position, float mass);
};
