#include "ofApp.h"

ofApp::ofApp():
	line(ofVec3f(0,0,0), 0.5, 2, 5, 15),
	cloth(ofVec3f(30, -30, 0), 1, 5, 3, 6, 6),
	softBody(ofVec3f(-90, -40, 0), 5, 15, 5, 6, 6, 6),
	attachVert0(ofVec3f(0,2,0),1),
	attachVert1(ofVec3f(30, 2, 0), 1),
	attachVert2(ofVec3f(60, 2, 0), 1),
	timeLast(0)
{

}

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setAutoDistance(false);
	cam.setDistance(250);
	ofEnableDepthTest();
	ofResetElapsedTimeCounter();
	ofSetWindowTitle("Spring Mass - 309039");

	line.link(attachVert0, line.getVertex(0));
	cloth.link(attachVert1, cloth.getVertex(5));
	cloth.link(attachVert2, cloth.getVertex(6*6-1));
}

//--------------------------------------------------------------
void ofApp::update(){
	this->dt = ofGetElapsedTimef() - this->timeLast;
	this->timeLast = ofGetElapsedTimef();

	line.gravityForce();
	line.springForce();
	cloth.gravityForce();
	cloth.springForce();
	softBody.gravityForce();
	softBody.springForce();
	
	line.run(dt);
	line.floor();
	cloth.run(dt);
	//cloth.floor();
	softBody.run(dt);
	softBody.floor();
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	line.draw();
	cloth.draw();
	softBody.draw();

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
