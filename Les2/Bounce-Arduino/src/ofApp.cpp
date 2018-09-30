#include "ofApp.h"

#define PIN_LED 12
#define PIN_SECONDLED 11

//--------------------------------------------------------------
void ofApp::setup(){
	// set listener - call ofApp::setupArduino when arduino is ready for use
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// connect to the Arduino
	// use the same device name used in the Arduino IDE
	arduino.connect("COM3", 57600);
	arduino.sendFirmwareVersionRequest(); // workaround for ofArduino/firmata bug
	x = ofRandom(0, ofGetWidth());
	y = ofRandom(0, ofGetHeight());

	speedX = 10;
	speedY = 10;

	radius = 40;
	
}

void ofApp::setupArduino(const int& version) {
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// print firmware name and version to the console
	ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
		<< " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

	arduino.sendDigitalPinMode(PIN_LED, ARD_OUTPUT);
	arduino.sendDigitalPinMode(PIN_SECONDLED, ARD_OUTPUT);
	;

}

//--------------------------------------------------------------
void ofApp::update(){
	arduino.update();
	if (x < 0) {
		x = 0;
		speedX = -speedX;
		arduino.sendDigital(PIN_LED, ARD_HIGH);
		arduino.sendDigital(PIN_SECONDLED, ARD_LOW);
		color = ofColor::red;
	}

	if (x > ofGetWidth()) {
		x = ofGetWidth();
		speedX = -speedX;
		arduino.sendDigital(PIN_LED, ARD_HIGH);
		arduino.sendDigital(PIN_SECONDLED, ARD_LOW);
		color = ofColor::red;
	}
	if (y < 0) {
		y = 0;
		speedY = -speedY;
		arduino.sendDigital(PIN_SECONDLED, ARD_HIGH);
		arduino.sendDigital(PIN_LED, ARD_LOW);
		color = ofColor::blue;
	}

	if (y > ofGetHeight()) {
		y = ofGetHeight();
		speedY = -speedY;
		arduino.sendDigital(PIN_SECONDLED, ARD_HIGH);
		arduino.sendDigital(PIN_LED, ARD_LOW);
		color = ofColor::blue;
	}

	x += speedX;
	y += speedY;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(color);
	ofDrawCircle(x, y, radius);

}
