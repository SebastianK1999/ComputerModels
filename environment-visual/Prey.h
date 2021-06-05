#pragma once
#include "Agent.h"
#include "ofMain.h"

class Prey :
    public Agent
{
private:
public:
    Prey(ofVec2f _position, size_t _hp);
};

