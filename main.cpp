#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "LinearInterpolation.hpp"


using namespace std;


pair<vector<double>, vector<double>> GetData(const string& filePath) {
    // return a tuple of vectors
    vector<double> xpoints, ypoints;

    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error opening the file" << endl;
        return make_pair(vector<double>(), vector<double>());
    }

    string line;
    // Skip the header line
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        string x_str, y_str;
        
        if (getline(iss, x_str, ',')) {
            if (getline(iss, y_str, ',')) {
                
                double x_val = stod(x_str);
                double y_val = stod(y_str);
                
                xpoints.push_back(x_val);
                ypoints.push_back(y_val);
            }
        }
    }

    return make_pair(xpoints, ypoints);
}

void print(vector<double> vec) {
    for (const auto& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {

    const string filePath = "data.csv";
    auto data = GetData(filePath);

    // Instantiate Interpolation class and feed in vectors of doubles
    LinearInterpolation interpolator;
    interpolator.setPoints(data.first, data.second);

    cout << interpolator.GetValue(7.004) << endl;

    return 0;
}