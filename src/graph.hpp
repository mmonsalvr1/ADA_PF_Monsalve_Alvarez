#pragma once
#include "parser.hpp"
#include <vector>

struct Edge {
    int u, v;
    double weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

std::vector<Edge> buildGraph(const std::vector<Customer>& customers);