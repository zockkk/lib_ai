#pragma once
#include "Agent.h"
#include "Model.h"

template <typename T>
class abstractEnvironment {
protected:
	Matrix<T> *currentState = nullptr;
	double currentReward = 0.0;
public:
	AbstractEnvironment() {}
	virtual ~AbstractEnvironment() {}

	virtual T nextState(Matrix<T> state, Matrix<T> action) = 0;
	double get_currentReward() { return currentReward; }
	const Matrix<T> get_currentState() { return currentState; }
};


namespace test {
	template <typename T>
	class Environment: abstractEnvironment {
		Environment(Matrix<T> *state) : abstractEnvironment() {
			currentState = state;
		}
		~Environment() {
			if (currentState != nullptr) {
				delete[] currentState;
			}
		}

		boll nextState(Matrix<T> state,const Matrix<T> action) override {
			if ((state + action).absValue() != 0) {
				(*currentState) = state + action;
				return true;
			}
			return false;
		}
	};
}