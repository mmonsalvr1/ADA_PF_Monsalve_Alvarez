#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

std::vector<Customer> parseCSV(const std::string& filename, int& nullTotalChargesCount) {
    std::vector<Customer> customers;
    std::ifstream file(filename);
    std::string line;
    nullTotalChargesCount = 0;

    if (!file.is_open()) {
        std::cerr << "Error abriendo el archivo: " << filename << "\n";
        return customers;
    }

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> cols;

        while (std::getline(ss, token, ',')) {
            cols.push_back(token);
        }

        if (cols.size() >= 21) {
            Customer c;
            c.id = cols[0];
            c.tenure = std::stoi(cols[5]);
            c.monthlyCharges = std::stod(cols[18]);
            c.churn = cols[20];

            std::string tc = cols[19];
            tc.erase(std::remove_if(tc.begin(), tc.end(), ::isspace), tc.end());
            if (tc.empty()) {
                c.totalCharges = 0.0;
                nullTotalChargesCount++;
            } else {
                c.totalCharges = std::stod(tc);
            }

            customers.push_back(c);
        }
    }
    file.close();
    return customers;
}