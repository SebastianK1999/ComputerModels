#include "ofApp.h"
#include <cmath>
#include <omp.h>

# define M_PI           3.14159265358979323846  /* pi */

constexpr bool SAVE_ENERGY		= 1;
constexpr bool SAVE_POSITIONS	= 0;
constexpr bool SAVE_PHASES		= 0;
constexpr bool SAVE_RECURENCE	= 0;

ofFloatColor palette( float t, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d )
{
	ofVec3f temp = 2*M_PI * (c * t + d);
	temp[0] = cos(temp[0]);
	temp[1] = cos(temp[1]);
	temp[2] = cos(temp[2]);
    temp = a + b * temp;
	return ofFloatColor(temp[0], temp[1], temp[2]);
}

void write_bmp(const char* path, const unsigned width, const unsigned height, const std::vector<std::vector<float>> data) {
	const unsigned pad = (4 - (3 * width) % 4) % 4, filesize = 54 + (3 * width + pad) * height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
	char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
	for (unsigned i = 0; i < 4; i++) {
		header[2 + i] = (char)((filesize >> (8 * i)) & 255);
		header[18 + i] = (char)((width >> (8 * i)) & 255);
		header[22 + i] = (char)((height >> (8 * i)) & 255);
	}
	std:vector<char> img(filesize);
	for (unsigned i = 0; i < 54; i++) img[i] = header[i];
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			const int i = 54 + 3 * x + y * (3 * width + pad);
			img[i]     = static_cast<char>(255 * data[x][y]);
			img[i + 1] = static_cast<char>(255 * data[x][y]);
			img[i + 2] = static_cast<char>(255 * data[x][y]);
		}
		for (unsigned p = 0; p < pad; p++) img[54 + (3 * width + p) + y * (3 * width + pad)] = 0;
	}
	std::ofstream file(path, std::ios::out | std::ios::binary);
	file.write(&img[0], filesize);
	file.close();
}

ofApp::ofApp():
	PENDULUMS_COUNT(10000),
	START_TETHA(M_PI/2.0 + 0.15),
	DIFF_TETHA(0.00001),
	pendulums(),
	states()
{
	if constexpr (SAVE_ENERGY)	ofs_energy.open("data/energy.txt");
	if constexpr (SAVE_POSITIONS) ofs_positions.open("data/positions.txt");
	if constexpr (SAVE_PHASES)	ofs_phases.open("data/phases.txt");

	pendulums.reserve(PENDULUMS_COUNT);

	for (int i = 0; i < PENDULUMS_COUNT; i++) {
		pendulums.emplace_back(DoublePendulum(400, 400, START_TETHA, 150, 1, START_TETHA + DIFF_TETHA * i, 150, 1));
		//pendulums.back().setColor((i < PENDULUMS_COUNT / 2 ? ofColor(127.5 + i * 255 / PENDULUMS_COUNT, 50, 255) : ofColor(255, 50, 255 - (i - PENDULUMS_COUNT / 2) * 255 / PENDULUMS_COUNT)));
		pendulums.back().setColor( palette(static_cast<float>(i)/PENDULUMS_COUNT, 
			ofVec3f(1.0, 0.0, 0.0), ofVec3f(1.0, 5.0, 1.0), ofVec3f(0.5, 0.0, 0.0), ofVec3f(0.0, 0.3, 0.2)) );
	}
}

ofApp::~ofApp() {
	if constexpr (SAVE_RECURENCE) {
		std::vector<std::vector<float>> matrix(states.size());
		float max = -1.0;
		for (int i = 0; i < states.size(); i++) {
			matrix[i] = std::vector<float>(states.size());
			for (int j = i+1; j < states.size(); j++) {
				matrix[i][j] = glm::length(states[i] - states[j]);
				if (matrix[i][j] > max) {
					max = matrix[i][j];
				}
			}
		}
		for (int i = 0; i < states.size(); i++) {
			for (int j = i + 1; j < states.size(); j++) {
				matrix[i][j] = matrix[i][j] / max;
				matrix[j][i] = matrix[i][j];
			}
		}
		write_bmp("test.bmp", states.size(), states.size(), matrix);
	}

	if constexpr (SAVE_ENERGY) {
		ofs_energy.close();
		system("python energy.py");
	}
	if constexpr (SAVE_POSITIONS) {
		ofs_positions.close();
		system("python positions.py");
	}
	if constexpr (SAVE_PHASES) {
		ofs_phases.close();
		system("python phases.py");
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(220,190, 50);
	ofSetVerticalSync(false);
	ofSetFrameRate(0);
}

//--------------------------------------------------------------
void ofApp::update(){
	static unsigned long iter = -1;
	iter++;
	//# pragma omp parallel for num_threads(6)
	for (int i = 0; i < PENDULUMS_COUNT; i++) {
		pendulums[i].computePositions();
		pendulums[i].updateAngles(0.01);
	}
	if constexpr (SAVE_RECURENCE) {
		static double offset = std::sqrt(std::sqrt(2));
		static const double offsetMultiplier = offset;

		if (!((iter + 1) % static_cast<unsigned long>(50))) {
			offset *= offsetMultiplier;
			states.emplace_back(pendulums[0].getState());
		}
	}

	if constexpr (SAVE_ENERGY) {
		static unsigned int i_en = 0;
		if (!(i_en % 10)) {
			ofs_energy << pendulums[0].streamEnergy() << " " << pendulums.back().streamEnergy() << "\n";
			i_en = 1;
		}
		else {
			i_en++;
		}
	}
	if constexpr (SAVE_POSITIONS) {
		static unsigned int i_pos = 0;
		if ( !(i_pos%10) ) {
			ofs_positions << pendulums[0].streamPosition() << " " << pendulums.back().streamPosition() << "\n";
			i_pos = 1;
		}
		else {
			i_pos++;
		}
	}
	if constexpr (SAVE_PHASES) {
		static unsigned int i_ph = 0;
		if (!(i_ph % 10)) {
			ofs_phases << pendulums[0].streamPhase() << " " << pendulums.back().streamPhase() << "\n";
			i_ph = 1;
		}
		else {
			i_ph++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < PENDULUMS_COUNT; i++) {
		pendulums[i].drawLines();
	}
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
