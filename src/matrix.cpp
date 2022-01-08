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
    m_rowSize = rowSize;
    m_colSize = colSize;
    m_matrix.resize(rowSize);

    for (unsigned i = 0; i < m_matrix.size(); i++)
        m_matrix[i].resize(colSize, initial);
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

Matrix Matrix::operator - (Matrix& B) 
{
    Matrix diff(m_colSize, m_rowSize, 0.0);

    for (unsigned i = 0; i < m_rowSize; i++)
    {
        for (unsigned j = 0; j < m_colSize; j++)
            diff(i, j) = this->m_matrix[i][j] - B(i, j);
    }

    return diff;
}

Matrix Matrix::operator * (Matrix& B) 
{
    Matrix multip(m_rowSize, B.getCols(), 0.0);

    if (m_colSize == B.getRows())
    {
        for (unsigned i = 0; i < m_rowSize; i++)
        {
            for (unsigned j = 0; j < B.getCols(); j++)
            {
                double temp = 0.0;

                for (unsigned k = 0; k < m_colSize; k++)
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
            m_matrix[i][j] = rand() / (RAND_MAX + 1.) * multipiler;
    }
}