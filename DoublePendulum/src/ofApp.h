#pragma once

#include <vector>
#include <iostream>

#include "ofMain.h"
#include "../DoublePendulum.h"

class ofApp : public ofBaseApp{
private:
	//static constexpr bool SAVE_ENERGY;
	//static constexpr bool SAVE_POSITIONS;
	//static constexpr bool SAVE_PHASES;
	const size_t PENDULUMS_COUNT;
	const double START_TETHA;
	const double DIFF_TETHA;

	std::vector<glm::vec4> states;
	std::vector<DoublePendulum> pendulums;
	std::ofstream ofs_energy;
	std::ofstream ofs_positions;
	std::ofstream ofs_phases;


public:
	ofApp();
	~ofApp();

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
