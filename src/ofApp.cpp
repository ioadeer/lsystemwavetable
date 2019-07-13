#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
 
	glm::vec3 strt(2.0,2.0,0.0);
	el.setup("F", "F+F-F-F+F", 50.0, 1.0 * PI/2.0, 50.0, strt); //era PI el 50.0 era 25.0
	//cout << el.getProduction() << endl;
	el.simulate(4);
	//cout << el.getProduction() << endl;
	//vecs.reserve(10);
	vecs.resize(400);
	ofBackground(0,0,0);
	ofSetFrameRate(30);
	el.update(vecs);
	lineShapeLookUpOffset = 1 ;
	lineShapeLookUp = 50;
}

//--------------------------------------------------------------
void ofApp::update(){
 	//el.update(pauly);
 	//el.update(vecs);
	if(lineShapeLookUpOffset == 0) el.update(vecs);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableAlphaBlending();
	ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
	glBegin(GL_LINE_STRIP);
	//	for(int i = 0; i < vecs.size(); i++){
	//		ofSetColor(255,255,255);
	//		glVertex3f(vecs[i].x,vecs[i].y,vecs[i].z);
	//	}
	//for(size_t i = 0; i < vecs.size(); i++){
	for(size_t i = lineShapeLookUpOffset; i < lineShapeLookUp + lineShapeLookUpOffset; i++){
		ofSetColor(255,255,255, 255);
		glVertex3f(vecs[i].x,vecs[i].y,vecs[i].z);
	}
	glEnd();
	ofEndShape();

	if(vecs.size() >  lineShapeLookUpOffset + lineShapeLookUp){
		lineShapeLookUpOffset++;
	} else {
		lineShapeLookUpOffset = 0;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
