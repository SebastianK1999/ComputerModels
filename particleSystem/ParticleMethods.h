#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ParticleMethods.h"

class ParticleMethods
{
public:
	static void gravity(Particle&);
	static void floor(Particle&);
	static void randomShape(Particle&);
};

class Emiter {
public:
	ofVec3f statingPoint;
	ofVec3f statingVelocity;
	bool changePos;
	bool fillCircle;
	float radius;


	void update();
	Emiter(ofVec3f pos, ofVec3f vel);
	Emiter();
};

