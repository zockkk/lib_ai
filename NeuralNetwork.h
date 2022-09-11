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

class abstractNeuralNetwork {
protected:
	// inputs/outputs(neurons) for each layers
	Matrix<double>* neurons_in = nullptr;
	std::vector<Matrix<double>> neurons__;
	Matrix<double>* neurons_out = nullptr;
	//std::vector<abstractLayer> layers;
	size_t n_layers = 0;
	double l_r = 0.001;
public:
	abstractNeuralNetwork(){}
	abstractNeuralNetwork(std::vector<size_t> n_neurons) {
		n_layers = n_neurons.size() - 1;
		neurons__.resize(n_layers - 1);
	}
	~abstractNeuralNetwork(){}

	virtual void forward() = 0;
	virtual void learn() = 0;

	void set_X(Matrix<double>* x) { if (n_layers != 0) neurons_in = x; };
	void set_Y(Matrix<double>* y) { if (n_layers != 0) neurons_out = y; };
	void set_lr(double rate) { 
		l_r = rate;
	}
};

namespace test {
	// test for abstract layer
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
	protected:
		// Errors input/output and gradients weights/shifts for backpropagation method
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
		perceptronLayer(const perceptronLayer& l) {
			errorX = l.errorX;
			errorY = l.errorY;
			input = l.input;
			output = l.output;
			w = l.w;
			b = l.b;
			n_in = l.n_in;
			n_out = l.n_out;
			lr = l.lr;
		}
		~perceptronLayer() {}

		// setters for errors 
		void setErrX(Matrix<double>* x) { errorX = x; }
		void setErrY(Matrix<double>* y) { errorY = y; }

