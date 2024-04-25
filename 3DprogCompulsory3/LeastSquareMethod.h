#ifndef LSM_H
#define LSM_H

#include <vector>
#include <string>

class LeastSquareMethod {
private:
    std::vector<double> coefficients;

public:
    // Constructor
    LeastSquareMethod(const std::vector<double>& xy, int degree);

    // A function designed to calculate the coefficients of a polynomial by using the least squares method
    std::vector<double> leastSquaresMethod(const std::vector<double>& xy, int degree);

    // A function designed to genereate a string representation of the polynomial equation
    std::string polynomialString();

    // A function designed to print coefficients
    void printCoefficients();

    std::vector<double> getCoefficients();
};

#endif
