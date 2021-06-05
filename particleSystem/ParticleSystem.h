#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ParticleMethods.h"
#include <vector>
#include <iostream>

class ParticleSystem
{
	std::vector<Particle> particles;
	size_t N;

	void emplaceParticle();
	float currentLifeSpan;
	float cycleAge;

public:
	ParticleSystem(size_t N);
	void draw();
	void simulate(float timePassed);
	void apply( void (*foo)(Particle&) );

	void setLifespan(float lifespan);

	void pushEmiter(Emiter emiter);
	size_t emiterIndex;
	std::vector<Emiter> emiters;
	void(*beginConfig)(Particle&);
};

