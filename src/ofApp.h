#pragma once

#include "ofMain.h"
#include "Lsystem.h"

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

		Lsystem el;
		Lsystem yo;
		Lsystem ello;
		ofPolyline pauly;
		vector <glm::vec3> vecs; 
		vector <glm::vec3> vecs2; 
		vector <glm::vec3> vecs3; 
		size_t lineShapeLookUpOffset;
		size_t lineShapeLookUp;
};
