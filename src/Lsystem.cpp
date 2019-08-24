#include "Lsystem.h"

Lsystem::Lsystem(){
	//axiom = "F";
	rule = "F+F-F";
	cout << "Rule on creator :" << rule << endl;
	//startLength= 5.0;
	//theta = 2.0 * PI / 3.0;
	//angle = 0.0;
	//distance = 5.0;
	//startPoint = glm::vec3(0.0,0.0, 0.0);
	//position = startPoint;
	//productionLookUpOffset = 0;
};

Lsystem::~Lsystem(){ cout << " Class destroyed"<<endl;};

void Lsystem::setup(string _axiom, string _rule, float _startLength, float _theta, float _distance, glm::vec3  _startPoint){
	this->axiom = _axiom;
	production = _axiom;
	rule = _rule;
	cout << "Rule on setup :" << rule << endl;
	startLength= _startLength;
	distance = _distance;
	theta = _theta;	
	startPoint = _startPoint;
	position = startPoint;
	productionLookUpOffset = 0;
	generations = 0;
};


void Lsystem::iterate(string & _prod, const string & _rule){
	//cout << "generations on iterate " << generations << endl;
	generations++;
	utils::replaceAll(_prod, "F", _rule);
	//cout << production << endl;
};

void Lsystem::simulate(int _gen){
	//cout << "generations on simulate " <<getAge() << endl;
	while(getAge() < _gen){
		//cout << "Before iterate on simulate: " << _gen << endl;
		//cout << "Production : " << production << endl;
		//cout << "Rule: " << rule << endl;
		iterate(production, rule);
		//cout << "After iterate on simulate: " << _gen << endl;
		//cout << "Production : " << production << endl;
		//cout << "Rule: " << rule << endl;
	}
};

string Lsystem::getProduction(){
	return production;
}

//void Lsystem::update(Polyline & line){
//la idea es agarrar un vector de glm main y devolverlo con los puntos y dibujarlo en el main
// update usande vector de glm vecs internos de la clase

void Lsystem::mapProductionToTurtleSteps(){
	float size = getNumberOfSteps();
	//lSystemVecs.clear();
	lSystemVecs.resize(size);
	cout << "Size of vec :" <<  lSystemVecs.size() << endl;
	if(lSystemVecs.size() > production.size()){
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
								lSystemVecs[v]= temp;
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
									//cout << "llego hasta aca" << endl;
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

// one step ahead con vecs internos
void Lsystem::nStepsAhead(size_t _n){
  prodLookUp = prodLookUp + _n >= production.size() ? 0 : prodLookUp;
	if(prodLookUp + _n < production.size()){
	//if(true){
		for(size_t i = 0; i < lSystemVecs.size()-_n; i++){
			glm::vec3 temp = lSystemVecs[i+_n];
			lSystemVecs[i] = temp;
		}
		for(size_t i = 0; i  < _n;){
			prodLookUp++; //= i;
  		prodLookUp = prodLookUp + _n >= production.size() ? 0 : prodLookUp;
			char p = production[prodLookUp];
			switch(p){
				case 'F':
								{
									glm::vec3 temp;
									temp.x = sin(angle) * distance + position.x;
									temp.y = cos(angle) * distance + position.y;
									if(fabs(temp.x) > ofGetWidth()/2) temp.x =0;
									if(fabs(temp.y) > ofGetHeight()/2) temp.y =0;
									lSystemVecs[lSystemVecs.size()-_n+i]= temp;
									position = temp;
									//cout << temp << endl;
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
				case '\0':
								{
									cout << "End of string" << endl;
									cout << prodLookUp << endl;
									cout << production.size() << endl;
									break;
								}
				default:
								{
									cout << "invalid" << endl;
									cout << prodLookUp << endl;
									cout << production.size() << endl;
								}
			}
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

void Lsystem::showAllValues(){
	cout <<"Axiom :"<< this->axiom <<endl;
	cout <<"Rule:"<< this->production <<endl;
	cout <<"Theta:"<< this->theta <<endl;

}
