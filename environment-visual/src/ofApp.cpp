#include "ofApp.h"

// Based on
//
// https://youtu.be/r_It_X7v-1E
//

ofApp::ofApp() :
	SIZE(10.0),

	PLANT_COUNT(8),
	PLANT_MAX_HP(240),
	PLANT_REPRODUCE_TIME(30),
	PLANT_REPRODUCE_COUNT(8),

	PREY_COUNT(8),
	PREY_MAX_HP(300),
	PREY_MAX_HUNGRY_HP_LEVEL(150),
	PREY_VELOCITY(2.5),
	PREY_REPRODUCE_COUNT(4),

	PREDATOR_COUNT(4),
	PREDATOR_MAX_HP(500),
	PREDATOR_MAX_HUNGRY_HP_LEVEL(150),
	PREDATOR_VELOCITY(2),
	PREDATOR_REPRODUCE_COUNT(1),

	plants(),
	preys(),
	predators()
{
	plants.reserve(PLANT_COUNT);
	for (int i = 0; i < PLANT_COUNT; i++) {
		plants.emplace_back(Plant(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PLANT_MAX_HP));
	}

	preys.reserve(PREY_COUNT);
	for (int i = 0; i < PREY_COUNT; i++) {
		preys.emplace_back(Prey(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PREY_MAX_HUNGRY_HP_LEVEL));
	}

	predators.reserve(PREDATOR_COUNT);
	for (int i = 0; i < PREDATOR_COUNT; i++) {
		predators.emplace_back(Predator(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PREDATOR_MAX_HUNGRY_HP_LEVEL));
	}
	
	ofs = std::ofstream((std::string("../data/simulations/sim_") + std::to_string(0) + ".txt").c_str());
}

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
	static constexpr bool SAVE_TO_FILE = 1;


	// plant
	static size_t plant_reproduce_countdown;
	if (plant_reproduce_countdown != 0) {
		plant_reproduce_countdown--;
	}
	else {
		plant_reproduce_countdown = PLANT_REPRODUCE_TIME;
		for (int i = 0; i < PLANT_REPRODUCE_COUNT; i++) {
			plants.push_back(Plant(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PLANT_MAX_HP));
		}
	}

	for (int i = 0; i < plants.size(); i++) {
		Plant& plant = plants[i];
		if (plant.hp != 0) {
			plant.hp--;
		}
		else {
			plants.erase(plants.begin() + i);
			i--;
			continue;
		}
	}

	// prey
	for (int i = 0; i < preys.size(); i++) {
		Prey& prey = preys[i];
		if (prey.hp != 0) {
			prey.hp--;
		}
		else {
			preys.erase(preys.begin() + i);
			i--;
			continue;
		}
	}

	for (int i = 0; i < preys.size(); i++) {
		Prey& prey = preys[i];

		if (prey.hp <= PREY_MAX_HUNGRY_HP_LEVEL) {
			if (plants.size() > 0) {
				size_t atractorIndex = 0;
				ofVec2f atractor = plants[atractorIndex].position - prey.position;
				float atractortDist = atractor.length();
				for (int j = 1; j < plants.size(); j++) {
					Plant& plant = plants[j];
					ofVec2f vec = plant.position - prey.position;
					float dist = vec.length();
					if (dist < atractortDist) {
						atractorIndex = j;
						atractor = vec;
						atractortDist = dist;
					}
				}
				prey.position += atractor / atractortDist * PREY_VELOCITY;
		
				if ((prey.position - plants[atractorIndex].position).length() < SIZE) {
					plants.erase(plants.begin() + atractorIndex);
					prey.hp = PREY_MAX_HP;
				}
			}
		}
		else {
			size_t atractorIndex = i;
			ofVec2f atractor = prey.position;
			float atractortDist = 1000;
			for (int j = 1; j < preys.size(); j++) {
				Prey& partner = preys[j];
				ofVec2f vec = partner.position - prey.position;
				float dist = vec.length();
				if (dist < atractortDist && partner.hp > PREY_MAX_HUNGRY_HP_LEVEL && j != i) {
					atractorIndex = j;
					atractor = vec;
					atractortDist = dist;
				}
			}
			Prey& partner = preys[atractorIndex];
			if (&prey != &partner) {
				prey.position += atractor / atractortDist * PREY_VELOCITY;
				if ((prey.position - preys[atractorIndex].position).length() < SIZE) {
					prey.hp = PREY_MAX_HUNGRY_HP_LEVEL;
					partner.hp = PREY_MAX_HUNGRY_HP_LEVEL;
					for (int j = 0; j < PREY_REPRODUCE_COUNT; j++) {
						preys.push_back(Prey(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PREY_MAX_HUNGRY_HP_LEVEL));
					}
				}
			}
		}
	}

	// prey
	for (int i = 0; i < preys.size(); i++) {
		Prey& prey = preys[i];
		if (prey.hp != 0) {
			prey.hp--;
		}
		else {
			preys.erase(preys.begin() + i);
			i--;
			continue;
		}
	}

	for (int i = 0; i < preys.size(); i++) {
		Prey& prey = preys[i];

		if (prey.hp <= PREY_MAX_HUNGRY_HP_LEVEL) {
			if (plants.size() > 0) {
				size_t atractorIndex = 0;
				ofVec2f atractor = plants[atractorIndex].position - prey.position;
				float atractortDist = atractor.length();
				for (int j = 1; j < plants.size(); j++) {
					Plant& plant = plants[j];
					ofVec2f vec = plant.position - prey.position;
					float dist = vec.length();
					if (dist < atractortDist) {
						atractorIndex = j;
						atractor = vec;
						atractortDist = dist;
					}
				}
				prey.position += atractor / atractortDist * PREY_VELOCITY;
		
				if ((prey.position - plants[atractorIndex].position).length() < SIZE) {
					plants.erase(plants.begin() + atractorIndex);
					prey.hp = PREY_MAX_HP;
				}
			}
		}
		else {
			size_t atractorIndex = i;
			ofVec2f atractor = prey.position;
			float atractortDist = 1000;
			for (int j = 1; j < preys.size(); j++) {
				Prey& partner = preys[j];
				ofVec2f vec = partner.position - prey.position;
				float dist = vec.length();
				if (dist < atractortDist && partner.hp > PREY_MAX_HUNGRY_HP_LEVEL && j != i) {
					atractorIndex = j;
					atractor = vec;
					atractortDist = dist;
				}
			}
			Prey& partner = preys[atractorIndex];
			if (&prey != &partner) {
				prey.position += atractor / atractortDist * PREY_VELOCITY;
				if ((prey.position - preys[atractorIndex].position).length() < SIZE) {
					prey.hp = PREY_MAX_HUNGRY_HP_LEVEL;
					partner.hp = PREY_MAX_HUNGRY_HP_LEVEL;
					for (int j = 0; j < PREY_REPRODUCE_COUNT; j++) {
						preys.push_back(Prey(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PREY_MAX_HUNGRY_HP_LEVEL));
					}
				}
			}
		}
	}


	// predator
	for (int i = 0; i < predators.size(); i++) {
		Predator& predator = predators[i];
		if (predator.hp != 0) {
			predator.hp--;
		}
		else {
			predators.erase(predators.begin() + i);
			i--;
			continue;
		}
	}

	for (int i = 0; i < predators.size(); i++) {
		Predator& predator = predators[i];

		if (predator.hp <= PREDATOR_MAX_HUNGRY_HP_LEVEL) {
			if (preys.size() > 0) {
				size_t atractorIndex = 0;
				ofVec2f atractor = preys[atractorIndex].position - predator.position;
				float atractortDist = atractor.length();
				for (int j = 1; j < preys.size(); j++) {
					Prey& prey = preys[j];
					ofVec2f vec = prey.position - predator.position;
					float dist = vec.length();
					if (dist < atractortDist) {
						atractorIndex = j;
						atractor = vec;
						atractortDist = dist;
					}
				}
				predator.position += atractor / atractortDist * PREDATOR_VELOCITY;

				if ((predator.position - preys[atractorIndex].position).length() < SIZE) {
					preys.erase(preys.begin() + atractorIndex);
					predator.hp = PREDATOR_MAX_HP;
				}
			}
		}
		else {
			size_t atractorIndex = i;
			ofVec2f atractor = predator.position;
			float atractortDist = 1000;
			for (int j = 1; j < predators.size(); j++) {
				Predator& partner = predators[j];
				ofVec2f vec = partner.position - predator.position;
				float dist = vec.length();
				if (dist < atractortDist && partner.hp > PREDATOR_MAX_HUNGRY_HP_LEVEL && j != i) {
					atractorIndex = j;
					atractor = vec;
					atractortDist = dist;
				}
			}
			Predator& partner = predators[atractorIndex];
			if (&predator != &partner) {
				predator.position += atractor / atractortDist * PREDATOR_VELOCITY;
				if ((predator.position - predators[atractorIndex].position).length() < SIZE) {
					predator.hp = PREDATOR_MAX_HUNGRY_HP_LEVEL;
					partner.hp = PREDATOR_MAX_HUNGRY_HP_LEVEL;
					for (int j = 0; j < PREDATOR_REPRODUCE_COUNT; j++) {
						predators.push_back(Predator(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PREDATOR_MAX_HUNGRY_HP_LEVEL));
					}
				}
			}
		}
	}


	// Save to file
	if constexpr (SAVE_TO_FILE) {
		static constexpr size_t TIME_OVERLOAD  = 10;
		static size_t counter = 0;
		if(counter != TIME_OVERLOAD){
			counter++;
		}
		else {
			ofs << plants.size() << " " << preys.size() << " " << predators.size() << "\n";
			counter = 0;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(100, 180, 100);
	for (int i = 0; i < plants.size(); i++) {
		ofDrawCircle(plants[i].position, SIZE);
	}

	ofSetColor(140, 140, 255);
	for (int i = 0; i < preys.size(); i++) {
		ofDrawCircle(preys[i].position, SIZE);
	}

	ofSetColor(180, 100, 100);
	for (int i = 0; i < predators.size(); i++) {
		ofDrawCircle(predators[i].position, SIZE);
	}
}

//--------------------------------------------------------------
ofApp::~ofApp() {
	ofs.close();
	system("python.exe ..\\data\\plotEpidemy.py ..\\data\\simulations\\sim_0.txt");
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
