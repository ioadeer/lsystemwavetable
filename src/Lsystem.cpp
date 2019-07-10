#include "Lsystem.h"

Lsystem::Lsystem(){
	axiom = "F";
	rule = "F+F-F";
	startLength= 5.0;
	theta = 2.0 * PI / 3.0;

};
void Lsystem::setup(string _axiom, string _rule, float _startLength, float _theta){
	
	axiom = _axiom;
	production = _axiom;
	rule = _rule;
	startLength= _startLength;
	theta = theta;

};

void Lsystem::iterate(string & _prod, const string & _rule){
	generations++;
	//cout << generations << " generacion: " << endl;
	//cout << "prod en iterate : "<< endl;
	//cout << _prod << endl;
	utils::replaceAll(_prod, "F", _rule);
	//cout<< "despues de replace" << endl;
	//cout << _prod << endl;
};

void Lsystem::simulate(int _gen){
	while(getAge() < _gen){
		//cout<< "en simulate" << endl;
		//production = iterate(production, rule);
		iterate(production, rule);
	}
};

string Lsystem::getProduction(){
	return production;
}
