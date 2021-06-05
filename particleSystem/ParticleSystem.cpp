#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(size_t N):
	particles(),
	N(N),
	currentLifeSpan(10),
	cycleAge(0),
	emiterIndex(0)
{
	//particles.reserve(N);
}

void ParticleSystem::draw() {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
}

void ParticleSystem::simulate(float timePassed) {
	if (particles.size() < N && (this->cycleAge > (this->currentLifeSpan / N) * particles.size())) {
		for (int i = 0; i < (cycleAge - (this->currentLifeSpan / N) * particles.size()) / (this->currentLifeSpan / N); i++) {
			this->emplaceParticle();
		}
	}
	for (int i = 0; i < particles.size(); i++) {
		particles[i].live(timePassed);
		if (particles[i].isDead()) {
			if (particles.size() > N) {
				particles.erase(particles.begin() + i);
			}
			else {
				particles[i].resurrect(this->emiters[this->emiterIndex].statingPoint, this->emiters[this->emiterIndex].statingVelocity, currentLifeSpan);
				this->emiters[emiterIndex].update();
				this->emiterIndex = (this->emiterIndex + 1) % this->emiters.size();
			}
		}
	}
	cycleAge += timePassed;
	cycleAge = (cycleAge > currentLifeSpan ? 0.0 : cycleAge);
}

void ParticleSystem::apply(void (*foo)(Particle&)) {
	for (int i = 0; i < particles.size(); i++) {
		foo(particles[i]);
	}
}

void ParticleSystem::setLifespan(float lifeSpan) {
	this->currentLifeSpan = lifeSpan;
}

void ParticleSystem::pushEmiter(Emiter emiter) {
	this->emiters.push_back(emiter);
}

void ParticleSystem::emplaceParticle() {
	particles.push_back(Particle(emiters[emiterIndex].statingPoint, emiters[emiterIndex].statingVelocity, currentLifeSpan));
	particles.back().setSize(10);
	this->beginConfig(particles.back());
	this->emiters[emiterIndex].update();
	this->emiterIndex = ((this->emiterIndex + 1) % this->emiters.size());
}