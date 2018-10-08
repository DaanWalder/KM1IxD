#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();

	void update();

	void draw();

	void keyPressed(int key);

	ofxPanel gui;
	ofParameter<float> rotateSpeedX;
	ofParameter<float> rotateSpeedY;
	ofParameter<float> rotateSpeedZ;

	ofParameter<bool> redLED;
	ofParameter<bool> drawGrid;
	ofParameter<bool> saveMatrix;

	float rotationX;
	float rotationY;
	float rotationZ;

	ofArduino arduino;
	void setupArduino(const int& version);

};
