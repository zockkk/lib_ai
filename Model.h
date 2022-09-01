#pragma once
#include "Agent.h"
#include "Environment.h"

template <typename T>
class abstractModel {
protected:
	T model;
	vector<double>* input = nullptr;
	vector<double>* output = nullptr;
public:
	abstractModel() { model = 0; }
	abstractModel(const T& in_model, vector<double>* in, vector<double>* out) { model = in_model; input = in; out = output; }

	~abstractModel() {
		if (input != nullptr) delete[] input;
		if (output != nullptr) delete[] output;
	}

	virtual void forward() = 0;
};
namespace test {
	template <typename T>
	class Model : abstractModel {
		Model()::abstractModel() {}
		Model(const T& in_model, vector<double>* in, vector<double>* out)::abstractModel(const T& in_model, vector<double>* in, vector<double>* out) {}
		~Model()::~abstractModel() {}

		void forward() override {
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