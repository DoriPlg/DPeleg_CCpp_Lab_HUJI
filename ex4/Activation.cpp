#include "Activation.h"

// see Activation.h for documentation

Matrix activation::relu(const Matrix &m)
{
    Matrix result(m);
    for (int i = 0; i < m.get_rows()*m.get_cols(); i++)
    {
        result[i] = (std::abs(m[i])+m[i])/2;
    }
    return result;
}

Matrix activation::softmax(const Matrix &m)
{
    Matrix new_vec(m);
    float sum = 0;
    for (int i = 0; i < m.get_rows()* m.get_cols(); i++)
    {
        new_vec[i] = std::exp(m[i]);
        sum += std::exp(m[i]);
    }
    return new_vec * (1 / sum);
}

