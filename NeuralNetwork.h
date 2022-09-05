#pragma once
#include "Matrix.h"


class abstractLayer {
public:
	// Matrix of inputs/outputs/weights NN 
	Matrix<double>* input = nullptr;
	Matrix<double>* output = nullptr;
	Matrix<double> w;

	abstractLayer() {}
	abstractLayer(Matrix<double>* in, Matrix<double>* out) {
		input = in;
		output = out;
		w = Matrix<double>(output->getRows(), input->getRows(), 0.1);
	}
	~abstractLayer() {
		if (input != nullptr) delete input;
		if (output != nullptr) delete output;
	}
	// Feed forward perceptron function
	void forward() {
		(*output) = w * (*input);
	}
	virtual void learn() = 0;

	// Result of NN
	Matrix<double> NN_out() { return *output; }

	// Change pointers for input/output
	void setInput(Matrix<double>* in) { input = in; };
	void setOutput(Matrix<double>* out) { output = out; }
};

namespace test {
	class Layer : abstractLayer{
	public:
		Layer(): abstractLayer() {}
		Layer(Matrix<double>* in, Matrix<double>* out) : abstractLayer(in,out) {}
		~Layer() {}

		void forward() {
			(*output) = w * (*input);
		}

		virtual void learn() override {}
	};
}
