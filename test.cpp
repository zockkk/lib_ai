#include "Agent.h"
#include "Environment.h"

int main() {
	using namespace test;
	std::cout << "start test";
	Matrix<double> inModel(5, 5, 0.1);
	std::vector<double> in(5);
	//in->resize(5);
	std::vector<double> out(5);
	//out->resize(5);
	Model<Matrix<double>> testModel(inModel, &in, &out);
	return 0;
}