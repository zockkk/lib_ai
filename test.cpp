#include "Agent.h"
#include "Environment.h"
#include <random>


void test_RL_001() {
	// test abstract model RL ++
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
	// test learning perceptron layer ++
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
			nnl.work();
			errorY = out - l_out[i];
			//errorY.print();
			nnl.learn();
			std::cout << normL1(errorY)<<'\n';
		}
	}
	nnl.print();

}

void test_RL_003() {
	// test learning fully connected perceptron
	using namespace perc;
	std::cout << "start test\n";
	const int size = 300;
	//input weignts outputs for learn
	Matrix<double> l_in[size];
	Matrix<double> l_out1[size];
	Matrix<double> l_out2[size];
	const Matrix<double> l_w1({ {1.1,2.3}, {1.5,0.5} });
	const Matrix<double> l_w2({ {1.1,2.3}, {1.5,0.5} });
	for (int i = 0; i < size; i++) {
		l_in[i] = std::vector<double>({ -1.0 + (double(rand() % 20)) / 10.0, -1.0 + (double(rand() % 20)) / 10.0 });
		l_out1[i] = l_w1 * l_in[i];
		l_out2[i] = l_w2 * l_out1[i];
	}
	Matrix<double> in(2, 1);
	Matrix<double> out(2, 1);
	NN_Model nn(&in, &out, {2,2,2});

	Matrix<double> errorY(2, 1);
	Matrix<double> errorX(2, 1);
	nn.setter(&errorX, &errorY);
	// the learning process on the regression
	for (int j = 0; j < 1000; j++) {
		for (int i = 0; i < size; i++) {
			in = l_in[i];
			nn.work();
			errorY = out - l_out2[i];
			//errorY = Pow(errorY, 2);
			nn.learn_NN();
			std::cout << normL1(errorY) << '\n';
		}
	}
	Print_Model(nn);
}

int main() {
	using namespace test;
	test_RL_003();
	return 0;
}