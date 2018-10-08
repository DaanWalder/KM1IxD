#include "ofApp.h"
#include "ofxGui.h"

void ofApp::setup(){
	ofSetFrameRate(20);
	ofBackground(ofColor::black);

	gui.setup();
	gui.add(drawGrid.set("Grid", false));
	gui.add(doRotate.set("Rotate", false));
	gui.add(rotateSpeedX.set("X", 1, 1, 9.0));
	gui.add(rotateSpeedY.set("Y", 1, 1, 9.0));
	gui.add(rotateSpeedZ.set("Z", 1, 1, 9.0));
}

void ofApp::update(){
	rotateX += rotateSpeedX;
	rotateY += rotateSpeedY;
	rotateZ += rotateSpeedZ;
}


void ofApp::draw(){
	gui.draw();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	if (doRotate) {
		ofRotateXDeg(rotateX);
		ofRotateYDeg(rotateY);
		ofRotateZDeg(rotateZ);
	}
	if (drawGrid) {
		ofDrawGrid(200);
	}
	ofSetColor(ofColor::aquamarine);
	ofDrawSphere(100, 100, 300, 50);

}


void ofApp::keyPressed(int key){
	if (key == 'g') {
		drawGrid = !drawGrid;
	}
	if (key == 'h') {
		doRotate = !doRotate;
	}
}