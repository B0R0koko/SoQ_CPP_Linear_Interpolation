#include <vector>
#include <iostream>
#include <algorithm>
#include "LinearInterpolation.hpp"


struct Point
{
    double x;
    double y;
    int idx;
};


bool checkGreater(const Point &point_1, const Point &point_2) {
    return point_1.x < point_2.x;
}

void sortPoints(std::vector<double> &x, std::vector<double> &y) {
    std::vector<Point> points(x.size());

    // Create Points from vectors
    for (int i = 0; i < x.size(); ++i) {
        points[i].x = x[i];
        points[i].y = y[i];
        points[i].idx = i;
    }

    std::sort(points.begin(), points.end(), checkGreater);

    for (int i = 0; i < x.size(); ++i) {
        x[i] = points[i].x;
        y[i] = points[i].y;
    }
}

void LinearInterpolation::setPoints(std::vector<double> x, std::vector<double> y) {
    sortPoints(x, y);
    x_vals = x;
    y_vals = y;
}


// Implement a function that calculates linear interpolation for x
double LinearInterpolation::GetValue(double x) {
    auto min_x = std::min_element(x_vals.begin(), x_vals.end());
    auto max_x = std::max_element(x_vals.begin(), x_vals.end());

    if (x < *min_x | x > *max_x) {
        std::cout << "Value of x' is outside of the domain" << std::endl;
        return -9999;
    }

    double x_lb, x_ub, y_lb, y_ub;

    // If not return -9999, then compute approx derivative
    for (int i=0; i < x_vals.size(); i++) {
        // since x_vals are sorted, therefore find the first instance when x >= x_vals[i],
        // therefore the next value will be the biggest closest ub
        if (x <= x_vals[i]) {
            x_lb = x_vals[i];
            x_ub = (i == x_vals.size()) ? x_vals[i] : x_vals[i+1];
            y_lb = y_vals[i];
            y_ub = (i == x_vals.size()) ? y_vals[i] : y_vals[i+1];
            break;
        }
    }

    double y_inter;
    y_inter = y_lb * (x - x_ub) / (x_lb - x_ub) + y_ub * (x - x_lb) / (x_ub - x_lb);

    return y_inter;
}