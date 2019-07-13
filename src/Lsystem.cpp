#include "Lsystem.h"

Lsystem::Lsystem(){
	axiom = "F";
	rule = "F+F-F";
	startLength= 5.0;
	theta = 2.0 * PI / 3.0;
	angle = 0.0;
	distance = 5.0;
	startPoint = glm::vec3(0.0,0.0, 0.0);
	position = startPoint;
	productionLookUpOffset = 0;
};
void Lsystem::setup(string _axiom, string _rule, float _startLength, float _theta, float _distance, glm::vec3  _startPoint){
	
	axiom = _axiom;
	production = _axiom;
	rule = _rule;
	startLength= _startLength;
	distance = _distance;
	theta = _theta;	
	startPoint = _startPoint;
	position = startPoint;
	productionLookUpOffset = 0;
};

void Lsystem::iterate(string & _prod, const string & _rule){
	generations++;
	utils::replaceAll(_prod, "F", _rule);
};

void Lsystem::simulate(int _gen){
	while(getAge() < _gen){
		iterate(production, rule);
	}
};

string Lsystem::getProduction(){
	return production;
}

//void Lsystem::update(Polyline & line){
//la idea es agarrar un vector de glm main y devolverlo con los puntos y dibujarlo en el main
void Lsystem::update(vector<glm::vec3> & _vecs){
	if(_vecs.size() > production.size()){
		cout << "vecs should be bigger than production" << endl;
	} else {
		position = startPoint;
		size_t prodLookUp = 0;
		for(size_t i = 0; i < _vecs.size();){
				char p = production[prodLookUp + productionLookUpOffset];
				prodLookUp++;
				switch(p){
				case 'F':
								{
								glm::vec3 temp;
								temp.x = sin(angle) * distance + position.x;
								temp.y = cos(angle) * distance + position.y;
								if(fabs(temp.x) > ofGetWidth()/2) temp.x =0;
								if(fabs(temp.y) > ofGetHeight()/2) temp.y =0;
								_vecs[i]= temp;
								position = temp;
								i++;
								break;
								}
				case '+':
								{
								angle += theta;
								break;
								}
				case '-':
								{
								angle -= theta;
								break;
								}
				default:
								{
								cout << "invalid" << endl;
								}
				}
		}
		if(production.size()> productionLookUpOffset + prodLookUp){ // o _vec.size() en lugar de prodLookUp
			productionLookUpOffset++;
		}else{
			productionLookUpOffset = 0;
		}
	}
}
