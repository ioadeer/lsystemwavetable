#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  phase = 0;
  phaseInc = 0.3;// era 0.15  
  glm::vec3 strt(0.0,0.0,-1.0);

  glm::vec3 strt2(-150.0,-150.0,-1.0);
  elloPtr = new Lsystem();

  elloPtr->setup("F", "-F+F", 35.0, 1.0 * PI/2.0, 35.0, strt, 9); //era PI el 50.0 era 25.0 F+F-F+F
  /* ---- para evitar nullpointer si no se graba inicialmente */ 
  elloPtr->lSysActualStateToGenome();
  elloPtr->lSysActualStateToPreviousGenome();
  output = elloPtr->toString();
  waveTableX.resize(elloPtr->getNumberOfSteps());
  waveTableY.resize(elloPtr->getNumberOfSteps());

  waveTableXPlay = waveTableX;
  waveTableYPlay = waveTableY;

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
  createLSystemFromGenome = false;
  saveGenome = false;
  createLSystemFromPreviousGenome = false;

  controls = "CONTROLS"
    "\n Press 'r' to create new L-system"
    "\n Press 'a' to update wavetable"
    "\n Press 'e' to evolve L-system"
    "\n Press 's' to save L-system"
    "\n Press 'g' to create L-system from previous saved state";

  ofSoundStreamSettings settings;
  settings.numOutputChannels = 2;
  settings.sampleRate = 48000; // antes estaba en 44100
  settings.bufferSize = BUFFER_SIZE;
  settings.numBuffers = 3; // antes estaba en 4
  settings.setOutListener(this);
  soundStream.setup(settings);

}

