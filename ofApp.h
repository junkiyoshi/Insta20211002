#pragma once
#include "ofMain.h"
#include "opencv2/opencv.hpp"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	ofEasyCam cam;

	cv::VideoCapture cap_1, cap_2;
	cv::Size cap_size;
	int number_of_frames_1, number_of_frames_2;
	vector<cv::Mat> frame_list_1, frame_list_2;

	float rect_size;
	vector<cv::Mat> rect_frames;
	vector<unique_ptr<ofImage>> rect_images;
	vector<cv::Rect> cv_rects;
};