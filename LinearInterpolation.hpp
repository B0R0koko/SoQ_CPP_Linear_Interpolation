#ifndef LINEARINTERPOLATION_H
#define LINEARINTERPOLATION_H

#include <vector>


class LinearInterpolation {
public:
    std::vector<double> x_vals;
    std::vector<double> y_vals;

    LinearInterpolation() {} 
    ~LinearInterpolation() {}

    void setPoints(std::vector<double> x, std::vector<double> y);
    double GetValue(double x);
};

#endif