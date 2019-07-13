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
};
void Lsystem::setup(string _axiom, string _rule, float _startLength, float _theta, float _distance, glm::vec3  _startPoint){
	
	axiom = _axiom;
	production = _axiom;
	rule = _rule;
	startLength= _startLength;
	distance = _distance;
	theta = theta;	
	startPoint = _startPoint;
	position = startPoint;

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
	//size_t steps = 3;
	//cout << "Lsys update" << endl;
	if(_vecs.size() > production.size()){
		//cout << "vecs should be bigger than production" << endl;
	} else {
		//for(size_t i = 0; i < production.size() - steps ; i+= steps){
		position = startPoint;
		size_t prodLookUp = 0;
		//cout << "antes del loop" << endl;
		//cout << _vecs.size() << endl;
		for(size_t i = 0; i < _vecs.size();){
			//cout << i << endl;
			
			//for(size_t y = 0; y < steps; y++){
				char p = production[prodLookUp];
				prodLookUp++;
				//cout << p << endl;
				switch(p){
				case 'F':
								{
								glm::vec3 temp;
								temp.x = sin(angle) * distance + position.x;
								temp.y = cos(angle) * distance + position.y;
								//cout<< temp.x << endl;
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
			//}
		}
	}
}
