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
}

//--------------------------------------------------------------
void ofApp::update(){
    mouse_x = ofGetMouseX();
}

//--------------------------------------------------------------
void ofApp::draw(){
    int index = (int)ofMap(mouse_x, 0, ofGetWidth(), 0, n);
    if (index < 0) {
        index = 0;
    } else if (index >= n) {
        index = n - 1;
    }
    
    vector<log_data> log_same_time = log[index];
    for (auto l: log_same_time) {
        ofDrawBitmapString(l.time, 10, 100);
        ofDrawCircle(ofMap(l.point.x, x_min, x_max, 0, ofGetWidth()), ofMap(l.point.y, y_min, y_max, ofGetHeight(), 0), 10);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
