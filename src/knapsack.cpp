#include "knapsack.hpp"
#include <algorithm>

void knapsackDP(const std::vector<Item>& items, int W, int& optimalValue, std::vector<std::string>& selectedIds) {
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    optimalValue = dp[n][W];

    int res = optimalValue;
    int w = W;
    for (int i = n; i > 0 && res > 0; i--) {
        if (res != dp[i - 1][w]) {
            selectedIds.push_back(items[i - 1].id);
            res -= items[i - 1].value;
            w -= items[i - 1].weight;
        }
    }
}