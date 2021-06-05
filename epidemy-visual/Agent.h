#pragma once

#include "ofMain.h"


enum State : size_t {infected, susceptible, recovered};
class Agent
{
private:

public:
	ofVec2f position;
	ofVec2f velocity;
	State state;

	int recoveryTime;

	Agent(ofVec2f p, double v, State s);
};


