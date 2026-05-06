#pragma once
#include <string>
#include <vector>

struct Customer {
    std::string id;
    int tenure;
    double monthlyCharges;
    double totalCharges;
    std::string churn;
};

std::vector<Customer> parseCSV(const std::string& filename, int& nullTotalChargesCount);