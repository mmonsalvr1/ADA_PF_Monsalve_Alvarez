#pragma once
#include "graph.hpp"
#include <vector>

std::vector<Edge> kruskalMST(std::vector<Edge>& edges, int V, double& totalWeight);