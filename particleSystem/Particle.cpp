#include "Particle.h"

Particle::Particle(ofVec3f position, ofVec3f velocity, float lifespan) :
	position(position),
	velocity(velocity),
	acceleration(0.0f, 0.0f, 0.0f),
	color(ofRandom(255), ofRandom(255), ofRandom(255)),
	lifespan(lifespan),
	age(0.0f),
	size(1.0f),
	radius(0.5f),
	opacity(255.0f),
	shape(0),
	dead(false)
{

}

void Particle::draw() {
	if (!dead) {
		ofSetColor(this->color, this->opacity);
		switch (this->shape) {
		case 0:
			ofDrawCircle(this->position, this->radius);
			break;
		case 1:
			ofDrawRectangle(this->position, this->size, this->size);
			break;

		}
	}
}

void Particle::live(float timePassed) {
	age += timePassed;
	velocity += acceleration * timePassed;
	position += velocity * timePassed;
	if (age >= lifespan) {
		this->dead = true;
	}
}

void Particle::resurrect(ofVec3f position, ofVec3f velocity, float lifespan) {
	this->position = position;
	this->velocity = velocity;
	this->acceleration = ofVec3f(0.0f, 0.0f, 0.0f);
	this->lifespan = lifespan;
	this->age = 0.0f;
	//this->size = 1.0f;
	//this->radius = 0.5f;
	//this->opacity = 255.0f;
	//this->shape = 0;
	this->dead = false;
}



void Particle::setPosition(ofVec3f pos) {
	this->position = pos;
}
void Particle::setVelocity(ofVec3f vel) {
	this->velocity = vel;
}
void Particle::setAcceleration(ofVec3f acc) {
	this->acceleration = acc;
}
void Particle::addPosition(ofVec3f pos) {
	this->position += pos;
}
void Particle::addVelocity(ofVec3f vel) {
	this->velocity += vel;
}
void Particle::addAcceleration(ofVec3f acc){
	this->acceleration += acc;
}
ofVec3f Particle::getPosition()const{
	return this->position;
}
ofVec3f Particle::getVelocity()const{
	return this->velocity;
}
ofVec3f Particle::getAcceleration()const{
	return this->acceleration;
}

void Particle::resetVelocity() {
	this->velocity = ofVec3f(0, 0, 0);
}
void Particle::resetAcceleration() {
	this->acceleration = ofVec3f(0, 0, 0);
}

void Particle::setSize(float size) {
	this->size = size;
	this->radius = size / 2;
}
float Particle::getSize() {
	return this->size;
}

void Particle::setShape(size_t shape) {
	this->shape = shape;
}

size_t Particle::getShape() const {
	return this->shape;
}

bool Particle::isDead() const {
	return this->dead;
}