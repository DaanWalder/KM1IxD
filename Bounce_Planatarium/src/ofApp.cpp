#include "ofApp.h"

#define PIN_LED 12
#define PIN_SECONDLED 11

void ofApp::setup() {
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	arduino.connect("COM7", 57600);
	arduino.sendFirmwareVersionRequest();

	ofBackground(ofColor::black);

	gui.setup();
	gui.add(drawGrid.set("Grid", false));
	gui.add(useLight.set("Light", true));

	light.setDirectional();
	light.setDiffuseColor(ofColor::white);
	light.enable();

	x = ofRandom(-540, 540);
	y = ofRandom(-360, 360);
	z = ofRandom(-200, 200);

	planet1SpeedX = 10;
	planet1SpeedY = 10;
	planet1SpeedZ = 10;

}

void ofApp::setupArduino(const int& version) {
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
	ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
		<< " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

	arduino.sendDigitalPinMode(PIN_LED, ARD_OUTPUT);
	arduino.sendDigitalPinMode(PIN_SECONDLED, ARD_OUTPUT);
	;

}

void ofApp::update() {
	arduino.update();
	if (x < -540) {
		x = -540;
		planet1SpeedX = -planet1SpeedX;
	}

	if (x > 540) {
		x = 540;
		planet1SpeedX = -planet1SpeedX;
	}
	if (y < -360) {
		y = -360;
		planet1SpeedY = -planet1SpeedY;
	}

	if (y > 360) {
		y = 360;
		planet1SpeedY = -planet1SpeedY;
	}
	if (z < -200) {
		z = -200;
		planet1SpeedZ = -planet1SpeedZ;
	}

	if (z > 200) {
		z = 200;
		planet1SpeedZ = -planet1SpeedZ;
	}

	x += planet1SpeedX;
	y += planet1SpeedY;
	z += planet1SpeedZ;
}

void ofApp::draw() {
	ofEnableDepthTest();

	cam.setVFlip(true);
	cam.begin();

	if (useLight) {
		ofEnableLighting();
	}
	else {
		ofDisableLighting();
	}

	ofSetColor(ofColor::yellow);
	ofDrawSphere(x, y, z, ofRandom(40, 70));

	ofSetColor(ofColor::blue);
	ofDrawSphere(x, y, z, ofRandom(40, 70));

	if (drawGrid) ofDrawGrid(100);

	cam.end();
	ofDisableDepthTest();

	if (drawGui) {
		ofDisableLighting();
		gui.draw();
	}
}

void ofApp::keyPressed(int key) {
	if (key == 'l') useLight = !useLight;
	if (key == 'g') drawGrid = !drawGrid;
	if (key == ' ') drawGui = !drawGui;
}