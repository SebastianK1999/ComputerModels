#include "ofApp.h"

ofApp::ofApp() :
	parsys(400),
	timeLast(0)
{

}

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setAutoDistance(false);
	cam.setDistance(250);
	ofEnableDepthTest();
	ofResetElapsedTimeCounter();

	parsys.pushEmiter(Emiter());
	parsys.pushEmiter(Emiter(ofVec3f(0,0,0), ofVec3f(0,10,0)));
	parsys.beginConfig = ParticleMethods::randomShape;
	parsys.setLifespan(20);
}

//--------------------------------------------------------------
void ofApp::update(){
	this->dt = ofGetElapsedTimef() - this->timeLast;
	this->timeLast = ofGetElapsedTimef();
	//ofResetElapsedTimeCounter();

	parsys.apply(ParticleMethods::gravity);
	parsys.apply(ParticleMethods::floor);
	parsys.simulate(this->dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	parsys.draw();

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
