#pragma once
#include "Environment.h"
#include "Model.h"

template <class Model_>
class AbstractAgent {

protected:
	double reward = 0.0;
	Model_ agentModel;
public:
	AbstractAgent() {}
	AbstractAgent(Model_ *model) {}
	virtual ~AbstractAgent() {}

	virtual void doAction(Matrix<double>* state) = 0;

	void setReward(double reward) { this.reward += reward; }
	double getReward() { return reward; }
};

namespace test {
	using namespace test;
	//realisation Agent classes test

	template <class Model_>
	class Agent : public AbstractAgent<Model_> {
		Model_ *agentModel;
		Matrix<double> *action = nullptr;
	public:
		Agent() : AbstractAgent<Model_>() {}
		Agent(Model_* model) : AbstractAgent<Model_>(model) {
			agentModel = model;
			action = agentModel->output;
		}

		virtual void doAction(Matrix<double>* state) override {
			agentModel->setIn(state);
			agentModel->work();
		}

		Matrix<double>* get() { return action; }
	};

	// test abstract agent class ++
	void testAgent_001() {
		std::cout << "start test\n";
		Matrix<double> inModel(5, 5, 0.1);
		Matrix<double> in({ 1,2,3,4,5 });
		//in->resize(5);
		Matrix<double> out({ 3,5,7,3,4 });
		Matrix<double> forwardOut(5, 1);
		//out->resize(5);
		Model testModel( &in, &out);
		Agent<Model> testAgent(&testModel);
		testAgent.get()->print();
	}
}



