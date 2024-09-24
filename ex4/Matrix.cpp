#include "Matrix.h"

// see Matrix.h for documentation

Matrix::Matrix(int rows, int cols) : _dims((matrix_dims){rows, cols})
{
    if (rows <= 0 || cols <= 0)
    {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
    _data = new float[rows*cols];
    for(int i = 0; i<rows*cols; i++)
    {
        _data[i] = 0;
    }
}

Matrix::Matrix(const Matrix &m)
{
    _dims = (matrix_dims){m.get_rows(), m.get_cols()};
    _data = new float [_dims.rows*_dims.cols];
    for (int i = 0; i < _dims.rows*_dims.cols; i++)
    {
        _data[i] = m[i];
    }
}

Matrix::~Matrix()
{
    delete[] _data;
}

Matrix& Matrix::transpose()
{
    Matrix temp_cpy(*this);
    _dims = (matrix_dims){_dims.cols, _dims.rows};
    for (int i = 0; i < _dims.rows; i++)
    {
        for (int j = 0; j < _dims.cols; j++)
        {
            (*this)(i, j) = temp_cpy(j, i);
        }
    }
    return *this;
}

Matrix& Matrix::vectorize()
{
    _dims = (matrix_dims){_dims.cols*_dims.rows,1};
    return *this;
}

using std::cout;
using std::endl;
void Matrix::plain_print() const
{
    for (int i = 0; i < _dims.rows; i++)
    {
        for (int j = 0; j < _dims.cols; j++)
        {
            cout << (*this)(i,j) << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::dot(const Matrix &m) const
{
    if (_dims.cols != m.get_cols() || _dims.rows != m.get_rows())
    {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(*this);
    for (int i = 0; i < _dims.rows * _dims.cols; i++)
    {
        result[i] *= m[i];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &m) const
{
    if (_dims.cols != m.get_rows())
    {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(_dims.rows, m.get_cols());
    for (int i = 0; i < _dims.rows; i++)
    {
        for (int j = 0; j < m.get_cols(); j++)
        {
            for (int k = 0; k < _dims.cols; k++)
            {
                result(i, j) += (*this)(i, k) * m(k, j);
            }
        }
    }
    return result;
}

float Matrix::norm() const
{
    Matrix squared((*this).dot(*this));
    return std::sqrt(squared.sum());
}

void Matrix::rref_divide_row(int row, float divisor)
{
    if (divisor == 0)
    {
        throw std::invalid_argument("Divisor cannot be 0");
    }
    if (row >= _dims.rows)
    {
        throw std::out_of_range("Row out of range");
    }
    if (row < 0)
    {
        throw std::out_of_range("Row must be non-negative");
    }
    for (int i = 0; i < _dims.cols; i++)
    {
        (*this)(row, i) /= divisor;
    }
}

void Matrix::rref_subtract_row(int row,
                               int target_row, float multiplicator)
{
    if (row >= _dims.rows || target_row >= _dims.rows)
    {
        throw std::out_of_range("Row out of range");
    }
    if (row < 0 || target_row < 0)
    {
        throw std::out_of_range("Row must be non-negative");
    }
    for (int i = 0; i < _dims.cols; i++)
    {
        (*this)(target_row, i) -= (*this)(row, i) * multiplicator;
    }
}

void Matrix::rref_swap_rows(int row1, int row2)
{
    if (row1 >= _dims.rows || row2 >= _dims.rows)
    {
        throw std::out_of_range("Row out of range");
    }
    if (row1 < 0 || row2 < 0)
    {
        throw std::out_of_range("Row must be non-negative");
    }
    float temp;
    for (int i = 0; i<_dims.cols;i++)
    {
        temp = (*this)(row1,i);
        (*this)(row1,i)=(*this)(row2,i);
        (*this)(row2,i)=temp;
    }
}

Matrix Matrix::rref() const
{
    Matrix rref(*this);
    int lead = 0;
    for (int r = 0; r < rref.get_rows(); r++)
    {
        if (lead >= rref._dims.cols)
        {
            break;
        }
        int i = r;
        while (rref(i, lead) == 0)
        {
            i++;
            if (i == rref.get_rows())
            {
                i = r;
                lead++;
                if (lead == rref.get_cols())
                {
                    break;
                }
            }
        }
        if (lead == rref.get_cols())
        {
            break;
        }
        rref.rref_swap_rows(i, r);
        if(rref(r,lead) !=  0)
        {
            rref.rref_divide_row(r, rref(r, lead));
        }
        for (int j = 0; j < rref.get_rows(); j++)
        {
            if (j != r)
            {
                rref.rref_subtract_row(r, j, rref(j, lead));
            }
        }
        lead++;
    }
    return rref;
}

int Matrix::argmax() const
{
    int max_index = 0;
    for (int i = 0; i < _dims.rows * _dims.cols; i++)
    {
        if ((*this)[i] > (*this)[max_index])
        {
            max_index = i;
        }
    }
    return max_index;
}

float Matrix::sum() const
{
    float sum = 0;
    for (int i = 0; i < (_dims.rows * _dims.cols); i++)
    {
        sum += _data[i];
    }
    return sum;
}

Matrix Matrix::operator+(const Matrix &m) const
{
    if (_dims.rows != m.get_rows() || _dims.cols != m.get_cols())
    {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(_dims.rows, _dims.cols);
    for (int i = 0; i < _dims.rows*_dims.cols; i++)
    {
        result[i] = (*this)[i] + m[i];
    }
    return result;
}


Matrix& Matrix::operator=(const Matrix &m) 
{
    if(this == &m)
    {
        return *this;
    }
    delete[] _data;
    _dims.cols = m.get_cols();
    _dims.rows = m.get_rows();
    _data = new float [m.get_cols()*m.get_rows()];
    for(int i = 0; i<m.get_cols()*m.get_rows();i++)
    {
        _data[i] = m[i];
    }
    
    return *this;
}

Matrix Matrix::operator*(const float &c) const
{
    Matrix result(_dims.rows, _dims.cols);
    for (int i = 0; i < _dims.rows*_dims.cols; i++)
    {
        result[i] = _data[i] * c;
    }
    return result;
}

ostream &operator<<(ostream &os, const Matrix &m)
{
    for (int i = 0; i < m.get_rows(); i++)
    {
        for (int j = 0; j < m.get_cols(); j++)
        {
            if (m(i, j) >= PRINT_THRESHOLD)
            {
                os << "**";
            }
            else
            {
                os << "  ";
            }
        }
        os << "\n";
    }
    return os;
}

istream &operator>>(istream &is, Matrix &m)
{
    for ( int i =0; i< m.get_cols()*m.get_rows();i++)
    {
        if (is.eof())
        {
            throw std::length_error("too short a stream for this  matrix");
        }
        is.read((char*)&(m[i]), sizeof(m[i]));
    }
    return is;
}

float &Matrix::operator()(int row, int col)
{
    if (row >= _dims.rows || col >= _dims.cols || row < 0 || col < 0)
    {
        throw std::out_of_range("Row or column out of range.");
    }
    return _data[row*_dims.cols+col];
}

float &Matrix::operator[](int i)
{
    if (i >= _dims.rows * _dims.cols || i < 0)
    {
        throw std::out_of_range("Index out of range.");
    }
    return _data[i];
}