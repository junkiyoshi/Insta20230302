#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

	// 配色デザイン ビビッドブルー P144
	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(18, 85, 163));
	color_palette.push_back(ofColor(0, 165, 231));
	color_palette.push_back(ofColor(93, 177, 186));
	color_palette.push_back(ofColor(44, 121, 191));
	color_palette.push_back(ofColor(136, 185, 79));
	color_palette.push_back(ofColor(246, 221, 80));
	color_palette.push_back(ofColor(200, 59, 57));

	if (ofGetFrameNum() % 2 == 0) {

		glm::vec2 location;
		glm::vec2 direction;
		glm::vec2 target;

		int r = ofRandom(4);
		if (r == 0) {

			location = glm::vec2(ofRandom(0, ofGetWindowWidth()), -30);
			direction = glm::vec2(0, 10);
			target = location + direction;
		}

		if (r == 1) {

			location = glm::vec2(ofRandom(0, ofGetWindowWidth()), 750);
			direction = glm::vec2(0, -10);
			target = location + direction;
		}

		if (r == 2) {

			location = glm::vec2(-30, ofRandom(0, ofGetWindowHeight()));
			direction = glm::vec2(10, 0);
			target = location + direction;
		}

		if (r == 3) {

			location = glm::vec2(750, ofRandom(0, ofGetWindowHeight()));
			direction = glm::vec2(-10, 0);
			target = location + direction;
		}

		this->location_list.push_back(location);
		this->direction_list.push_back(direction);
		this->target_list.push_back(target);
		int color_index = ofRandom(color_palette.size());
		this->color_list.push_back(color_palette[color_index]);
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		this->target_list[i] += this->direction_list[i];
	}

	while (this->location_list.size() > 1000) {

		this->location_list.erase(this->location_list.begin());
		this->direction_list.erase(this->direction_list.begin());
		this->target_list.erase(this->target_list.begin());
		this->color_list.erase(this->color_list.begin());
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->location_list.size(); i++) {

		this->draw_arrow(this->location_list[i], this->target_list[i], 30, this->color_list[i], ofColor(255));
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor fill_color, ofColor no_fill_color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto distance = glm::distance(target, location);

	ofPushMatrix();
	ofTranslate(target);

	ofSetColor(fill_color);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
	ofEndShape();

	ofSetColor(no_fill_color);
	ofNoFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
	ofEndShape();

	ofPopMatrix();
}
//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}