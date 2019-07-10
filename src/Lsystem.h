#ifndef Lsystem_h
#define Lsystem_h

#include "ofMain.h"
#include "utils.h"

class Lsystem{

	public:
		
		Lsystem();
		void setup(string _axiom, string _rule, float _startLength, float _theta);
		int	getAge(){return generations;};
		void simulate(int _gen);
		//string iterate(string & _prod, const string &  _rule);
		void iterate(string & _prod, const string &  _rule);
		string getProduction();
		
	private:
		int steps =0;
		string axiom;
		string rule;
		string production;

		float startLength;
		float drawLength;
		float theta;
		int generations;
};
#endif
