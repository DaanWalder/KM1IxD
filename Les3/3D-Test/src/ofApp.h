#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

	private:
		ofxPanel gui;


		ofParameter<float> rotateSpeedX = 1;
		ofParameter<float> rotateSpeedY = 1;
		ofParameter<float> rotateSpeedZ = 1;
		
		ofParameter<bool> drawGrid = true;
		ofParameter<bool> doRotate = true;

		float rotateX = 1;
		float rotateY = 1;
		float rotateZ = 1;

};
