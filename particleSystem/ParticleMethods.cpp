#include "ParticleMethods.h"

// METHODS
void ParticleMethods::gravity(Particle& particle) {
	particle.setAcceleration(ofVec3f(0, -50, 0));
}

void ParticleMethods::floor(Particle& particle) {
	ofVec3f newPos = particle.getPosition();
	if (newPos[1] < 0) {
		ofVec3f newVel = particle.getVelocity();
		newPos[1] = 0;
		newVel[1] = -newVel[1];
		particle.setVelocity(newVel * 0.75);
		particle.setPosition(newPos);
	}
}

void ParticleMethods::randomShape(Particle& particle) {
	particle.setShape(static_cast<size_t>(ofRandom(0.5, 1.5)));
}



// EMITER
Emiter::Emiter(ofVec3f pos, ofVec3f vel):
	changePos(false),
	fillCircle(false),
	radius(100)
{
	this->statingPoint = pos;
	this->statingVelocity = vel;
}
Emiter::Emiter() :
	changePos(true),
	fillCircle(false),
	radius(100)
{
	this->update();
}

void Emiter::update() {
	if (this->changePos) {
		float r;
		if (fillCircle) r = ofRandom(0, radius);
		else r = radius;
		float alphaPos = ofRandom(3.141593 * 2);
		this->statingPoint = ofVec3f(cosf(alphaPos) * r, 0, sinf(alphaPos) * r);
	}
	float alphaVel = ofRandom(3.141593 * 2);
	this->statingVelocity = ofVec3f(cosf(alphaVel) * 5, 100, sinf(alphaVel) * 5);
	
}