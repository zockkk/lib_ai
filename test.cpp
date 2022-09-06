#include "Agent.h"
#include "Environment.h"
#include <random>


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

void test_RL_002() {
	using namespace perc;
	std::cout << "start test\n";
	const int size = 20;
	//input weignts outputs for learn
	Matrix<double> l_in[size];
	Matrix<double> l_out[size];
	const Matrix<double> l_w({ {1.1,2.3}, {1.5,0.5} });
	for (int i = 0; i < size; i++) {
		l_in[i] =  std::vector<double>( { -1.0 + (double(rand() % 20)) / 10.0, -1.0 + (double(rand() % 20)) / 10.0 });
		l_out[i] = l_w * l_in[i];
	}
	Matrix<double> in(2,1);
	Matrix<double> out(2, 1);
	Model nnl(&in,&out);

	Matrix<double> errorY(2, 1);
	Matrix<double> errorX(2, 1);
	nnl.set_errors(&errorX, &errorY);
	// the learning process on the regression
	for (int j = 0; j < 1000; j++) {
		for (int i = 0; i < size; i++) {
			in = l_in[i];
			nnl.forward();
			errorY = out - l_out[i];
			//errorY.print();
			nnl.learn();
			std::cout << normL1(errorY)<<'\n';
		}
	}
	nnl.print();

}

int main() {
	using namespace test;
	test_RL_002();
	return 0;
}