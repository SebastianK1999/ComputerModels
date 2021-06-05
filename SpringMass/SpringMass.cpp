#include "SpringMass.h"

SpringMass::SpringMass(ofVec3f startPos, float  mass, float l, float k, size_t x) {
	this->k = k;
	this->x = x;
	this->y = 1;
	this->z = 1;
	this->xy = this->x * this->y;

	this->mass = mass;
	float vertMass = mass / (x * y * z);

	this->points.reserve(x);
	this->links.reserve(x - 1);
	this->linksLength.reserve(links.size());
	for (size_t i = 0; i < x; i++) {
		this->points.emplace_back(Vertex(startPos + ofVec3f(l * i, 0, 0), vertMass));
	}
	for (size_t i = 1; i < x; i++) {
		this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i - 1], this->points[i]));
		this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
	}
}
SpringMass::SpringMass(ofVec3f startPos, float  mass, float l, float k, size_t x, size_t y) {
	this->k = k;
	this->x = x;
	this->y = y;
	this->z = 1;
	this->xy = this->x * this->y;

	this->mass = mass;
	float vertMass = mass / (x * y * z);

	this->points.reserve(x * y);
	this->links.reserve((x - 1) * y + x * (y - 1));
	this->linksLength.reserve(links.size());
	for (size_t i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			this->points.emplace_back(Vertex(startPos + ofVec3f(l * i, l * j, 0), vertMass));
		}
	}
	for (size_t i = 1; i < x; i++) {
		for (size_t j = 1; j < y; j++) {
			this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i - 1 + j * x], this->points[i + j * x]));
			this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
			this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i + (j - 1) * x], this->points[i + j * x]));
			this->linksLength.push_back((links.back().first.position - links.back().second.position).length());

			//this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i + (j - 1) * x], this->points[(i - 1) + j * x]));
			//this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
			//this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i - 1) + (j - 1) * x], this->points[i + j * x]));
			//this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
		}
	}
	for (size_t i = 1; i < y; i++) {
		this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i - 1) * x], this->points[i * x]));
		this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
		this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i - 1], this->points[i]));
		this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
	}

}

SpringMass::SpringMass(ofVec3f startPos, float  mass, float l, float k, size_t x, size_t y, size_t z) {
	this->k = k;
	this->x = x;
	this->y = y;
	this->z = z;
	this->xy = this->x * this->y;

	this->mass = mass;
	float vertMass = mass / (x * y * z);


	this->points.reserve(x * y * z);
	this->links.reserve((x - 1) * y * z + x * (y - 1) * z + x * y * (z - 1));
	this->linksLength.reserve(links.size());
	for (size_t i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < y; k++) {
				this->points.emplace_back(Vertex(startPos + ofVec3f(l * i, l * k, l * j), vertMass));
			}
		}
	}

	size_t xy = x*y;
	for (size_t i = 1; i < x; i++) {
		for (size_t j = 1; j < y; j++) {
			for (size_t k = 1; k < y; k++) {
				this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i - 1) + j * x + k * xy], this->points[i + j * x + k * xy]));
				this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
				this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i + (j - 1) * x + k * xy], this->points[i + j * x + k * xy]));
				this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
				this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i + j * x + (k - 1) * xy], this->points[i + j * x + k * xy]));
				this->linksLength.push_back((links.back().first.position - links.back().second.position).length());

				this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i-1) + (j-1) * x + (k - 1) * xy], this->points[i + j * x + k * xy]));
				this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
				this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i + (j-1) * x + (k - 1) * xy], this->points[(i-1) + j * x + k * xy]));
				this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
				this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i-1) + j * x + (k - 1) * xy], this->points[i + (j-1) * x + k * xy]));
				this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
				this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i-1) + (j-1) * x + k * xy], this->points[i + j * x + (k-1) * xy]));
				this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
			}
		}
	}
	for (size_t i = 1; i < x; i++) {
		for (size_t j = 1; j < y; j++) {
			this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i - 1) + j * x], this->points[i + j * x]));
			this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
			this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i + (j - 1) * x], this->points[i + j * x]));
			this->linksLength.push_back((links.back().first.position - links.back().second.position).length());


			this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i - 1) + j * xy], this->points[i + j * xy]));
			this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
			this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i + (j - 1) * xy], this->points[i + j * xy]));
			this->linksLength.push_back((links.back().first.position - links.back().second.position).length());


			this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i - 1) * x + j * xy], this->points[i * x + j * xy]));
			this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
			this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i * x + (j - 1) * xy], this->points[i * x + j * xy]));
			this->linksLength.push_back((links.back().first.position - links.back().second.position).length());

		}
	}
	for (size_t i = 1; i < y; i++) {
		this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i - 1) * xy], this->points[i * xy]));
		this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
		this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[(i - 1) * x], this->points[i * x]));
		this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
		this->links.emplace_back(std::pair<Vertex&, Vertex&>(this->points[i - 1], this->points[i]));
		this->linksLength.push_back((links.back().first.position - links.back().second.position).length());
	}

}

void SpringMass::draw() {
	for (size_t i = 0; i < this->links.size(); i++) {
		std::pair<Vertex&, Vertex&>& verPair = this->links[i];
		ofSetColor(255, 0, 0);
		ofDrawLine(verPair.first.position, verPair.second.position);
		ofDrawCircle(verPair.first.position, 1);
	}
	ofDrawCircle(links.back().second.position, 1);
}

void SpringMass::run(float dt) {
	for (size_t i = 0; i < this->points.size(); i++) {
		Vertex& point = this->points[i];

		//ofVec3f newPosition = 2 * point.position - point.lastPosition + dt * dt * point.force / point.mass;
		//
		// this didn't work for me, i found deferent equasion
		// the objests were visibly accelerating and slowing down at random
		// here is formula i found every where online
		// https://stackoverflow.com/questions/29009771/verlet-algorithm-implementation-in-python
		//
		// If position(0) == position(-1), then:
		// 2 * point.position - point.lastPosition + dt * point.force / point.mass
		// ==
		// point.position + dt * point.force / point.mass

		ofVec3f newPosition = point.position + (point.position-point.lastPosition) + ((dt*dt)*0.5) * point.force / point.mass;
		point.lastPosition = point.position;
		point.position = newPosition;
		point.force = ofVec3f(0, 0, 0);
	}
}

void SpringMass::link(Vertex& vert0, Vertex& vert1) {
	if (&vert0 != &vert1) {
		this->links.push_back(std::pair<Vertex&, Vertex&>(vert0, vert1));
		this->linksLength.push_back((vert0.position - vert1.position).length());
	}
}

Vertex& SpringMass::getVertex(size_t i) {
	return this->points[i];
}

void SpringMass::gravityForce() {
	for (size_t i = 0; i < this->points.size(); i++) {
		Vertex& point = this->points[i];
		point.force += ofVec3f(0, -11.8*point.mass, 0);
	}
}

void SpringMass::springForce() {
	for (size_t i = 0; i < this->links.size(); i++) {
		std::pair<Vertex&, Vertex&> spring = this->links[i];
		ofVec3f deltaSpring = spring.second.position - spring.first.position;
		ofVec3f f =  -k * (linksLength[i] * (deltaSpring/deltaSpring.length()) - deltaSpring);
		spring.first.force += f;
		spring.second.force -= f;
	}
}

void SpringMass::floor(){
	static float level = -100;
	for (size_t i = 0; i < this->points.size(); i++) {
		Vertex& point = this->points[i];
		if (point.position.y < level) {
			point.position.y = level;
		}
	}
}