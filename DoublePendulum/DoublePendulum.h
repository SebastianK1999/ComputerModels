#pragma once
#include <ofMain.h>
#include <sstream>

class DoublePendulum{
private:
	double x;
	double y;

	double x0;
	double y0;
	double ang_velocity0;
	double ang_acceleration0;
	double tetha0;
	double l0;
	double m0;
	ofColor c0;

	double x1;
	double y1;
	double ang_velocity1;
	double ang_acceleration1;
	double tetha1;
	double l1;
	double m1;
	ofColor c1;

public:
	DoublePendulum(double _x, double _y, double _tetha0, double _length0, double _mass0, double _tetha1, double _length1, double _mass1);
	
	void setColors(ofColor _color0, ofColor _color1);
	void setColor(ofColor _color);
	void computePositions();
	void updateAngles(double dt);
	void drawLines();


	glm::vec4 getState();
	std::stringstream streamEnergy();
	std::stringstream streamPosition();
	std::stringstream streamPhase();

};

