#include "Agent.h"
#include "Environment.h"


void test_RL_001() {
	using namespace test;
	std::cout << "start test\n";
	Matrix<double> inModel(5, 5, 0.1);
	Matrix<double> in({ 1,2,3,4,5 });
	//in->resize(5);
	Matrix<double> out({ 3,5,7,3,4 });
	Matrix<double> forwardOut(5, 1);
	//out->resize(5);
	Model testModel(&in, &out);
	Agent<Model> testAgent(&testModel);
	Environment testEn(in);
	testAgent.get()->print();
	testAgent.doAction(&in);
	testEn.nextState(&in, out);
	in.print();
	out.print();
}

int main() {
	using namespace test;
	testModel_002();
	return 0;
}