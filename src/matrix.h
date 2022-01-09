#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

using std::vector;
using std::tuple;

class Matrix 
{

private:
    unsigned m_rowSize;
    unsigned m_colSize;
    vector<vector<double> > m_matrix;

public:
    Matrix(unsigned, unsigned, double);
    Matrix(const Matrix&);
    Matrix(double* vector, int size);
    Matrix();
    ~Matrix();

    void init(unsigned, unsigned, double);
    Matrix operator+(Matrix&);
    Matrix operator-(Matrix&);
    Matrix operator*(Matrix&);
    Matrix transpose();

    Matrix operator+(double);
    Matrix operator-(double);
    Matrix operator*(double);
    Matrix operator/(double);

    double& operator()(const unsigned&, const unsigned&);
    void print() const;
    unsigned getRows() const;
    unsigned getCols() const;
    void sumVector(double* vector);
    void randomValue(const unsigned multipiler = 1.0);
};