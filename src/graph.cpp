#include "graph.hpp"
#include <cmath>

std::vector<Edge> buildGraph(const std::vector<Customer>& customers) {
    std::vector<double> sumMonthly(20, 0.0);
    std::vector<int> countNode(20, 0);

    for (size_t i = 0; i < customers.size(); ++i) {
        int group = i % 20;
        sumMonthly[group] += customers[i].monthlyCharges;
        countNode[group]++;
    }

    std::vector<double> avgMonthly(20, 0.0);
    for (int i = 0; i < 20; i++) {
        if (countNode[i] > 0) {
            avgMonthly[i] = std::round((sumMonthly[i] / countNode[i]) * 100.0) / 100.0;
        }
    }

    std::vector<Edge> edges;
    for (int u = 0; u < 20; u++) {
        for (int v = u + 1; v < 20; v++) {
            double cost = std::floor(avgMonthly[u] + avgMonthly[v]);
            edges.push_back({u, v, cost});
        }
    }
    return edges;
}