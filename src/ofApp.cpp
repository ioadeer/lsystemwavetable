#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
 
	glm::vec3 strt(0.0,0.0,-1.0);
	glm::vec3 strt2(-150.0,-150.0,-1.0);
	el.setup("F", "F+F-F+F", 25.0, 0.5 * PI/2.0, 25.0, strt); //era PI el 50.0 era 25.0
	//yo.setup("F", "F+F-F+F", 15.0, 0.25 * PI/2.0, 15.0, strt); //era PI el 50.0 era 25.0 r: F+F-F+F+F
	//ello.setup("F", "F+F-F+F", 35.0, 0.25 * PI/2.0, 35.0, strt); //era PI el 50.0 era 25.0 F+F-F+F
	//ello.setup("F", "F+F-F+F", 25.0, 0.5 * PI/2.0, 25.0, strt); //era PI el 50.0 era 25.0 F+F-F+F
	ello.setup("F", "-F+F", 35.0, 1.0 * PI/2.0, 35.0, strt); //era PI el 50.0 era 25.0 F+F-F+F
	
	//cout << el.getProduction() << endl;
	el.simulate(5);
	yo.simulate(5); //era 3
	ello.simulate(9); // era 4
	//ello.simulate(7);
	//cout << el.getProduction() << endl;
	//vecs.reserve(10);
	vecs.resize(el.getNumberOfSteps());
	cout << el.getNumberOfSteps() << endl;
	vecs2.resize(yo.getNumberOfSteps());
	xNormalizedContent.resize(vecs2.size());
	cout << yo.getNumberOfSteps() << endl;
	vecs3.resize(ello.getNumberOfSteps());
	cout << ello.getNumberOfSteps() << endl;
	ofBackground(0,0,0);
	ofSetFrameRate(30);
	el.update(vecs);
	yo.update(vecs2);
	ello.update(vecs3);
	lineShapeLookUpOffset = 1 ;
	lineShapeLookUp = 35;

	for(size_t i = 0 ; i < vecs.size(); i++){
		sonny.addVertex(vecs[i].x,vecs[i].y,vecs[i].z);
		//xNormalizedContent[i] = ofMap(vecs2[i].x, -ofGetWidth()/2, ofGetWidth()/2, -1,1);
		//cout<< xNormalizedContent[i] << endl;
	}	
	for(size_t i = 0 ; i < vecs2.size(); i++){
		pauly.addVertex(vecs2[i].x,vecs2[i].y,vecs2[i].z);
		xNormalizedContent[i] = ofMap(vecs2[i].x, -ofGetWidth()/2, ofGetWidth()/2, -1,1);
		//cout<< xNormalizedContent[i] << endl;
	}	
	for(size_t i = 0 ; i < vecs3.size(); i++){
		vinnie.addVertex(vecs3[i].x,vecs3[i].y,vecs3[i].z);
		//xNormalizedContent[i] = ofMap(vecs2[i].x, -ofGetWidth()/2, ofGetWidth()/2, -1,1);
		//cout<< xNormalizedContent[i] << endl;
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
 	//el.update(pauly);
 	//el.update(vecs);
	//if(lineShapeLookUpOffset % 50 == 0) el.update(vecs);
	//if(lineShapeLookUpOffset % 1  == 0) el.oneStep(vecs);
	//el.oneStep(vecs);
	el.nStepsAhead(5,vecs);
	//if(lineShapeLookUpOffset % 1  == 0) yo.oneStep(vecs2);
	//yo.oneStep(vecs2);
	//if(lineShapeLookUpOffset % 1  == 0) ello.oneStep(vecs3);
	//ello.oneStep(vecs3);
	yo.nStepsAhead(1,vecs2);	
	ello.nStepsAhead(1,vecs3);
 
	sonny.clear();	
	for(int i = 0; i < vecs.size(); i++){
			vecs[i].z-= 2.0;
			//sonny.addVertex(vecs[i].x,vecs[i].y,vecs[i].z);
			sonny.curveTo(vecs[i].x,vecs[i].y,vecs[i].z);

	}
	pauly.clear();
	for(int i = 0; i < vecs2.size(); i++){
			//vecs2[i].z-= 0.5;
			//pauly.addVertex(vecs2[i].x,vecs2[i].y,vecs2[i].z);
			pauly.curveTo(vecs2[i].x,vecs2[i].y,vecs2[i].z);
	}
	vinnie.clear();
	vinniex.clear();
	vinniey.clear();
	for(int i = 0; i < vecs3.size(); i++){
			//vecs3[i].z-= 1.5;
			//vecs3[i].z-= 2.5;
			//vinnie.addVertex(vecs3[i].x,vecs3[i].y,vecs3[i].z);
			vinnie.curveTo(vecs3[i].x,vecs3[i].y,vecs3[i].z);
			vinniey.curveTo(vecs3[i].x,ofMap(i,0,vecs3.size(),-ofGetHeight()/2,ofGetHeight()/2),0);
			vinniex.curveTo(ofMap(i,0,vecs3.size(),-ofGetWidth()/2,ofGetWidth()/2), vecs3[i].y, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableAlphaBlending();
	ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
	

	//ofSetColor(255,255,255,100);
	//sonny.draw();

	//box2 = sonny.getBoundingBox();
	//ofSetColor(0,255,0,100);
	//ofRect(box2);
	

	
	//EL QUE VENIA USANDO 
	//
	//
	//ofSetColor(255,255,255,100);
	//pauly.draw();
	box = sonny.getBoundingBox();
	centroid = sonny.getCentroid2D();

	//ofSetColor(255,0,0,100);
	////ofRect(box);
	//glBegin(GL_LINE_STRIP);
	//////for(size_t i = lineShapeLookUpOffset; i < lineShapeLookUp + lineShapeLookUpOffset; i++){
	//for(size_t i = 0; i < vecs.size(); i++){
	//	//ofSetColor(155,105,155, 255);
	//	//ofSetColor(255,0,0, 255);
	//	float pct = ofMap(glm::distance(vecs[i],centroid),0,ofGetWidth()/2,1, 0);
	//	pct = pow(pct,4);
	//	ofSetColor(255,255,255, 50+ 205*pct);
	//	glVertex3f(vecs[i].x,vecs[i].y,vecs[i].z);
	//}
	//glEnd();
	//ofEndShape();

  /*---------------------*/

	//glBegin(GL_LINE_STRIP);
	////for(size_t i = lineShapeLookUpOffset; i < lineShapeLookUp + lineShapeLookUpOffset; i++){
	//	//ofSetColor(155,105,155, 255);
	//for(size_t i = 0; i < vecs2.size(); i++){
	//	//ofSetColor(0,255,0, 255);
	//	ofSetColor(255,255,255, 255);
	//	glVertex3f(vecs2[i].x,vecs2[i].y,vecs2[i].z);
	//}
	//glEnd();
	//ofEndShape();

  /*---------------------*/
	ofRectangle box = vinniey.getBoundingBox();
	ofSetColor(255,255,255,200);
	ofPushMatrix();

	ofTranslate(-ofGetWidth()/2+ofGetWidth()/8, 0);
	ofScale(0.25, 1,1);
	vinniey.draw();
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(ofGetWidth()/4, -ofGetHeight()/2+ofGetWidth()/8);
	ofScale(1, 0.25,1);
	vinniex.draw();
	ofPopMatrix();

	box2 = vinnie.getBoundingBox();
	//ofSetColor(0,0,255,100);
	//ofRect(box2);
	centroid = vinnie.getCentroid2D();
	ofPushMatrix();
	ofTranslate(ofGetWidth()/8, ofGetHeight()/8);
	//ofTranslate(centroid.x, centroid.y);
	//ofDrawEllipse(centroid, 10, 10);
	ofScale(0.5,0.5,1);
	vinnie.draw();
	ofPopMatrix();
	//glBegin(GL_LINE_STRIP);
	////for(size_t i = lineShapeLookUpOffset; i < lineShapeLookUp + lineShapeLookUpOffset; i++){
	//for(size_t i = 0; i < vecs3.size(); i++){
	//	//ofSetColor(155,105,155, 255);
	//	float pct = ofMap(glm::distance(vecs3[i],centroid), 0,ofGetWidth(),0, 1);
	//	//pct = pow(pct,2);
	//	//ofSetColor(0,0,255, 255);
	//	//ofSetColor(255,255,255, 255*pct);
	//	glVertex3f(vecs3[i].x,vecs3[i].y,vecs3[i].z);
	//}
	//glEnd();
	//ofEndShape();

	//if(vecs3.size()  >  lineShapeLookUpOffset + lineShapeLookUp){
	//	lineShapeLookUpOffset++;
	//} else {
	//	lineShapeLookUpOffset = 0;
	//}
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
