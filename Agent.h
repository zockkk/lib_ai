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

	virtual void doAction(Environment state, const Matrix& action) = 0;

	void setReward(float reward) { this->reward += reward; }
	double getReward() { return reward; }
};

namespace test {
	using namespace test;

	template <typename T>
	class Agent : AbstractAgent {
		T agentModel;
	public:
		Agent(const Model model) : AbstractAgent() {
			agentModel = model;
		}
		void doAction(Environment *state, Matrix &action) override { 
			agentModel.forward(state);
			action = agentModel.output();
		}
	};
}



