#include "Vertex.h"

Vertex::Vertex(ofVec3f position, float mass) :
	//position(position),
	//lastPosition(position),
	force(0, 0, 0),
	mass(mass)
{
	position.x += ofRandom(-0.2, 0.2);
	position.y += ofRandom(-0.2, 0.2);
	position.z += ofRandom(-0.2, 0.2);
	this->position = position;
	this->lastPosition = position;
}