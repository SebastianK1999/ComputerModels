#pragma once

#include "ofMain.h"
#include <vector>
#include "../Agent.h"

class ofApp : public ofBaseApp{
	const size_t COUNT;
	const size_t INFECTED_COUNT;
	const int RECOVERY_TIME;
	const float SIZE;
	const float VELOCITY;
	const double PROB;

	std::vector<Agent> population;

	public:
		ofApp();
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