		void operator = (const perceptronLayer& l) {
			errorX = l.errorX;
			errorY = l.errorY;
			input = l.input;
			output = l.output;
			w = l.w;
			b = l.b;
			gradW = l.gradW;
			gradB = l.gradB;
			n_in = l.n_in;
			n_out = l.n_out;
			lr = l.lr;
		}
		void operator = (perceptronLayer&& l) {
			errorX = l.errorX;
			errorY = l.errorY;
			input = l.input;
			output = l.output;
			w = l.w;
			b = l.b;
			gradW = l.gradW;
			gradB = l.gradB;
			n_in = l.n_in;
			n_out = l.n_out;
			lr = l.lr;
		}

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
			std::cout << "- weights \n";
			w.print();
			std::cout << "- shifts \n";
			b.print();
		}
	};

	class FC_perceptron :abstractNeuralNetwork {
		// errrors input/hidden/output neurons layers
		Matrix<double>* errors_in = nullptr;
		std::vector<Matrix<double>> errors__;
		Matrix<double>* errors_out = nullptr;
		std::vector<perceptronLayer> layers;
	public:
		FC_perceptron():abstractNeuralNetwork() {}
		FC_perceptron(std::vector<size_t> n_neurons) :abstractNeuralNetwork(n_neurons) {
			layers.resize(n_layers);
			errors__.resize(n_layers - 1);
			for (size_t i = 0; i < n_layers-1; i++) {
				neurons__[i] = Matrix<double>(n_neurons[i], 1, 0.0);
				errors__[i] = Matrix<double>(n_neurons[i], 1, 0.0);
				
			}
			for (size_t i = 1; i < n_layers-1; i++) {
				layers[i] = perceptronLayer(&neurons__[i-1], &neurons__[i]);
				layers[i].setErrX(&errors__[i-1]);
				layers[i].setErrY(&errors__[i]);
			}

		}
		FC_perceptron(FC_perceptron& nn) {
			n_layers = nn.n_layers;
			std::swap(neurons_in, nn.neurons_in);
			// initialisation new neurons and errors
			neurons__.resize(nn.n_layers - 1);
			for (size_t i = 0; i < n_layers - 1; i++) {
				neurons__[i] = Matrix<double>(nn.neurons__[i].getRows(), nn.neurons__[i].getCols(), 0.0);
			}
			std::swap(neurons_out, nn.neurons_out);
			std::swap(errors_in, nn.errors_in);
			errors__.resize(n_layers - 1);
			for (size_t i = 0; i < n_layers - 1; i++) {
				errors__[i] = Matrix<double>(nn.neurons__[i].getRows(), nn.neurons__[i].getCols(), 0.0);
			}
			std::swap(errors_out, nn.errors_out);
			layers.resize(n_layers);
			// init layers without input and output layers
			for (size_t i = 1; i < n_layers - 1; i++) {
				layers[i] = perceptronLayer(&neurons__[i - 1], &neurons__[i]);
				layers[i].setErrX(&errors__[i - 1]);
				layers[i].setErrY(&errors__[i]);
			}
			l_r = nn.l_r;
		}
		~FC_perceptron() {}

		void operator = (FC_perceptron& nn) {
			n_layers = nn.n_layers;
			neurons_in = nn.neurons_in;
			neurons__.resize(nn.n_layers - 1);
			for (size_t i = 0; i < n_layers - 1; i++) {
				neurons__[i] = Matrix<double>(nn.neurons__[i].getRows(), nn.neurons__[i].getCols(), 0.0);
			}
			neurons_out = nn.neurons_out;
			errors_in = nn.errors_in;
			errors__.resize(n_layers - 1);
			for (size_t i = 0; i < n_layers - 1; i++) {
				errors__[i] = Matrix<double>(nn.neurons__[i].getRows(), nn.neurons__[i].getCols(), 0.0);
			}
			errors_out = nn.errors_out;
			layers.resize(n_layers);
			for (size_t i = 1; i < n_layers - 1; i++) {
				layers[i] = perceptronLayer(&neurons__[i - 1], &neurons__[i]);
				layers[i].setErrX(&errors__[i - 1]);
				layers[i].setErrY(&errors__[i]);
			}
			l_r = nn.l_r;
		}

		void operator = (FC_perceptron&& nn) {
			n_layers = nn.n_layers;
			std::swap(neurons_in,nn.neurons_in);
			neurons__.resize(nn.n_layers-1);
			for (size_t i = 0; i < n_layers - 1; i++) {
				neurons__[i] = Matrix<double>(nn.neurons__[i].getRows(), nn.neurons__[i].getCols(), 0.0);
			}
			std::swap(neurons_out, nn.neurons_out);
			std::swap(errors_in, nn.errors_in);
			errors__.resize(n_layers - 1);
			for (size_t i = 0; i < n_layers - 1; i++) {
				errors__[i] = Matrix<double>(nn.neurons__[i].getRows(), nn.neurons__[i].getCols(), 0.0);
			}
			std::swap(errors_out, nn.errors_out);
			layers.resize(n_layers);
			for (size_t i = 1; i < n_layers - 1; i++) {
				layers[i] = perceptronLayer(&neurons__[i - 1], &neurons__[i]);
				layers[i].setErrX(&errors__[i - 1]);
				layers[i].setErrY(&errors__[i]);
			}
			l_r = nn.l_r;
		}

		// setter for *inputs/*outputs/*errors of input and output layers
		void set_side_vectors(Matrix<double>* in, Matrix<double>* out, Matrix<double> * err_x,Matrix<double> *err_y) {
			neurons_in = in;
			neurons_out = out;
			errors_in = err_x;
			errors_out = err_y;
			layers[0] = perceptronLayer(neurons_in, &neurons__[0]);
			layers[n_layers - 1] = perceptronLayer(&neurons__[n_layers - 2], neurons_out);
			layers[0].setErrX(errors_in);
			layers[0].setErrY(&errors__[0]);
			layers[n_layers - 1].setErrX(&errors__[n_layers - 2]);
			layers[n_layers - 1].setErrY(errors_out);
		}

		void forward() {
			for (size_t i = 0; i < n_layers; i++) {
				layers[i].forward();
			}
		}

		void backward() {
			if (n_layers >= 0) {
				for (size_t i = n_layers; i > 0; --i) {
					layers[i-1].backward();
				}
			}
		}

		void calcGrad() {
			for (size_t i = 0; i < n_layers; i++) {
				layers[i].gradient();
			}
		}

		void learn() {
			this->backward();
			this->calcGrad();
			for (size_t i = 0; i < n_layers; i++) {
				layers[i].learn();
			}
		}

		friend void Print_NN(FC_perceptron& NN) {
			for (size_t i = 0; i < NN.n_layers; i++) {
				NN.layers[i].print();
				std::cout << "\n -"<<i<<" - Layer\n";
			}
		}
	};
}