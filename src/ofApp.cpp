#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	phase = 0;
 	phaseInc = 0.15;	
	glm::vec3 strt(0.0,0.0,-1.0);
	glm::vec3 strt2(-150.0,-150.0,-1.0);
	//el.setup("F", "F+F-F+F", 25.0, 0.5 * PI/2.0, 25.0, strt); //era PI el 50.0 era 25.0
	//yo.setup("F", "F+F-F+F", 15.0, 0.25 * PI/2.0, 15.0, strt); //era PI el 50.0 era 25.0 r: F+F-F+F+F
	//ello.setup("F", "F+F-F+F", 35.0, 0.25 * PI/2.0, 35.0, strt); //era PI el 50.0 era 25.0 F+F-F+F
	//ello.setup("F", "F+F-F+F", 25.0, 0.5 * PI/2.0, 25.0, strt); //era PI el 50.0 era 25.0 F+F-F+F
	ello.setup("F", "-F+F", 35.0, 1.0 * PI/2.0, 35.0, strt); //era PI el 50.0 era 25.0 F+F-F+F
	
	//cout << el.getProduction() << endl;
	//el.simulate(5);
	//yo.simulate(5); //era 3
	ello.simulate(9);
	vecs3.resize(ello.getNumberOfSteps());
	waveTableX.resize(ello.getNumberOfSteps());
	waveTableY.resize(ello.getNumberOfSteps());
	cout << ello.getNumberOfSteps() << endl;

	ofBackground(0,0,0);
	ofSetFrameRate(30);
	//el.update(vecs);
	//yo.update(vecs2);
	ello.update(vecs3);
	lineShapeLookUpOffset = 1 ;
	lineShapeLookUp = 35;

	for(size_t i = 0 ; i < vecs3.size(); i++){
		vinnie.addVertex(vecs3[i].x,vecs3[i].y,vecs3[i].z); //xNormalizedContent[i] = ofMap(vecs2[i].x, -ofGetWidth()/2, ofGetWidth()/2, -1,1);
		//cout<< xNormalizedContent[i] << endl;
		//waveTableX[i] = ofClamp(vecs3[i].x, -0.9, 0.9);	
	}	

	updateWaveTable = false;

	ofSoundStreamSettings settings;
  settings.numOutputChannels = 2;
  settings.sampleRate = 48000; // antes estaba en 44100
  settings.bufferSize = 512;
  settings.numBuffers = 3; // antes estaba en 4
  settings.setOutListener(this);
  soundStream.setup(settings);

}

//--------------------------------------------------------------
void ofApp::update(){

	unique_lock<mutex> lock(audioMutex);

	ello.nStepsAhead(1,vecs3);
	vinnie.clear();
	//vinniex.clear();
	//vinniey.clear();
	for(int i = 0; i < vecs3.size(); i++){
			//vecs3[i].z-= 1.5;
			//vecs3[i].z-= 2.5;
			//vinnie.addVertex(vecs3[i].x,vecs3[i].y,vecs3[i].z);
			vinnie.curveTo(vecs3[i].x,vecs3[i].y,vecs3[i].z);
			//vinniey.curveTo(vecs3[i].x,ofMap(i,0,vecs3.size(),-ofGetHeight()/2,ofGetHeight()/2),0);
			//vinniex.curveTo(ofMap(i,0,vecs3.size(),-ofGetWidth()/2,ofGetWidth()/2), vecs3[i].y, 0);
	}
	
	if(updateWaveTable){
		vinniey.clear();
		vinniex.clear();
		for(int i = 0; i < vecs3.size(); i++){
			waveTableX[i] = vecs3[i].x;	
			waveTableY[i] = vecs3[i].y;
			vinniey.curveTo(vecs3[i].x,ofMap(i,0,vecs3.size(),-ofGetHeight()/2,ofGetHeight()/2),0);
			vinniex.curveTo(ofMap(i,0,vecs3.size(),-ofGetWidth()/2,ofGetWidth()/2), vecs3[i].y, 0);
		}
		utils::normalize(waveTableX);
		utils::normalize(waveTableY);
	//	for(size_t i = 0; i < setBuffer.getNumFrames(); i++){
	//		setBuffer.getSample(i, 0) = waveTableX[i];		
	//	}
		//for(int i = 0; i < vecs3.size(); i++){
		//	cout << waveTableX[i] << endl;
		//}
		updateWaveTable = false;
	}
 	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableAlphaBlending();
	ofTranslate(ofGetWidth()/2,ofGetHeight()/2);

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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'r'){
		updateWaveTable = true;
	}
	else{
		cout << "Press r tu update wavetable " << endl;
	}
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

void ofApp::audioOut(ofSoundBuffer &outBuffer){

	unique_lock<mutex> lock(audioMutex);

	for(size_t i = 0; i < outBuffer.getNumFrames(); i++){
		float currentSampleX;
		float currentSampleY;
		phase += phaseInc;
		if(phase >= waveTableX.size()){phase = 0;}
		currentSampleX = waveTableX[int(phase)];
		currentSampleY = waveTableY[int(phase)];
		outBuffer.getSample(i,0) = currentSampleX;	
		outBuffer.getSample(i,1) = currentSampleY;	
	}
}

void ofApp::exit(){
    ofSoundStreamClose();
}

