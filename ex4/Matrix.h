// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <stdexcept>

#define PRINT_THRESHOLD 0.1


struct matrix_dims {
     int rows, cols;
};

using std::ostream;
using std::istream;

class Matrix
{
private:
    /*
    * _dims - a struct holding the dimensions of the matrix
    * _data - a 2D array holding the matrix data
    */
    matrix_dims _dims;
    float * _data;
    // float **_data;

    /*
    * rref_divide_row - divide a row by a scalar
    * @param row - the row to divide
    * @param divisor - the scalar to divide by 
    * @throw std::invalid_argument if divisor is 0
    * @throw std::out_of_range if row is out of range
    */
    void rref_divide_row( int row, float divisor);
    /*
    * rref_subtract_row-subtract a row multiplied by a scalar from another row
    * @param row - the row to subtract
    * @param target_row - the row to subtract from
    * @param factor - the scalar to multiply the row by
    * @throw std::out_of_range if row or target_row are out of range
    * @throw std::invalid_argument if factor is 0
    */
    void rref_subtract_row( int row,  int target_row,\
                                                        float factor);
    /*
    * rref_swap_rows - swap two rows in the matrix
    * @param row1 - the first row to swap
    * @param row2 - the second row to swap
    * @throw std::out_of_range if row1 or row2 are out of range
    */
    void rref_swap_rows( int row1,  int row2);    
public:
    /*
    * Matrix - constructor for the Matrix class
    * initializes the data of the matrix to 0.
    * if provided with rows and cols
    * initializes the matrix to the given dimensions
    * if provided with a matrix, initializes the matrix
    * to the same dimensions and data as the given matrix
    * else: initializes the matrix to 1x1
    * @param rows - the number of rows in the matrix
    * @param cols - the number of columns in the matrix
    * @param m - the matrix to copy
    * @throw std::invalid_argument if rows or cols are non-positive
    */
    Matrix( int rows,  int cols);
    Matrix(): Matrix(1,1) {}
    Matrix(const Matrix &m);
    /* destructor for Matrix */
    ~Matrix();

    // methods
    /*
    * getters for the matrix dimensions
    */
     int get_rows() const { return _dims.rows; }
     int get_cols() const { return _dims.cols; }

    /*
    * transpose - transpose the matrix
    * @return a new matrix that is the transpose of the original matrix
    */
    Matrix& transpose();

    /*
    * vectorize - return a matrix strung as a vector
    * @return a new matrix of dimensions (row*col,1)
    *  that is the vectorized version of the original matrix
    */
    Matrix& vectorize();

    /*
    * plain_print - print the matrix in a plain format, 
    * showing the data in each row separated by spaces
    */
    void plain_print() const;

    /*
    * dot - element-wise multiplication of two matrices
    * @param m - the matrix to multiply with
    * @return a new matrix that is the element-wise 
    * multiplication of the two matrices
    * @throw std::invalid_argument if the matrices do not have
    * the same dimensions
    */
    Matrix dot(const Matrix &m) const;

    /*
    * norm - calculate the Frobenius norm of the matrix
    * @return the Frobenius norm of the matrix
    */
    float norm() const;

    /*
    * rref - calculate the reduced row echelon form of the matrix
    * @return a new matrix that is the reduced row echelon form
    * of the original matrix
    */
    Matrix rref() const;

    /*
    * argmax - return the index of the maximum value in the matrix
    * @return the index of the maximum value in the matrix, 
    * return the first index in case of a tie
    */
    int argmax() const;

    /*
    * sum - calculate the sum of all the elements in the matrix
    * @return the sum of all the elements in the matrix
    */
    float sum() const;

    // operators
    /*
    * operator* - matrix multiplication as learned in linear algebra
    * @param m - the matrix to multiply with
    * @return a new matrix that is the result of the matrix multiplication
    * @throw std::invalid_argument if the matrices do not 
    * have the correct dimensions
    */
    Matrix operator*(const Matrix &m)const;

    /*
    * operator* - scalar multiplication
    */
    Matrix operator*(const float &c)const;

    /*
    * operator* - scalar multiplication
    */
    friend Matrix operator*(const float &c, const Matrix &m){ return m * c; }

    /*
    * operator+ - matrix addition
    */
    Matrix operator+(const Matrix &m)const;

    /*
    * operator+= - matrix addition, modifies the matrix
    */
    Matrix& operator+=(const Matrix &m) 
    {
        (*this) = (*this) + m;
        return *this;
    }

    /*
    * operator= - assignment operator
    */
    Matrix& operator=(const Matrix &m);

    /*
    * operator() - access the matrix elements for reading and writing
    * @param row - the row of the element
    * @param col - the column of the element
    * @throw std::out_of_range if row or col are out of range
    * @return a reference to the element
    */
    float& operator()(int row, int col);

    /*
    * operator() - access the matrix elements for reading
    * @param row - the row of the element
    * @param col - the column of the element
    * @throw std::out_of_range if row or col are out of range
    * @return the element by value
    */
    float operator()(int row, int col) const
        { return _data[row*_dims.cols + col]; }

    /*
    * operator[] - access the matrix elements for reading and writing
    * @param i - the index of the element, row*cols + col
    * @throw std::out_of_range if i is out of range
    * @return a reference to the element
    */
    float& operator[](int i);

    /*
    * operator[] - access the matrix elements for reading
    * @param i - the index of the element, row*cols + col
    * @throw std::out_of_range if i is out of range
    * @return the element by value
    */
    float operator[](int i) const { return _data[i]; }

    /*
    * operator<< - print the matrix to an output stream
    * @param os - the output stream to print to
    * @param m - the matrix to print
    * @return the output stream
    */
    friend ostream& operator<<(ostream &os, const Matrix &m);

    /*
    * operator>> - read the matrix from an input stream
    * @param is - the input stream to read from
    * @param m - the matrix to read into
    * @return the input stream
    */
    friend istream& operator>>(istream &os, Matrix &m);
};

#endif //MATRIX_H