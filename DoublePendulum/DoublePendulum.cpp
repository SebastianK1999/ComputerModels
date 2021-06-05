#include "DoublePendulum.h"
#include <cmath>
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */
constexpr double g = 9.81;


DoublePendulum::DoublePendulum(double _x, double _y, double _tetha0, double _length0, double _mass0, double _tetha1, double _length1, double _mass1) :
	x(_x),
	y(_y),
	x0(0), 
	y0(0), 
	ang_velocity0(0),
	ang_acceleration0(0),
	tetha0(_tetha0),
	l0(_length0),
	m0(_mass0),
	c0(255,0,128),

	x1(0), 
	y1(0), 
	ang_velocity1(0),
	ang_acceleration1(0),
	tetha1(_tetha1),
	l1(_length1),
	m1(_mass1),
	c1(128,0,255)
{

}
void DoublePendulum::setColors(ofColor _color0, ofColor _color1) {
	c0 = _color0;
	c1 = _color1;
}
void DoublePendulum::setColor(ofColor _color) {
	c0 = _color;
	c1 = _color;
}
void DoublePendulum::computePositions() {
	x0 = x + std::sin(tetha0) * l0;
	y0 = y + std::cos(tetha0) * l0;

	x1 = x0 + std::sin(tetha1) * l1;
	y1 = y0 + std::cos(tetha1) * l1;

}
void DoublePendulum::updateAngles(double dt){
	double u = 1 + m0 + m1;
	double angAcceleration0 = 
		(g*(sin(tetha1) * cos(tetha0 - tetha1) - u*sin(tetha0))
		- (l1*pow(ang_velocity1,2) + l0*pow(ang_velocity0, 2) * cos(tetha0 - tetha1))*sin(tetha0-tetha1) )
		/(l0*(u - pow(cos(tetha0-tetha1),2)));
	double angAcceleration1 = 
		(g*u*(sin(tetha0) * cos(tetha0-tetha1) - sin(tetha1))+(u*l0*pow(ang_velocity0,2)
		+ l1*pow(ang_velocity1,2)*cos(tetha0-tetha1))*sin(tetha0-tetha1))
		/ (l1 * (u - pow(cos(tetha0 - tetha1), 2)));

	ang_velocity0 += (angAcceleration0 + ang_acceleration0) / 2 * dt;
	ang_velocity1 += (angAcceleration1 + ang_acceleration1) / 2 * dt;
	tetha0 += ang_velocity0 * dt +  ang_acceleration0*pow(dt, 2) / 2;
	tetha1 += ang_velocity1 * dt +  ang_acceleration1*pow(dt, 2) / 2;
	ang_acceleration0 = angAcceleration0;
	ang_acceleration1 = angAcceleration1;

	/*
	ang_acceleration0 = angAcceleration0;
	ang_acceleration1 = angAcceleration1;
	ang_velocity0 += ang_acceleration0 * dt;
	ang_velocity1 += ang_acceleration1 * dt;
	tetha0 += ang_velocity0 * dt;
	tetha1 += ang_velocity1 * dt;
	*/
}
void DoublePendulum::drawLines() {
	ofSetColor(c0,50);
	ofDrawLine(x, y, x0, y0);

	ofSetColor(c1,50);
	ofDrawLine(x0, y0, x1, y1);
}

glm::vec4 DoublePendulum::getState() {
	return glm::vec4(tetha0, ang_velocity0, tetha1, ang_velocity1);
}


std::stringstream DoublePendulum::streamEnergy() {
	double ek = m0 * pow(ang_velocity0*150,2) /2   +   m1 * pow(ang_velocity1*150, 2) /2;
	double ep = m0 * g * (-y0 + (400 + 150))   +   m1 * g * (-y1+(400 + 150));

	return std::stringstream() << ek << " " << ep << " " << ek+ep ;
}
std::stringstream DoublePendulum::streamPosition(){
	return std::stringstream() << x1 << " " << 800-y1;
}
std::stringstream DoublePendulum::streamPhase(){
	return std::stringstream() << tetha0 << " " << ang_velocity0 << " " << tetha1 << " " << ang_velocity1;
}