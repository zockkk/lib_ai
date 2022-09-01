#pragma once
#include "Matrix.h"
#include "Environment.h"
#include "Model.h"




template <typename T>
class AbstractAgent {

protected:
	float reward;

public:
	AbstractAgent() {}
	virtual ~AbstractAgent() {}

	virtual void doAction(Environment state, const Matrix& action) = 0;

	void setReward(float reward) { this->reward += reward; }
	float getReward() {	return reward; }
};

namespace test {
	template <typename T>
	class Agent : AbstractAgent {
		T agentModel;
	public:
		Agent(const Model model) {
			agentModel = model;
		}
		void doAction(Environment state, const Matrix& action) override { }
	};
}



