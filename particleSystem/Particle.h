#pragma once
#include "ofMain.h"

class Particle
{
	ofVec3f position;
	ofVec3f velocity;
	ofVec3f acceleration;

	ofColor color;
	float lifespan;
	float age;
	float size;
	float radius;
	float opacity;
	size_t shape; // 0 - circle, 1 - sqare

	bool dead;

public:
	Particle(ofVec3f position, ofVec3f velocity, float lifespan);
	void draw();
	void live(float timePassed);
	void resurrect(ofVec3f position, ofVec3f velocity, float lifespan);

	void setShape(size_t shape);
	size_t getShape() const;
	void setSize(float size);
	float getSize();
	void setPosition(ofVec3f pos);
	void setVelocity(ofVec3f pos);
	void setAcceleration(ofVec3f pos);
	void addPosition(ofVec3f pos);
	void addVelocity(ofVec3f pos);
	void addAcceleration(ofVec3f pos);
	void resetVelocity();
	void resetAcceleration();
	ofVec3f getPosition()const;
	ofVec3f getVelocity()const;
	ofVec3f getAcceleration()const;
	bool isDead()const;
	

};

