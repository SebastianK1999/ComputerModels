#include "Agent.h"

#include <cmath>

Agent::Agent(ofVec2f p, double v, State s) :
	position(p),
	velocity(0, 10),
	state(s),
	recoveryTime(-1)
{
	double rad = ofRandom(2 * 3.141592);
	this->velocity.x = std::cos(rad) * v;
	this->velocity.y = std::sin(rad) * v;
}