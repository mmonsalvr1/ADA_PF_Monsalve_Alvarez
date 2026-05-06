#pragma once
#include <string>
#include <vector>

struct Item {
    std::string id;
    int weight;
    int value;
};

void knapsackDP(const std::vector<Item>& items, int W, int& optimalValue, std::vector<std::string>& selectedIds);