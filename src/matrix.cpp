#include "matrix.h"
using namespace std;

Matrix::Matrix(unsigned rowSize, unsigned colSize, double initial) 
{
    this->init(rowSize, colSize, initial);
}

Matrix::Matrix(const Matrix& B)
{
    this->m_colSize = B.getCols();
    this->m_rowSize = B.getRows();
    this->m_matrix = B.m_matrix;

}

Matrix::Matrix()
{
    this->m_colSize = 0;
    this->m_rowSize = 0;
}

void Matrix::init(unsigned rowSize, unsigned colSize, double initial)
{
    this->m_rowSize = rowSize;
    this->m_colSize = colSize;
    
    this->m_matrix = new double* [m_rowSize];
    for (int i = 0; i < m_rowSize; i++)
        this->m_matrix[i] = new double[colSize];

    for (int i = 0; i < m_rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            this->m_matrix[i][j] = 0;
        }
    }
}

void Matrix::changeSign()
{
    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
            this->m_matrix[i][j] = 1 - this->m_matrix[i][j];
    }
}

Matrix::~Matrix() 
{
}

Matrix Matrix::operator + (Matrix& B) 
{
    Matrix sum(m_colSize, m_rowSize, 0.0);
    
    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
            sum(i, j) = this->m_matrix[i][j] + B(i, j);
    }

    return sum;
}

Matrix Matrix::operator-(Matrix B) 
{
    Matrix diff(m_colSize, m_rowSize, 0.0);

    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
            diff(i, j) = this->m_matrix[i][j] - B(i, j);
    }

    return diff;
}

Matrix Matrix::operator * (Matrix B) 
{
    Matrix multip = Matrix(m_rowSize, m_colSize, 0.0);

    if (m_colSize == B.getCols() && m_rowSize == B.getRows())
    {
        for (unsigned i = 0; i < m_rowSize; i++)
        {
            for (unsigned j = 0; j < m_colSize; j++)
            {
                multip(i, j) = m_matrix[i][j] * B(i, j);
            }
        }
        return multip;
    }
    else
    {
        throw std::runtime_error("Error size matrix");
    }
}

Matrix Matrix::dot(Matrix B)
{
    Matrix multip(this->m_rowSize, B.getCols(), 0.0);

    if (this->m_colSize == B.getRows())
    {
        for (unsigned i = 0; i < this->m_rowSize; i++)
        {
            for (unsigned j = 0; j < B.getCols(); j++)
            {
                double temp = 0.0;

                for (unsigned k = 0; k < this->m_colSize; k++)
                    temp += m_matrix[i][k] * B(k, j);

                multip(i, j) = temp;
            }
        }
        return multip;
    }
    else
    {
        throw std::runtime_error("Error size matrix");
    }
}

double* Matrix::dot(double* vector, int vector_size)
{
    double* multip = new double[vector_size];

    if (this->m_colSize == vector_size)
    {
        for (unsigned i = 0; i < this->m_rowSize; i++)
        {
            double temp = 0.0;

            for (unsigned k = 0; k < this->m_colSize; k++)
                temp += m_matrix[i][k] * vector[k];

            multip[i] = temp;
        }
        return multip;
    }
    else
    {
        throw std::runtime_error("Error size matrix");
    }
}

void Matrix::dotTranspose(double* vector, int vector_size, double* finish)
{
    if (this->m_rowSize == vector_size)
    {
        for (unsigned i = 0; i < this->m_colSize; i++)
        {
            double temp = 0.0;

            for (unsigned k = 0; k < this->m_rowSize; k++)
                temp += m_matrix[k][i] * vector[k];

            finish[i] = temp;
        }
    }
    else
    {
        throw std::runtime_error("Error size matrix");
    }
}

Matrix::Matrix(double* vector, int size)
{
    this->m_rowSize = size;
    this->m_colSize = 1;
    this->init(this->m_rowSize, this->m_colSize, 0.0);

    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
            this->m_matrix[i][j] = vector[i];
    }
}

Matrix Matrix::operator + (double scalar) 
{
    Matrix result(m_rowSize, m_colSize, 0.0);

    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
        {
            result(i, j) = this->m_matrix[i][j] + scalar;
        }
    }

    return result;
}

void Matrix::sumVector(double* vector)
{
    for (int idx = 0; idx < this->getRows(); idx++)
    {
        this->m_matrix[idx][0] += vector[idx];
    }
}

Matrix Matrix::operator - (double scalar) 
{
    Matrix result(m_rowSize, m_colSize, 0.0);

    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
        {
            result(i, j) = this->m_matrix[i][j] - scalar;
        }
    }

    return result;
}

Matrix Matrix::operator * (double scalar) 
{
    Matrix result(m_rowSize, m_colSize, 0.0);

    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
            result(i, j) = this->m_matrix[i][j] * scalar;
    }

    return result;
}

Matrix Matrix::operator / (double scalar) 
{
    Matrix result(m_rowSize, m_colSize, 0.0);
    
    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
            result(i, j) = this->m_matrix[i][j] / scalar;
    }

    return result;
}


double& Matrix::operator()(const unsigned& rowNo, const unsigned& colNo)
{
    return this->m_matrix[rowNo][colNo];
}

unsigned Matrix::getRows() const
{
    return this->m_rowSize;
}

unsigned Matrix::getCols() const
{
    return this->m_colSize;
}

Matrix Matrix::transpose()
{
    Matrix Transpose(m_colSize, m_rowSize, 0.0);

    for (unsigned i = 0; i < m_colSize; i++)
    {
        for (unsigned j = 0; j < m_rowSize; j++) {
            Transpose(i, j) = this->m_matrix[j][i];
        }
    }

    return Transpose;
}

void Matrix::print() const
{
    for (unsigned i = 0; i < m_rowSize; i++) 
    {
        for (unsigned j = 0; j < m_colSize; j++) 
            cout << m_matrix[i][j] << " ";
        
        cout << endl;
    }
}

void Matrix::randomValue(const unsigned multipiler)
{
    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
            m_matrix[i][j] = -3 + (double)rand() / RAND_MAX * 6;
    }
}

std::ostream& operator << (std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); j++) {
            os << m.m_matrix[i][j] << " ";
        }
    }
    return os;
}

std::istream& operator >> (std::istream& is, Matrix& m) {
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); j++) {
            is >> m.m_matrix[i][j];
        }
    }
    return is;
}