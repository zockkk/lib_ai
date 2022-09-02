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
	template <class T>
	class Model : public abstractModel<T> {
	public:
		Model() : abstractModel() {}
		Model(const T& in_model, std::vector<double>* in, std::vector<double>* out) : abstractModel(in_model, in, out) {}
		~Model() {
			if (this->input != nullptr) delete[] this->input;
			if (this->output != nullptr) delete[] this->output;
		}

		void forward(Matrix<T>* A) override {
			this->input = A;
			for (size_t i = 0; i < this->input.size(); i++) {
				for (size_t j = 0; j < this->output.size(); j++) {
					this->output[i] += this->output[i] * this->input[i];
				}
			}
		}

		void getActoin() {
			if (this->input != nullptr && this->output != nullptr) {
				this->model.setIn(this->input);
				this->model.setOut(this->output);
				this->model.forward();
			}
			else {
				std::cout << "error Model \n";
			}
		}
	};
}