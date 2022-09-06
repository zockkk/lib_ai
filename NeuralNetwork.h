#pragma once
#include "Matrix.h"


class abstractLayer {
protected:
	// Matrix of inputs/outputs/weights(w)/shifts(b) NN 
	Matrix<double>* input = nullptr;
	Matrix<double>* output = nullptr;
	Matrix<double> w;
	Matrix<double> b;

	// size matrix weights
	size_t n_in = 0;
	size_t n_out = 0;

	//learning rate
	double lr = 0.001;
public:
	abstractLayer() {}
	abstractLayer(Matrix<double>* in, Matrix<double>* out) {
		input = in;
		output = out;
		n_in = input->getRows();
		n_out = output->getRows();
		w = Matrix<double>(output->getRows(), input->getRows(), 0.1);
	}
	~abstractLayer() {
		//if (input != nullptr) delete input;
		//if (output != nullptr) delete output;
	}
	// Feed forward perceptron function
	virtual void forward() = 0;
		
	virtual void learn() = 0;

	// Result of NN
	Matrix<double> NN_out() { return *output; }

	// Change pointers for input/output/learning rate
	void setInput(Matrix<double>* in) { input = in; };
	void setOutput(Matrix<double>* out) { output = out; }
	void setLearningRate(const double new_lr) { lr = new_lr; }
};

namespace test {
	class Layer : abstractLayer{
	public:
		Layer(): abstractLayer() {}
		Layer(Matrix<double>* in, Matrix<double>* out) : abstractLayer(in,out) {}
		~Layer() {}

		virtual void forward() override {
			(*output) = w * (*input);
		}

		virtual void learn() override {}
	};
}

namespace perc {
	//realisation Petceptron NN layer
	class perceptronLayer : abstractLayer {
		// Errors input/output/gradients weights and shifts for backpropagation method
		Matrix<double>* errorX = nullptr;
		Matrix<double>* errorY = nullptr;
		Matrix<double> gradW;
		Matrix<double> gradB;
	public:
		perceptronLayer():abstractLayer() {}
		perceptronLayer(Matrix<double>* in, Matrix<double>* out) : abstractLayer(in, out) {
			input = in;
			output = out;
			n_in = input->getRows();
			n_out = output->getRows();
			w = Matrix<double>(n_out, n_in, 0.1);
			b = Matrix<double>(n_out, 1, 0.0);
			gradW.resize(n_out, n_in);
			gradB.resize(n_out, 1);
		}
		~perceptronLayer() {}

		// setters for errors 
		void setErrX(Matrix<double>* x) { errorX = x; }
		void setErrY(Matrix<double>* y) { errorY = y; }

		virtual void forward() override  {
			(*output) = w * (*input) + b;
		}
		void backward() { (*errorX) = w.t() * (*errorY); }
		void gradient(){
			for (size_t i = 0; i < n_out; i++)
			{
				for (size_t j = 0; j < n_in; j++)
				{
					gradW.set(i, j, errorY->get(i, 0) * input->get(j, 0));
				}
			}

			for (size_t i = 0; i < n_out; i++)
			{
				gradB.set(i, 0, errorY->get(i, 0));
			}
		}
		void learn() {
			this->backward();
			this->gradient();
			w -= lr * gradW;
			b -= lr * gradB;
		}

		void print() {
			w.print();
			std::cout << '\n';
			b.print();
		}
	};
}