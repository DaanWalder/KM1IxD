#include "ofApp.h"

#define PIN_REDLED 12
#define PIN_POT 0
#define PIN_BUTTONRED 6
#define PIN_BUTTONYELLOW 7

void ofApp::setup() {
	ofSetFrameRate(60);
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	arduino.connect("COM7", 57600);
	arduino.sendFirmwareVersionRequest();
	drawGrid = true;

	gui.setup();    
	gui.add(rotateSpeedY.set("Y", 0, 0, 9.0));     
	gui.add(rotateSpeedZ.set("Z", 0, 0, 9.0));
	gui.add(rotateSpeedX.set("X", 0, 0, 9.0));
	gui.add(redLED.set("Brightness LED", false));
	gui.add(drawGrid.set("Grid", false));          
	gui.add(saveMatrix.set("save matrix", false));

	
}

void ofApp::setupArduino(const int& version) {
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
	ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
		<< " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

	arduino.sendDigitalPinMode(PIN_BUTTONRED, ARD_OUTPUT);
	arduino.sendDigitalPinMode(7, ARD_INPUT);
	arduino.sendDigitalPinMode(PIN_REDLED, ARD_OUTPUT);
	arduino.sendAnalogPinReporting(0, ARD_ANALOG);
	;

}

void ofApp::update() {
	arduino.update();

	rotationX += rotateSpeedX;
	rotationY += rotateSpeedY;
	rotationZ += rotateSpeedZ;
	
}

void ofApp::draw() {
	gui.draw();

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	if (saveMatrix) ofPushMatrix();
	ofRotateX(rotationX);
	if (saveMatrix) ofPopMatrix();

	if (saveMatrix) ofPushMatrix();
	ofRotateY(rotationY);
	if (saveMatrix) ofPopMatrix();

	if (saveMatrix) ofPushMatrix();
	ofRotateZ(rotationZ);
	if (saveMatrix) ofPopMatrix();

	if (drawGrid) ofDrawGrid(200);

	if (redLED) arduino.sendDigital(PIN_REDLED, ARD_HIGH);

	//if (arduino.getDigital(PIN_BUTTONRED)) {
	//	arduino.sendDigital(PIN_REDLED, ARD_HIGH);
	//}
	//else
	//{
	//	arduino.sendDigital(PIN_REDLED, ARD_LOW);
	//}

	ofSetColor(255, 255, 0);
	ofDrawSphere(0, 0, 0, ((arduino.getAnalog(PIN_POT)) / 10));
	ofSetColor(255, 0, 255);
	ofDrawSphere(-300, 100, 50, 20);
	ofDrawSphere(50, 200, 60, 10);

}

void ofApp::keyPressed(int key) {
	if (key == 'g') {        
		drawGrid = !drawGrid;  
	}
	else if (key == 'r') {  
		rotationX = 0;
		rotationY = 0;
		rotationZ = 0;
	}
	else if (key == ' ') { 
		rotateSpeedX = 0;
		rotateSpeedY = 0;
		rotateSpeedZ = 0;
	}
	else if (key == 'm') { 
		saveMatrix = !saveMatrix;
	}
}