#pragma once
#include "Agent.h"
#include "Model.h"

template <typename T>
class abstractEnvironment {
protected:
	Matrix<T> *currentState = nullptr;
	double currentReward = 0.0;
public:
	abstractEnvironment() {}
	virtual ~abstractEnvironment() {}

	virtual T nextState(Matrix<T> state, Matrix<T> action) = 0;
	double get_currentReward() { return currentReward; }
	const Matrix<T> get_currentState() { return currentState; }
};


namespace test {
	using namespace test;

	template <typename T>
	class Environment: public abstractEnvironment<T> {
		Environment(Matrix<T> *state) : abstractEnvironment() {
			this->currentState = state;
		}
		~Environment() {
			if (this->currentState != nullptr) {
				delete[] this->currentState;
			}
		}
		
		T nextState(Matrix<T> state,const Matrix<T> action) override {
			if ((state + action).absValue() != 0) {
				(*this->currentState) = state + action;
				return true;
			}
			return false;
		}
	};
}