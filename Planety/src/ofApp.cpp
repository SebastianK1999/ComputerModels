#include "ofApp.h"

ofApp::ofApp(size_t N) :
	N(N),
	dt(0),
	sun(ofRandom(10,20), ofRandom(100000000,1000000000000), ofColor(255,255,150))
{
	this->planets = new Sphere[N];
	for (size_t i = 0; i < this->N; i++) {
		planets[i] = Sphere(&this->sun, ofRandom(1, 8), ofRandom(10000, 800000), ofVec3f(ofRandom(20,200), ofRandom(20, 200), ofRandom(30, 30)), ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setAutoDistance(false);
	cam.setDistance(250);
	ofResetElapsedTimeCounter();

}

//--------------------------------------------------------------
void ofApp::update(){
	this->dt = ofGetElapsedTimef();
	ofResetElapsedTimeCounter();
	for (size_t i = 0; i < this->N; i++) {
		this->planets[i].orbit(dt);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	ofNoFill();

	this->sun.draw();

	ofFill();
	for (size_t i = 0; i < this->N; i++) {
		planets[i].draw();
	}
	cam.end();
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
