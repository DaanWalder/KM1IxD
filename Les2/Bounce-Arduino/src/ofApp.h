#pragma once

#include "ofMain.h"
#include "ofEvents.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

	private:
		ofArduino arduino;
		void setupArduino(const int& version);
		float x;
		float y;
		float speedX;
		float speedY;
		int radius;
		ofColor color;

		
};
