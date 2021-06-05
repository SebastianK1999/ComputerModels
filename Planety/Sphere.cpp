#include "Sphere.h"

const float Sphere::G = 6.67430e-7; // needs to be scaled down for a simulation in this scale

Sphere::Sphere( Sphere* center,	const float_t& radius, const float_t& mass, const ofVec3f& position, const ofColor& color ) :
	center(center), radius(radius), mass(mass), position(position), color(color),
	velocity(-position[1] / position.length() * std::sqrt(G * center->mass / position.length()),
			  position[0] / position.length() * std::sqrt(G * center->mass / position.length()),
			  position[2] / position.length() * std::sqrt(G * center->mass / position.length())
	)
{}

Sphere::Sphere( const float_t& radius, const float_t& mass, const ofColor& color) :
	center(this), radius(radius), mass(mass), position(0,0,0), color(color),
	velocity(0, 0, 0)
{}

Sphere::Sphere():
	center(this), radius(0), mass(0), position(0, 0, 0), color(0),
	velocity(0, 0, 0)
{}

Sphere& Sphere::operator=(Sphere&& obj) noexcept {
	this->center	= obj.center;
	this->radius	= obj.radius;
	this->mass		= obj.mass;
	this->position	= obj.position;
	this->color		= obj.color;
	this->velocity	= obj.velocity;

	return *this;
}

void Sphere::orbit(const float_t& dt) {
	this->position += this->velocity * dt;
	this->velocity += dt * (G * center->mass / pow((this->position - center->position).length(),2) * ((center->position - this->position) / (this->position - center->position).length()));
}

void Sphere::draw() {
	ofSetColor(this->color);
	ofDrawSphere(this->position, this->radius);
}