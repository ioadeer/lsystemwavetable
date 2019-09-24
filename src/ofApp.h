#pragma once

#include "ofMain.h"
#include "Lsystem.h"
#include "audioTools.h"

#define MAX_TABOSC_SIZE 4096 
#define BUFFER_SIZE 512

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void audioOut(ofSoundBuffer &outBuffer);
		void exit();

		//Lsystem el;
		//Lsystem yo;
		//Lsystem ello;
		
		Lsystem * elloPtr;
		
		ofPolyline pauly;
		ofPolyline sonny;
		ofPolyline vinnie;
		ofPolyline vinniey;
		ofPolyline vinniex;
		vector <glm::vec3> vecs; 
		vector <glm::vec3> vecs2; 
		vector <glm::vec3> vecs3; 

		vector <glm::vec3>  * vecs3Ptr; 
		size_t lineShapeLookUpOffset;
		size_t lineShapeLookUp;
		vector <float> xNormalizedContent;
		ofRectangle box;
		ofRectangle box2;
		glm::vec3 centroid;

		vector <float> waveTableX;
		vector <float> waveTableY;
	
		vector <float> waveTableXPlay;
		vector <float> waveTableYPlay;

		vector <float> * waveTableXPtr;
		vector <float> * waveTableYPtr;

		bool updateWaveTable;	
		bool createNewLSystem;
		bool createLSystemFromGenome;
		bool createLSystemFromPreviousGenome;
		bool saveGenome;
		bool evolveLsystem;

		string globalRule;
		string output;
		string genomeOutput;

		std::mutex audioMutex;
    ofSoundStream soundStream;
		ofSoundBuffer setBuffer;
		ofSoundBuffer playBuffer;

		double phase;
		double phaseInc;
		//glm::vec3 strt;
};

