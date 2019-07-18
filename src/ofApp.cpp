#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
 
	glm::vec3 strt(0.0,0.0,-1.0);
	el.setup("F", "F+F-F-F+F", 25.0, 0.5 * PI/2.0, 25.0, strt); //era PI el 50.0 era 25.0
	yo.setup("F", "F+F-F", 55.0, 0.75 * PI/2.0, 55.0, strt); //era PI el 50.0 era 25.0
	ello.setup("F", "F+F-F+F", 35.0, 1.0 * PI/2.0, 35.0, strt); //era PI el 50.0 era 25.0
	//cout << el.getProduction() << endl;
	el.simulate(4);
	yo.simulate(4);
	ello.simulate(4);
	//cout << el.getProduction() << endl;
	//vecs.reserve(10);
	vecs.resize(400);
	vecs2.resize(200);
	vecs3.resize(300);
	ofBackground(0,0,0);
	ofSetFrameRate(30);
	el.update(vecs);
	yo.update(vecs2);
	ello.update(vecs3);
	lineShapeLookUpOffset = 1 ;
	lineShapeLookUp = 35;
}

//--------------------------------------------------------------
void ofApp::update(){
 	//el.update(pauly);
 	//el.update(vecs);
	//if(lineShapeLookUpOffset % 50 == 0) el.update(vecs);
	if(lineShapeLookUpOffset % 1  == 0) el.oneStep(vecs);
	if(lineShapeLookUpOffset % 1  == 0) yo.oneStep(vecs2);
	if(lineShapeLookUpOffset % 1  == 0) ello.oneStep(vecs3);
	
	for(int i = 0; i < vecs.size(); i++){
			vecs[i].z-= 1.0;
	}
	for(int i = 0; i < vecs2.size(); i++){
			vecs2[i].z-= 0.5;
	}
	for(int i = 0; i < vecs3.size(); i++){
			vecs3[i].z-= 1.5;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableAlphaBlending();
	ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
	
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < vecs.size(); i++){
			ofSetColor(255,255,255);
			glVertex3f(vecs[i].x,vecs[i].y,vecs[i].z);
	}
	//for(size_t i = 0; i < vecs.size(); i++){
	//for(size_t i = lineShapeLookUpOffset; i < lineShapeLookUp + lineShapeLookUpOffset; i++){
	//	ofSetColor(255,255,255, 255);
	//	glVertex3f(vecs[i].x,vecs[i].y,vecs[i].z);
	//}
	glEnd();
	//ofEndShape();

	glBegin(GL_LINE_STRIP);
	for(size_t i = lineShapeLookUpOffset; i < lineShapeLookUp + lineShapeLookUpOffset; i++){
		ofSetColor(155,105,155, 255);
		glVertex3f(vecs[i].x,vecs[i].y,vecs[i].z);
	}
	glEnd();
	ofEndShape();

  /*---------------------*/
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < vecs2.size(); i++){
			ofSetColor(255,255,255);
			glVertex3f(vecs2[i].x,vecs2[i].y,vecs2[i].z);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for(size_t i = lineShapeLookUpOffset; i < lineShapeLookUp + lineShapeLookUpOffset; i++){
		ofSetColor(155,105,155, 255);
		glVertex3f(vecs2[i].x,vecs2[i].y,vecs2[i].z);
	}
	glEnd();
	ofEndShape();

  /*---------------------*/

	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < vecs3.size(); i++){
			ofSetColor(255,255,255);
			glVertex3f(vecs3[i].x,vecs3[i].y,vecs3[i].z);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for(size_t i = lineShapeLookUpOffset; i < lineShapeLookUp + lineShapeLookUpOffset; i++){
		ofSetColor(155,105,155, 255);
		glVertex3f(vecs3[i].x,vecs3[i].y,vecs3[i].z);
	}
	glEnd();
	ofEndShape();

	if(vecs2.size()  >  lineShapeLookUpOffset + lineShapeLookUp){
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
