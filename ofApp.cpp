#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
	ofDisableArbTex();

	this->cap_1.open("D:\\MP4\\VN20210917_143130.mp4");
	this->cap_size = cv::Size(640, 360);

	this->rect_size = 40;
	for (int x = 0; x < this->cap_size.width; x += this->rect_size) {

		for (int y = 0; y < this->cap_size.height; y += this->rect_size) {

			auto image = make_unique<ofImage>();
			image->allocate(this->rect_size, this->rect_size, OF_IMAGE_COLOR);
			cv::Mat frame = cv::Mat(cv::Size(image->getWidth(), image->getHeight()), CV_MAKETYPE(CV_8UC3, image->getPixels().getNumChannels()), image->getPixels().getData(), 0);
			cv::Rect rect = cv::Rect(x, y, this->rect_size, this->rect_size);

			this->rect_images.push_back(move(image));
			this->cv_rects.push_back(rect);
			this->rect_frames.push_back(frame);
		}
	}

	this->number_of_frames_1 = this->cap_1.get(cv::CAP_PROP_FRAME_COUNT);
	for (int i = 0; i < this->number_of_frames_1; i++) {

		cv::Mat src, tmp;
		this->cap_1 >> src;
		if (src.empty()) {

			return;
		}

		cv::resize(src, tmp, this->cap_size);
		cv::cvtColor(tmp, tmp, cv::COLOR_BGR2RGB);

		this->frame_list_1.push_back(tmp);
	}

	this->cap_2.open("D:\\MP4\\MOV_0324.mp4");
	this->number_of_frames_2 = this->cap_2.get(cv::CAP_PROP_FRAME_COUNT);
	for (int i = 0; i < this->number_of_frames_2; i++) {

		cv::Mat src, tmp;
		this->cap_2 >> src;
		if (src.empty()) {

			return;
		}

		cv::resize(src, tmp, this->cap_size);
		cv::cvtColor(tmp, tmp, cv::COLOR_BGR2RGB);

		this->frame_list_2.push_back(tmp);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(this->cap_size.width * -0.5 + 20, this->cap_size.height * -0.5 - 20, 0);

	for (int i = 0; i < this->rect_frames.size(); i += 1) {

		ofPushMatrix();
		ofTranslate(this->cv_rects[i].x, this->cap_size.height - this->cv_rects[i].y, 0);

		float noise_value = ofNoise(this->cv_rects[i].x * 0.0025, this->cv_rects[i].y * 0.0025, ofGetFrameNum() * 0.008);
		float deg = 0;
		if (noise_value <= 0.45) { deg = 0; }
		if (noise_value > 0.45 && noise_value < 0.55) { deg = ofMap(noise_value, 0.45, 0.55, 0, 180); }
		if (noise_value >= 0.55) { deg = 180; }
		
		ofRotateY(deg);

		int frame_index = ofGetFrameNum() % this->number_of_frames_1;

		cv::Mat tmp_box_image_1(this->frame_list_1[frame_index], this->cv_rects[i]);
		tmp_box_image_1.copyTo(this->rect_frames[i]);

		this->rect_images[i]->update();
		this->rect_images[i]->getTexture().bind();
		ofSetColor(255);
		ofFill();
		ofDrawBox(glm::vec3(0, 0, 1), this->rect_size, this->rect_size, 1);
		this->rect_images[i]->unbind();

		ofSetColor(39);
		ofNoFill();
		ofDrawBox(glm::vec3(0, 0, 1), this->rect_size, this->rect_size, 1);

		ofPopMatrix();
	}

	for (int i = 0; i < this->rect_frames.size(); i += 1){

		ofPushMatrix();
		ofTranslate(this->cv_rects[i].x, this->cap_size.height - this->cv_rects[i].y, 0);

		float noise_value = ofNoise(this->cv_rects[i].x * 0.0025, this->cv_rects[i].y * 0.0025, ofGetFrameNum() * 0.008);
		float deg = 0;
		if (noise_value <= 0.45) { deg = 0; }
		if (noise_value > 0.45 && noise_value < 0.55) { deg = ofMap(noise_value, 0.45, 0.55, 0, 180); }
		if (noise_value >= 0.55) { deg = 180; }

		ofRotateY(deg);

		int frame_index = ofGetFrameNum() % this->number_of_frames_2;

		cv::Mat tmp_box_image_2(this->frame_list_2[frame_index], this->cv_rects[i]);
		tmp_box_image_2.copyTo(this->rect_frames[i]);

		this->rect_images[i]->update();
		this->rect_images[i]->getTexture().bind();
		ofSetColor(255);
		ofFill();
		ofDrawBox(glm::vec3(0, 0, -1), this->rect_size, this->rect_size, 1);
		this->rect_images[i]->unbind();

		ofSetColor(39);
		ofNoFill();
		ofDrawBox(glm::vec3(0, 0, -1), this->rect_size, this->rect_size, 1);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}