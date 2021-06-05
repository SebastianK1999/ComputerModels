#pragma once

#include "ofMain.h"
#include <cstdlib>
#include <cmath>

class Sphere
{
private:
	float_t radius;
	float_t mass;
	ofVec3f position;
	ofVec3f velocity;
	ofColor color;
	Sphere* center;
	static const float G;

public:
	Sphere( Sphere* center, const float_t& radius, const float_t& mass, const ofVec3f& position, const ofColor& color );
	Sphere(const float_t& radius, const float_t& mass, const ofColor& color);
	Sphere();
	Sphere& operator=(Sphere&& obj) noexcept;
	void orbit( const float_t& dt );
	void draw();

};

