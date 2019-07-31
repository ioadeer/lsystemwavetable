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
	//cout << production << endl;
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
		//position = startPoint;
		prodLookUp = 0;
		size_t v = 0;
		for(size_t i = 0; i < production.size();i++){
				//char p = production[prodLookUp + productionLookUpOffset];
				char p = production[i];
				prodLookUp++;
				switch(p){
				case 'F':
								{
								glm::vec3 temp;
								temp.x = sin(angle) * distance + position.x;
								temp.y = cos(angle) * distance + position.y;
								//if(glm::distance(temp, startPoint) < distance){
								//	temp.x = startPoint.x;
								//	temp.y = startPoint.y;
								//} else {
								//temp.x = sin(angle) * distance + position.x;
								//temp.y = cos(angle) * distance + position.y;
								if(fabs(temp.x) > ofGetWidth()/2) temp.x =0;
								if(fabs(temp.y) > ofGetHeight()/2) temp.y =0;
								//}
								_vecs[v]= temp;
								position = temp;
								v++;
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
		//angle = theta;
		//prodLookUp;
		if(production.size() > productionLookUpOffset + prodLookUp){ // o _vec.size() en lugar de prodLookUp
			productionLookUpOffset++;
		}else{
			productionLookUpOffset = 0;
		}
	}
}

void Lsystem::oneStep(vector<glm::vec3> & _vecs){

	if(prodLookUp < production.size()-1) {
		prodLookUp++;
	} else {
		prodLookUp = 0;
	}
	char p = production[prodLookUp];
	switch(p){
		case 'F':
						{
						for(size_t i = 0; i < _vecs.size()-1; i++){
							glm::vec3 temp = _vecs[i+1];
							_vecs[i] = temp;
						}
						glm::vec3 temp;
						temp.x = sin(angle) * distance + position.x;
						temp.y = cos(angle) * distance + position.y;
						if(fabs(temp.x) > ofGetWidth()/2) temp.x =0;
						if(fabs(temp.y) > ofGetHeight()/2) temp.y =0;
						_vecs[_vecs.size()-1]= temp;
						position = temp;
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
		case '\0':
						{
							cout<< "end of string" << endl;
							break;
						}
		default:
						{
						cout << "invalid" << endl;
						}
		}
}
void Lsystem::countSteps(){
	numberOfSteps =0;
	for(size_t i =0; i < production.size(); i++){
		if(production[i] == 'F') numberOfSteps++;
	}
}
int Lsystem::getNumberOfSteps(){
	countSteps();
	return numberOfSteps;
}
