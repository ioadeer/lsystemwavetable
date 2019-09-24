#ifndef Lsystem_h
#define Lsystem_h

#include "ofMain.h"
#include "utils.h"

class Lsystem{

	struct Genome{
		string genAxiom;
		string genRule;
		float genDistance;
		float genTheta;
		int genNumberOfSteps;
		int genNumberOfIterations;
	};

	public:
		
		Lsystem();
		~Lsystem();
		void setup(string _axiom, string _rule, float _startLength, float _theta, float distance, glm::vec3 _startPoint, int _numberOfIterations);
		void setLSystemWithGenome(Genome _genome);
		void setLSystemWithPreviousGenome();
		void setLSystemWithActualGenome();
		int	getAge(){return generations;};
		void simulate(int _gen);
		//string iterate(string & _prod, const string &  _rule);
		void iterate(string & _prod, const string &  _rule);
		string getProduction();
		void mapProductionToTurtleSteps();
		void countSteps();
		int getNumberOfSteps();
		void nStepsAhead(size_t _n);
		vector<glm::vec3> getlSystemVecs(){return lSystemVecs;};
		void showAllValues(); 
		string toString();

		void lSysToGenome(Genome &_genome);
		void lSysActualStateToGenome();
		void lSysActualStateToPreviousGenome();
		string genomeToString(Genome _genome);
		string lSysActualStateToString();
		string lSysPreviousStateToString();

		void evolveGenome(Genome &_genome);
		void modifyRule(Genome &_genome);
		void modifyTheta(Genome &_genome);
		void modifyDistance(Genome &_genome);
		void modifyNumberOfIterations(Genome &_genome);

		int countStepsOnRule(string _rule);
		int countDirectionsOnRule(string _rule);
		void assignStepOnDirection(string &_rule);
		void assignDirectionOnStep(string &_rule); 
		void changeStepOrDirectionRandomly(string &_rule);
		void evolveLSystemSavePreviousState();
		void evolveLSystem();

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
		size_t prodLookUp;
		int numberOfSteps;
		vector <glm::vec3> lSystemVecs;
		int numberOfIterations;

		Genome previousState;
		Genome actualState;

};
#endif
