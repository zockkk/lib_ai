#pragma once
#include "Matrix.h"
#include "NeuralNetwork.h"

class abstractModel {
public:
	Matrix<double>* input = nullptr;
	Matrix<double>* output = nullptr;
	abstractModel() {}
	abstractModel(Matrix<double>* in, Matrix<double>* out) { input = in; output = out; }

	void operator = (abstractModel& a) {
		for (size_t i = 0; i < input->getRows(); i++) {
			(*input)[i][0] = (*a.input)[i][0];
		}
		for (size_t i = 0; i < output->getRows(); i++) {
			(*output)[i][0] = (*a.output)[i][0];
		}
	}
	void operator = (abstractModel &&a) {
		std::swap(input,a.input);
		std::swap(output,a.output);
	}

	void setIn(Matrix<double>* in) { input = in; }
	void setOut(Matrix<double>* out) { output = out; }
	void setInOut(Matrix<double>* in, Matrix<double>* out) { input = in; output = out; }
	//Matrix<double>* getOut() { return output; } !!!Need fix

	virtual ~abstractModel() {}

	virtual void work() = 0;

};

namespace test {
	//realisation model classes test

	class Model : public abstractModel {
	public:
		Matrix<double>* input = nullptr;
		Matrix<double>* output = nullptr;
		Model() : abstractModel() {}
		Model(Matrix<double>* in, Matrix<double>* out) : abstractModel( in, out)
		{ 
			input = in;
			output = out; 
		}

		virtual ~Model() override {
			//if (input != nullptr) delete input;
			//if (output != nullptr) delete output; !!!Need fix
		}

		virtual void work() override {
			(*output) = (*input)*0.01;
		}
	};

	//text abstract model class ++
	void testModel_001() {

		std::cout << "start test\n";
		Matrix<double> inModel(5, 5, 0.1);
		Matrix<double> in({ 1, 2, 3, 4, 5 });
		//in.print();
		Matrix<double> out({ 3,5,7,3,4 });
		Matrix<double> forwardOut(5, 1);
		//forwardOut.print();
		Model testModel(&in, &out);
		testModel.work();
		out.print();
	}


	class ModelPerc :abstractModel {
	private:
		Layer lnn;
	public:
		ModelPerc() : abstractModel() {}
		ModelPerc(Matrix<double>* in, Matrix<double>* out) : abstractModel(in, out) {
			lnn = Layer(in, out);
		}
		virtual ~ModelPerc() override {}

		virtual void work() override {
			lnn.forward();
		}

	};

	// test abstract model feed forward ++
	void testModel_002() {

		std::cout << "start test\n";
		Matrix<double> inModel(5, 5, 0.1);
		Matrix<double> in({ 1, 2, 3, 4, 5 });
		//in.print();
		Matrix<double> out({ 3,5,7,3,4 });
		Matrix<double> forwardOut(5, 1);
		//forwardOut.print();
		Model testModel(&in, &out);
		testModel.work();
		out.print();
	}
}

// Perceptron model realisation
namespace perc {
	class Model : abstractModel{
		// perceptron layer
		perceptronLayer nnl;
		// errors inputs and outputs
		Matrix<double>* errX = nullptr;
		Matrix<double>* errY = nullptr;
	public:
		Model(): abstractModel() {}
		Model(Matrix<double>* in, Matrix<double>* out) : abstractModel(in, out) {
			nnl = perceptronLayer(in, out);
		}

		virtual void work() override {
			nnl.forward();
		}
		void learn() { nnl.learn(); }

		void set_errors(Matrix<double>* x, Matrix<double>* y) {
			errX = x;
			errY = y;
			nnl.setErrX(errX);
			nnl.setErrY(errY);
		}
		void print() {
			nnl.print();
		}
	};

	class NN_Model :abstractModel {
	private:
		// perceptron neural network init
		FC_perceptron NN;

		// errors inputs and outputs
		Matrix<double>* errX = nullptr;
		Matrix<double>* errY = nullptr;

		// initialisation NN side vectors check
		bool check = false;
	public:
		NN_Model(): abstractModel(){}
		NN_Model(Matrix<double>* in, Matrix<double>* out, std::vector<size_t> n_neurons) :abstractModel(in, out) {
			NN = FC_perceptron(n_neurons);
		}

		~NN_Model(){}

		void setter(Matrix<double>* x,Matrix<double> *y) { 
			errX = x;
			errY = y;
			NN.set_side_vectors(input, output, errX, errY);
			check = true;
		}

		virtual void work() override {
			if (check) {
				NN.forward();
			}
			else {
				std::cout << "set side vectors please!!!";
				std::cin.get();
				exit(-1);
			}
		}
		void learn_NN() {
			if (check) {
				NN.learn();
			}
			else {
				std::cout << "set side vectors please!!!";
				std::cin.get();
				exit(-1);
			}
		}

		friend void Print_Model(NN_Model& NNM) {
			Print_NN(NNM.NN);
		}
	};
}