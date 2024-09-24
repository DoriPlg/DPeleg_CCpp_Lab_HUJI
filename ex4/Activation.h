// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include <cmath>
#include <stdexcept>

namespace activation
{
    /*
    * Applies the ReLU activation function on the given matrix.
    * The input matrix must be a vector.
    * @return a new matrix with the same dimensions as the input matrix.
    */
    Matrix relu(const Matrix &m);

    /*
    * Applies the softmax activation function on the given matrix.
    * The input matrix must be a vector.
    * @return a new matrix with the same dimensions as the input matrix.
    */
    Matrix softmax(const Matrix &m);
}


#endif //ACTIVATION_H