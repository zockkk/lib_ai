#pragma once
#include "Agent.h"
#include "Model.h"

class abstractEnvironment {
	
public:
	Matrix<double> *currentState = nullptr;
	double currentReward = 0.0;
	abstractEnvironment() {}
	abstractEnvironment(Matrix<double> state) {
		currentState = &state;
	}
	virtual ~abstractEnvironment() {}

	virtual bool nextState(Matrix<double> *state,const Matrix<double> &action) = 0;
	double get_currentReward() { return currentReward; }
	Matrix<double> get_currentState() const { return *currentState; }
};


namespace test {
	// realisation environment classes test

	class Environment: public abstractEnvironment {
	public:
		Environment(): abstractEnvironment() {}
		Environment(Matrix<double> state) : abstractEnvironment(state) {
			//this->currentState = state;
		}
		~Environment() {
			//if (this->currentState != nullptr) {
			//	delete this->currentState;
			//}
		}
		
		virtual bool nextState(Matrix<double> *state,const Matrix<double> &action) override {
			if (normL1(*state + action) != 0) {
				//std::cout << "OK\n";
				this->currentState = state;
				*this->currentState += action;
				return true;
			}
			return false;
		}
	};

	//test abstract environment class ++
	void testEnvironment_001() {
		std::cout << "start test\n";
		Matrix<double> state({ 1,2,3,4,5 });
		Matrix<double> action({ 3,4,5,3,4 });
		Environment en(state);
		en.nextState(&state, action);
		state.print();

	}
}