#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	phase = 0;
 	phaseInc = 0.15;	
	glm::vec3 strt(0.0,0.0,-1.0);

	glm::vec3 strt2(-150.0,-150.0,-1.0);
	elloPtr = new Lsystem();

	elloPtr->setup("F", "-F+F", 35.0, 1.0 * PI/2.0, 35.0, strt); //era PI el 50.0 era 25.0 F+F-F+F
	//cout << "llego hasta aca" << endl;
	//elloPtr->showAllValues();
	elloPtr->simulate(9);	
	//elloPtr->showAllValues();
	elloPtr->mapProductionToTurtleSteps();
	waveTableX.resize(elloPtr->getNumberOfSteps());
	waveTableY.resize(elloPtr->getNumberOfSteps());

	//cout << (*elloPtr).getNumberOfSteps() << endl;

	ofBackground(0,0,0);
	ofSetFrameRate(30);
	lineShapeLookUpOffset = 1 ;
	lineShapeLookUp = 35;

	for(size_t i = 0 ; i < elloPtr->getlSystemVecs().size(); i++){
		glm::vec3 temp = elloPtr->getlSystemVecs()[i];
		vinnie.addVertex(temp.x,temp.y,temp.z);
	}	

	updateWaveTable = false;
	createNewLSystem = false;
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


	if(createNewLSystem){
		delete elloPtr;
		float tempRand = ofRandom(1);	
		if(tempRand < 0.25) { globalRule = "F+F-F+F";}
		else if(tempRand > 0.25 && tempRand < 0.50) { globalRule = "F+F-F+F";}
		else if(tempRand > 0.50 && tempRand < 0.75) { globalRule = "-F+F";}
		else if(tempRand > 0.75) { globalRule = "-F-F-F+F";}
		glm::vec3 strt(0.0,0.0,-1.0);
		elloPtr = new Lsystem(); //"F", "-F-F-F+F", 35.0, 1.0 * PI/2.0, 35.0, strt);
		//cout << globalRule << endl;
		elloPtr->setup("F", globalRule, 35.0, ofRandom(2)* 1.0 * PI/2.0, 35.0, strt); // agregue angulo random
		//elloPtr->setup("F", "-F-F-F+F", 35.0, 1.0 * PI/2.0, 35.0, strt);
		int randomSimulateValue = 3 + (int) ofRandom(4);
		//elloPtr->simulate(3);	
		elloPtr->simulate(randomSimulateValue);	
		elloPtr->mapProductionToTurtleSteps();
		//elloPtr->showAllValues();
		waveTableX.clear();
		waveTableX.resize(elloPtr->getNumberOfSteps());
		waveTableY.clear();
		waveTableY.resize(elloPtr->getNumberOfSteps());
		//cout << (*elloPtr).getNumberOfSteps() << endl;
		output = elloPtr->toString();
		createNewLSystem = false;
	}


	unique_lock<mutex> lock(audioMutex);
	//ello.nStepsAhead(1,vecs3);
	elloPtr->nStepsAhead(8); // no puede exceder el tamanio de una produccion
	vinnie.clear();
	//vinniey.clear();
	
	for(size_t i = 0 ; i < elloPtr->getlSystemVecs().size(); i++){
		glm::vec3 temp = elloPtr->getlSystemVecs()[i];
		//cout << "Temp: " << temp << endl;
		vinnie.curveTo(temp.x,temp.y,temp.z);
	}	

	if(updateWaveTable){
		vinniey.clear();
		vinniex.clear();
		int tempSize =elloPtr->getlSystemVecs().size();
		for(int i = 0; i < tempSize; i++){
			glm::vec3 temp = elloPtr->getlSystemVecs()[i];
			waveTableX[i] = temp.x;	
			waveTableY[i] = temp.y;
			vinniey.curveTo(temp.x,ofMap(i,0,tempSize,-ofGetHeight()/2,ofGetHeight()/2),0);
			vinniex.curveTo(ofMap(i,0,tempSize,-ofGetWidth()/2,ofGetWidth()/2), temp.y, 0);
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
	
	ofDrawBitmapString(output, ofGetWidth()/2 -200,ofGetHeight()/2 - 80);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'a'){
		updateWaveTable = true;
	}
	if(key == 'r'){
		createNewLSystem = true;
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
		if(phase >= waveTableX.size()-1){phase = 0;}
		//currentSampleX = waveTableX[int(phase)];
		//currentSampleY = waveTableY[int(phase)];
		//linear interpolation
		currentSampleX = linearInterp(waveTableX[int(phase)],waveTableX[int(phase+1)],phase);
		currentSampleY = linearInterp(waveTableY[int(phase)],waveTableY[int(phase+1)],phase);
		outBuffer.getSample(i,0) = currentSampleX;	
		outBuffer.getSample(i,1) = currentSampleY;	
	}
}

void ofApp::exit(){
    ofSoundStreamClose();
}

