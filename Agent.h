#pragma once
#include "Environment.h"
#include "Model.h"

template <typename T>
class AbstractAgent {

protected:
	double reward;

public:
	AbstractAgent() {}
	virtual ~AbstractAgent() {}

	virtual void doAction(T state, const Matrix<double>& action) = 0;

	void setReward(double reward) { this->reward += reward; }
	double getReward() { return reward; }
};

namespace test {
	using namespace test;

	template <typename T>
	class Agent : public AbstractAgent<T> {
		T agentModel;
	public:
		Agent() : AbstractAgent() {}
		Agent(const Model<T> model) {
			agentModel = model;
		}
		void doAction(Environment<T> *state, Matrix<double> &action) override { 
			agentModel.forward(state);
			action = agentModel.output();
		}
	};
}



