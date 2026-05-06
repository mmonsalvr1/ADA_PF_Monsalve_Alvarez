#include "kruskal.hpp"
#include <numeric>
#include <algorithm>

struct UnionFind {
    std::vector<int> parent, rank;
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        std::iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) parent[root_i] = root_j;
            else if (rank[root_i] > rank[root_j]) parent[root_j] = root_i;
            else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

std::vector<Edge> kruskalMST(std::vector<Edge>& edges, int V, double& totalWeight) {
    std::sort(edges.begin(), edges.end());
    UnionFind uf(V);
    std::vector<Edge> mst;
    totalWeight = 0.0;
    
    for (const auto& edge : edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v);
            mst.push_back(edge);
            totalWeight += edge.weight;
            if (mst.size() == V - 1) break;
        }
    }
    return mst;
}