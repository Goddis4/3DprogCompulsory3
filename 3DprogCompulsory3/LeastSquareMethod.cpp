#include "LeastSquareMethod.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

// Constructor
LeastSquareMethod::LeastSquareMethod(const std::vector<double>& xy, int degree) {
    coefficients = leastSquaresMethod(xy, degree);
}

// A function designed to calculate the coefficients of a polynomial by using the least squares method
std::vector<double> LeastSquareMethod::leastSquaresMethod(const std::vector<double>& xy, int degree) 
{
    int n = xy.size() / 2;

    std::vector<double> coefficients(degree + 1, 0.0);
    std::vector<double> xSum(2 * degree + 1, 0.0);
    std::vector<double> ySum(degree + 1, 0.0);

    // Gets the x and y coordinates from vector
    std::vector<double> x, y;
    for (int i = 0; i < n; ++i) 
    {
        x.push_back(xy[2 * i]);
        y.push_back(xy[2 * i + 1]);
    }

    // Calculation of the sums of powers of x
    for (int i = 0; i < 2 * degree + 1; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            xSum[i] += pow(x[j], i);
        }
    }

    // Calculation of the sums of powers of x*y
    for (int i = 0; i < degree + 1; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            ySum[i] += pow(x[j], i) * y[j];
        }
    }

    // Creation of the normal equations matrix
    std::vector<std::vector<double>> A(degree + 1, std::vector<double>(degree + 1, 0.0));
    for (int i = 0; i < degree + 1; ++i) 
    {
        for (int j = 0; j < degree + 1; ++j) 
        {
            A[i][j] = xSum[i + j];
        }
    }

    // Solving the equations
    for (int i = 0; i < degree + 1; ++i) 
    {
        for (int j = i + 1; j < degree + 1; ++j) 
        {
            double ratio = A[j][i] / A[i][i];
            for (int k = 0; k < degree + 1; ++k) 
            {
                A[j][k] -= ratio * A[i][k];
            }
            ySum[j] -= ratio * ySum[i];
        }
    }

    // Back substitution
    coefficients[degree] = ySum[degree] / A[degree][degree];
    for (int i = degree - 1; i >= 0; --i) 
    {
        double sum = 0.0;
        for (int j = i + 1; j < degree + 1; ++j) 
        {
            sum += A[i][j] * coefficients[j];
        }
        coefficients[i] = (ySum[i] - sum) / A[i][i];
    }

    return coefficients;
}

// A function designed to genereate a string representation of the polynomial equation
std::string LeastSquareMethod::polynomialString() 
{
    std::stringstream stringStream;
    int degree = coefficients.size() - 1;

    for (int i = degree; i >= 0; --i) 
    {
        if (coefficients[i] != 0.0) 
        {
            if (i < degree) 
            {
                stringStream << " + ";
            }
            stringStream << std::fixed << std::setprecision(2) << coefficients[i];
            if (i > 0) 
            {
                stringStream << "x";
                if (i > 1) 
                {
                    stringStream << "^" << i;
                }
            }
        }
    }

    return stringStream.str();
}

// A function designed to print coefficients
void LeastSquareMethod::printCoefficients() 
{
    std::cout << "Coefficients: ";
    for (double coefficient : coefficients) 
    {
        std::cout << coefficient << " ";
    }
    std::cout << std::endl;
}

std::vector<double> LeastSquareMethod::getCoefficients()
{
    return coefficients;
}