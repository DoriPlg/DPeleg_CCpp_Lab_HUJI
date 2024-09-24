#include "MlpNetwork.h"

// See MlpNetwork.h for documentation

MlpNetwork::MlpNetwork(MatrixArray weights, MatrixArray biases):
		_layers{Dense(weights[0], biases[0], activation::relu),
				 Dense(weights[1], biases[1], activation::relu),
				 Dense(weights[2], biases[2], activation::relu),
				 Dense(weights[3], biases[3], activation::softmax)}
{
	// Check if the weights/biases dimensions are valid
	if (weights[0].get_cols() != DIM1||
		weights[0].get_rows() != DIM2||
		weights[1].get_cols() != DIM2||
		weights[1].get_rows() != DIM3||
		weights[2].get_cols() != DIM3||
		weights[2].get_rows() != DIM4||
		weights[3].get_cols() != DIM4||
		weights[3].get_rows() != DIM5||
		biases[0].get_cols() != 1||
		biases[0].get_rows() != DIM2||
		biases[1].get_cols() != 1||
		biases[1].get_rows() != DIM3||
		biases[2].get_cols() != 1||
		biases[2].get_rows() != DIM4||
		biases[3].get_cols() != 1||
		biases[3].get_rows() != DIM5)
	{
		throw std::invalid_argument("Invalid weights/biases dimensions");
	}
}

digit MlpNetwork::operator()(const Matrix& input) const
{
	Matrix result(input);
	for (int i = 0; i < MLP_SIZE; i++)
	{
		result = _layers[i](result);
	}
	digit d = (digit){0, result[0]};
	d.value = result.argmax();
		d.probability = result[d.value];
	return d;
}
