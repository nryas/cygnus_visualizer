#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    buffer = ofBufferFromFile("cygnus_log.txt");
    vector<float> x_vec, y_vec;
    string prev_time = "";
    vector<log_data> log_same_time;
    
    for (auto line: buffer.getLines()) {
        auto split_line = ofSplitString(line, ", ");
        float x = ofToFloat(split_line[1]);
        float y = ofToFloat(split_line[2]);
        
        x_vec.push_back(x);
        y_vec.push_back(y);
        
        if (prev_time != split_line[0]) {
            if (log_same_time.size() != 0) {
                log.push_back(log_same_time);
                log_same_time.clear();
            }
        }
        
        log_data l;
        l.time = prev_time = split_line[0];
        l.point = ofPoint(x, y);
        
        log_same_time.push_back(l);
    }
    
    n = log.size();
    x_min = *min_element(x_vec.begin(), x_vec.end());
    x_max = *max_element(x_vec.begin(), x_vec.end());
    y_min = *min_element(y_vec.begin(), y_vec.end());
    y_max = *max_element(y_vec.begin(), y_vec.end());
    
    mode = Mode::INTERACTIVE;
    current_index = 0;
    ofSetBackgroundAuto(false);
    ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    int fps = ofGetMouseY();
    ofSetFrameRate(ofMap(fps, ofGetHeight(), 0, 1, 60));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofDrawBitmapString(ofGetFrameRate(), 10, 100);
    ofRotateZ(-10);
    ofNoFill();
    ofSetColor(255, 255, 255);
    auto origin = ofPoint(ofMap(0, x_min, x_max, 0, ofGetWidth()), ofMap(0, y_min, y_max, ofGetHeight(), 0));
    ofDrawCircle(origin, 10);
    ofDrawLine(origin, ofPoint(cos(4*M_PI/3)*1000, sin(4*M_PI/3)*1000));
    ofDrawLine(origin, ofPoint(cos(2*M_PI/3)*1000, sin(2*M_PI/3)*1000));
    ofFill();
    
    if (mode == Mode::INTERACTIVE) {
        int index = (int)ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, n);
        if (index < 0) {
            index = 0;
        } else if (index >= n) {
            index = n - 1;
        }
        
        vector<log_data> log_same_time = log[index];
        for (auto l: log_same_time) {
            ofSetColor(255, 255, 255);
            ofDrawBitmapString(l.time, 10, 20);
            ofSetColor(0, 0, 0, 10);
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            ofSetColor(0, 200, 255);
            ofDrawCircle(ofMap(l.point.x, x_min, x_max, 0, ofGetWidth()), ofMap(l.point.y, y_min, y_max, ofGetHeight(), 0), 10);
        }
        ofPopMatrix();
    } else if (mode == Mode::MOVIE) {
        for (auto l: log[current_index]) {
            ofSetColor(255, 255, 255);
            ofDrawBitmapString(l.time, 10, 20);
            ofSetColor(0, 0, 0, 10);
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            ofSetColor(0, 200, 255);
            ofDrawCircle(ofMap(l.point.x, x_min, x_max, 0, ofGetWidth()), ofMap(l.point.y, y_min, y_max, ofGetHeight(), 0), 10);
        }
        ofPopMatrix();
        ofSetColor(0, 200, 255);
        ofDrawRectangle(0, ofGetHeight()-10, (float)current_index / (float)n * (float)ofGetWidth(), 10);
        if (++current_index > n) { current_index = 0; }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (mode) {
        mode = Mode::INTERACTIVE;
    } else {
        mode = Mode::MOVIE;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
