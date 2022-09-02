#pragma once
#include "Matrix.h"

template <typename T>
class abstractModel {
protected:
	T model;
	std::vector<double>* input;
	std::vector<double>* output;
public:
	abstractModel() { model = 0; }
	abstractModel(const T in_model, std::vector<double>* in, std::vector<double>* out) { model = in_model; input = in; out = output; }

	void operator = (abstractModel& a) {
		model = a.model;
		for (size_t i = 0; i < input.size(); i++) {
			(*input)[i] = (*a.input)[i];
		}
		for (size_t i = 0; i < output.size(); i++) {
			(*output)[i] = (*a.output)[i];
		}
	}

	void operator = (abstractModel &&a) {
		swap(model,a.model);
		swap(input, a.input);
		swap(output, a.output);
	}

	~abstractModel() {
		//if (input != nullptr) delete input;
		//if (output != nullptr) delete output;
	}

	virtual void forward(Matrix<double> &A) = 0;

	//std::vector<double> out() { return (*output); }
};

namespace test {
	template <class T>
	class Model : public abstractModel<T> {
	private:
		T model;
		std::vector<double> *input = nullptr;
		std::vector<double> *output = nullptr;
	public:
		Model() : abstractModel<T>() {}
		Model(const T in_model, std::vector<double>* in, std::vector<double>* out) : abstractModel<T>(in_model, in, out) 
		{ 
			model = in_model; 
			input = in;
			output = out; }

		void operator = (Model& a) {
			model = a.model;
			input = *a.input;
			output = *a.output;
		}
		void operator = (Model&& a) {
			swap(model, a.model);
			swap(input, a.input);
			swap(output, a.output);
		}

		~Model() {
			//if (input != nullptr) delete input;
			//if (output != nullptr) delete output;
		}

		void forward(Matrix<double>& A) override {
			//A.to_vector(input);
			Matrix<double> out((*output));
			Matrix<double> in((*input));
			A = in + out;
		}

		void getActoin() {
			if (this.input != nullptr && this.output != nullptr) {
				this.model.setIn(this.input);
				this.model.setOut(this.output);
				this.model.forward();
			}
			else {
				std::cout << "error Model \n";
			}
		}
	};
}