// MlpNetwork.h
#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"
#include "Matrix.h"

#define MLP_SIZE 4
#define DIM1  784
#define DIM2  128
#define DIM3  64
#define DIM4  20
#define DIM5  10

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

typedef Matrix  MatrixArray[MLP_SIZE];

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

class MlpNetwork
{
public:
	/**
	 * constructor - creates a MlpNetwork object
	 * @param weights - the weights matrix array
	 * @param biases - the bias matrix array
	 * @throw std::invalid_argument if the weights/biases dimensions
	 * are invalid
	 */
	MlpNetwork ( MatrixArray weights, MatrixArray biases);

	/**
	 * operator() - applies the Mlp network on the input matrix
	 * @param input - the input matrix
	 * @return the identified digit with the associated probability
	 */
	digit operator()(const Matrix& input) const;
private:
	/**
	 * attributes:
	 * _layers - the Dense layers array
	 */
	Dense _layers[MLP_SIZE];
};

#endif // MLPNETWORK_H