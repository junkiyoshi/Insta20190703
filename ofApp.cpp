#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 300, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	auto noise_seed_x = ofRandom(1000);
	auto noise_seed_y = ofRandom(1000);
	for (char c = 'A'; c <= 'Z'; c++) {

		auto x = 0;
		auto y = 0;
		auto z = ofMap(c, 'A', 'Z', -300, 300);
		auto noise_value_x = ofNoise(noise_seed_x, (ofGetFrameNum() + z) * 0.005);
		if (noise_value_x < 0.25) {

			x = ofMap(noise_value_x, 0, 0.25, -300, 0);
		}
		else if (noise_value_x >= 0.75) {

			x = ofMap(noise_value_x, 0.75, 1, 0, 300);
		}

		auto noise_value_y = ofNoise(noise_seed_y, (ofGetFrameNum() + z) * 0.005);
		if (noise_value_y < 0.25) {

			y = ofMap(noise_value_y, 0, 0.25, -300, 0);
		}
		else if (noise_value_y >= 0.75) {

			y = ofMap(noise_value_y, 0.75, 1, 0, 300);
		}
		auto location = glm::vec3(x - 150, y + 150, z);

		auto path = font.getCharacterAsPoints(c, true, false);
		auto outline = path.getOutline();

		for (int line_index = 0; line_index < outline.size(); line_index++) {

			for (auto& vertex : outline[line_index].getVertices()) {
				
				vertex += location;
			}
		}

		ofFill();
		ofSetColor(239);
		ofBeginShape();
		for (int line_index = 0; line_index < outline.size(); line_index++) {

			if (line_index != 0) { ofNextContour(true); }

			auto vertices = outline[line_index].getVertices();
			ofVertices(vertices);
		}
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		for (int line_index = 0; line_index < outline.size(); line_index++) {

			if (line_index != 0) { ofNextContour(true); }

			auto vertices = outline[line_index].getVertices();
			ofVertices(vertices);
		}
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}