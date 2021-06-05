#pragma once

#include "ofMain.h"


class Agent
{
private:

public:
	ofVec2f position;
	size_t hp;
	size_t state;
	Agent(ofVec2f _position, size_t _hp);
};