//--------------------------------------------------------------
void ofApp::update(){


  if(createNewLSystem){
    float tempRand = ofRandom(1); 
    if(tempRand < 0.25) { globalRule = "F+F-F+F";}
    else if(tempRand > 0.25 && tempRand < 0.50) { globalRule = "F+F-F+F";}
    else if(tempRand > 0.50 && tempRand < 0.75) { globalRule = "-F+F";}
    else if(tempRand > 0.75) { globalRule = "-F-F-F+F";}
    glm::vec3 strt(0.0,0.0,-1.0);
    float randomDistance = ofRandom(20.0) + 15.0;
    int randomSimulateValue = 3 + (int) ofRandom(4);
    elloPtr->setup("F", globalRule, randomDistance, ofRandom(2)* 1.0 * PI/1.0, randomDistance, strt, randomSimulateValue); // agregue angulo random
    elloPtr->lSysActualStateToGenome();
    int tempStepsNumber = elloPtr->getNumberOfSteps();
    int tempResize = tempStepsNumber <= MAX_TABOSC_SIZE ? tempStepsNumber : MAX_TABOSC_SIZE;
    waveTableX.clear();
    waveTableX.resize(tempResize);
    waveTableY.clear();
    waveTableY.resize(tempResize);
    output = elloPtr->toString();
    //genomeOutput = elloPtr->lSysActualStateToString();
    createNewLSystem = false;
  }
  if(saveGenome){
    elloPtr->lSysActualStateToPreviousGenome();
    //output = elloPtr->lSysPreviousStateToString();
    saveGenome = false;
  }
  if(evolveLsystem){
    elloPtr->lSysActualStateToPreviousGenome();
    elloPtr->evolveLSystem();
    evolveLsystem = false;
  }
  if(createLSystemFromGenome){
    elloPtr->setLSystemWithActualGenome();
    int tempStepsNumber = elloPtr->getNumberOfSteps();
    output = elloPtr->lSysActualStateToString();
    int tempResize = tempStepsNumber <= MAX_TABOSC_SIZE ? tempStepsNumber : MAX_TABOSC_SIZE;
    waveTableX.clear();
    waveTableX.resize(tempResize);
    waveTableY.clear();
    waveTableY.resize(tempResize);
    createLSystemFromGenome = false;
  }

  if(createLSystemFromPreviousGenome){
    elloPtr->setLSystemWithPreviousGenome();
    output = elloPtr->lSysPreviousStateToString();
    int tempStepsNumber = elloPtr->getNumberOfSteps();
    int tempResize = tempStepsNumber <= MAX_TABOSC_SIZE ? tempStepsNumber : MAX_TABOSC_SIZE;
    waveTableX.clear();
    waveTableX.resize(tempResize);
    waveTableY.clear();
    waveTableY.resize(tempResize);
    createLSystemFromPreviousGenome = false;
  }

  //ello.nStepsAhead(1,vecs3);
  elloPtr->nStepsAhead(3); // no puede exceder el tamanio de una produccion
  vinnie.clear();
  //vinniey.clear();
  
  for(size_t i = 0 ; i < elloPtr->getlSystemVecs().size(); i++){
    glm::vec3 temp = elloPtr->getlSystemVecs()[i];
    vinnie.curveTo(temp.x,temp.y,temp.z);
  } 

  if(updateWaveTable){


    vinniey.clear();
    vinniex.clear();
    int tempSize =elloPtr->getlSystemVecs().size();
    if(tempSize <= MAX_TABOSC_SIZE){
      for(int i = 0; i < tempSize; i++){
        glm::vec3 temp = elloPtr->getlSystemVecs()[i];
        waveTableX[i] = temp.x; 
        waveTableY[i] = temp.y;
        vinniey.curveTo(temp.x,ofMap(i,0,tempSize,-ofGetHeight()/2,ofGetHeight()/2),0);
        vinniex.curveTo(ofMap(i,0,tempSize,-ofGetWidth()/2,ofGetWidth()/2), temp.y, 0);
      }
    } else {
      for(int i = 0; i < tempSize; i++){
        glm::vec3 temp = elloPtr->getlSystemVecs()[i];
        vinniey.curveTo(temp.x,ofMap(i,0,tempSize,-ofGetHeight()/2,ofGetHeight()/2),0);
        vinniex.curveTo(ofMap(i,0,tempSize,-ofGetWidth()/2,ofGetWidth()/2), temp.y, 0);
      }
      for(int i = 0; i < MAX_TABOSC_SIZE; i++){
        glm::vec3 temp = elloPtr->getlSystemVecs()[i];
        waveTableX[i] = temp.x; 
        waveTableY[i] = temp.y;
      }
    }
    utils::normalize(waveTableX);
    utils::normalize(waveTableY);

    unique_lock<mutex> lock(audioMutex);

    waveTableXPlay = waveTableX;
    waveTableYPlay = waveTableY;

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
  centroid = vinnie.getCentroid2D();
  ofPushMatrix();
  ofTranslate(ofGetWidth()/8, ofGetHeight()/8);
  ofScale(0.5,0.5,1);
  vinnie.draw();
  ofPopMatrix();
  
  ofDrawBitmapString(output, ofGetWidth()/2 -200,ofGetHeight()/2 - 100);
  //ofDrawBitmapString(genomeOutput, ofGetWidth()/2 -200,ofGetHeight()/2 - 100);
  ofDrawBitmapString(controls,-ofGetWidth()/2+280,ofGetHeight()/2 - 88);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == 'a'){
    updateWaveTable = true;
  }
  if(key == 'e'){
    evolveLsystem = true;
    createLSystemFromGenome = true;
    updateWaveTable = true;
  }
  if(key == 'g'){
    createLSystemFromPreviousGenome = true;
    updateWaveTable = true;
  }
  if(key == 's'){
    saveGenome = true;
  }
  if(key == 'r'){
    createNewLSystem = true;
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
    if(phase >= waveTableX.size()-1){phase = 0;}
    //currentSampleX = waveTableX[int(phase)];
    //currentSampleY = waveTableY[int(phase)];
    //linear interpolation
    currentSampleX = linearInterp(waveTableXPlay[int(phase)],waveTableXPlay[int(phase+1)],phase);
    currentSampleY = linearInterp(waveTableYPlay[int(phase)],waveTableYPlay[int(phase+1)],phase);
    outBuffer.getSample(i,0) = currentSampleX;  
    outBuffer.getSample(i,1) = currentSampleY;  
  }
  //waveTableXPlay = waveTableX;
  //waveTableYPlay = waveTableY;
}

void ofApp::exit(){
    ofSoundStreamClose();
}

