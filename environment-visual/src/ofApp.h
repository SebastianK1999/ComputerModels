#pragma once

#include "ofMain.h"
#include "../Plant.h"
#include "../Prey.h"
#include "../Predator.h"

#include <vector>


class ofApp : public ofBaseApp{
	const double SIZE;

	const size_t PLANT_COUNT;
	const size_t PLANT_MAX_HP;
	const size_t PLANT_REPRODUCE_TIME;
	const size_t PLANT_REPRODUCE_COUNT;

	const size_t PREY_COUNT;
	const size_t PREY_MAX_HP;
	const size_t PREY_MAX_HUNGRY_HP_LEVEL;
	const double PREY_VELOCITY;
	const double PREY_REPRODUCE_COUNT;

	const size_t PREDATOR_COUNT;
	const size_t PREDATOR_MAX_HP;
	const size_t PREDATOR_MAX_HUNGRY_HP_LEVEL;
	const double PREDATOR_VELOCITY;
	const double PREDATOR_REPRODUCE_COUNT;

	//const size_t ALIEN_COUNT;
	//const size_t ALIEN_MAX_HP;
	//const size_t ALIEN_MAX_HUNGRY_HP_LEVEL;

	std::vector<Plant> plants;
	std::vector<Prey> preys;
	std::vector<Predator> predators;
	//std::vector<Alien> aliens;

	std::ofstream ofs;
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
