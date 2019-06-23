#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	ofArduino arduino;
	void setupArduino(const int& version);

	void keyPressed(int key);

	ofxPanel gui;

	ofParameter<bool> drawGrid;
	ofParameter<bool> useLight;
	bool drawGui = true;

	ofLight light;
	ofEasyCam cam;
	float x;
	float y;
	float z;
	float planet1SpeedX;
	float planet1SpeedY;
	float planet1SpeedZ;
};
