// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#include "Matrix.h"
#include <stdexcept>

typedef Matrix (*func_MtM)(const Matrix&);
class Dense
{
public:
    /*
    * constructor - creates a Dense object
    * @param weight - the weights matrix
    * @param bias - the bias matrix
    * @param ActivationFunction - the activation function to be used
    * @throw std::invalid_argument if the weights/biases dimensions
    * are invalid
    */
    Dense(Matrix weight,Matrix bias,\
                    Matrix (*ActivationFunction)(const Matrix&) ):
    _weight(weight),_bias(bias),_ActivationFunction(ActivationFunction)
    {
        if (weight.get_rows() != bias.get_rows())
        {
            throw std::invalid_argument("Invalid weights/biases dimensions");
        }
    }
    
    /*
    * getters:
    * get_weight - returns the weights matrix
    * get_bias - returns the bias matrix
    * get_activation - returns the activation function
    */
    Matrix get_weights() const { return _weight; }
    Matrix get_bias() const { return _bias; }
    func_MtM get_activation() const { return _ActivationFunction; }

    /*
    * operator() - applies the Dense layer on the input matrix
    * @param input - the input matrix
    * @return a vector with the same amountg of rows as 
    * the weights and bias matrices
    */
    Matrix operator()(const Matrix& input) const
    {
        return _ActivationFunction((_weight*input)+_bias);
    }
private:
    /*
    * attributes:
    * _weight - the weights matrix
    * _bias - the bias matrix
    * _ActivationFunction - the activation function to be used
    */
    Matrix _weight;
    Matrix _bias;
    func_MtM _ActivationFunction;
};








#endif //DENSE_H