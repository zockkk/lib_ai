#pragma once
#include "Matrix.h"

template <typename T>
class abstractModel {
protected:
	T model;
	std::vector<double>* input = nullptr;
	std::vector<double>* output = nullptr;
public:
	abstractModel() { model = 0; }
	abstractModel(const T& in_model, std::vector<double>* in, std::vector<double>* out) { model = in_model; input = in; out = output; }

	~abstractModel() {
		if (input != nullptr) delete[] input;
		if (output != nullptr) delete[] output;
	}

	virtual void forward(Matrix<T> *A) = 0;

	std::vector<double> out() { return (*output); }
};


namespace test {
	template <typename T>
	class Model : abstractModel {
		Model():abstractModel() {}
		Model(const T& in_model, std::vector<double>* in, std::vector<double>* out):abstractModel(const T& in_model, std::vector<double>* in, std::vector<double>* out) {}
		~Model():~abstractModel() {}

		void forward(Matrix<T>* A) override {
			input = A;
			for (size_t i = 0; i < input.size(); i++) {
				for (size_t j = 0; j < output.size(); j++) {
					output[i] += output[i] * input[i];
				}
			}
		}

		void getActoin() {
			if (input != nullptr && output != nullptr) {
				Model.setIn(input);
				Model.setOut(output);
				Model.forward();
			}
			else {
				std::cout << "error Model \n";
			}
		}
	};
}