#ifndef Lsystem_h
#define Lsystem_h

#include "ofMain.h"
#include "utils.h"

class Lsystem{

	public:
		
		Lsystem();
		void setup(string _axiom, string _rule, float _startLength, float _theta, float distance, glm::vec3 _startPoint);
		int	getAge(){return generations;};
		void simulate(int _gen);
		//string iterate(string & _prod, const string &  _rule);
		void iterate(string & _prod, const string &  _rule);
		string getProduction();
		void update();
//		void draw();
		//void update(ofPolyline & line);
		void update(vector<glm::vec3> & _vec);
		
	private:
		int steps =0;
		string axiom;
		string rule;
		string production;

		float startLength;
		float drawLength;
		float theta;
		float angle;
		float distance;
		int generations;
		glm::vec3 startPoint;
		glm::vec3 position;
		size_t productionLookUpOffset;
};
#endif
