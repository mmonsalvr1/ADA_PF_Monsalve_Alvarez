#include "parser.hpp"
#include "mergesort.hpp"
#include "binary_search.hpp"
#include "graph.hpp"
#include "kruskal.hpp"
#include "knapsack.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./ada_pf data/WA_Fn-UseC_-Telco-Customer-Churn.csv\n";
        return 1;
    }

    std::string filename = argv[1];
    int nullCount = 0;

    auto customers = parseCSV(filename, nullCount);
    std::cout << "Registros cargados: " << customers.size() << "\n";
    std::cout << "Registros con TotalCharges nulo: " << nullCount << "\n";

    auto startA = std::chrono::high_resolution_clock::now();
    mergeSort(customers, 0, customers.size() - 1);
    auto endA = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> timeA = endA - startA;
    
    std::ofstream outOrd("results/solicitudes_ordenadas.csv");
    outOrd << "customerID,tenure,MonthlyCharges,TotalCharges,Churn\n";
    for(const auto& c : customers) {
        outOrd << c.id << "," << c.tenure << "," << c.monthlyCharges << "," << c.totalCharges << "," << c.churn << "\n";
    }
    outOrd.close();

    int queries[] = {72, 60, 45, 30, 12};
    std::ofstream outQA("results/busquedas_A.txt");
    for (int q : queries) {
        int idx = binarySearch(customers, 0, customers.size() - 1, q);
        if (idx != -1) {
            outQA << "Q_A: " << q << " -> customerID: " << customers[idx].id << " (tenure: " << customers[idx].tenure << ")\n";
        } else {
            outQA << "Q_A: " << q << " -> No encontrado\n";
        }
    }
    outQA << "Tiempo MergeSort: " << timeA.count() << " ms\n";
    outQA.close();

    auto edges = buildGraph(customers);
    double mstWeight = 0.0;
    auto mst = kruskalMST(edges, 20, mstWeight);

    std::ofstream outMST("results/mst_red.txt");
    outMST << "Peso total del MST: " << mstWeight << "\nAristas incluidas:\n";
    for (const auto& e : mst) {
        outMST << "(" << e.u << ", " << e.v << ") -> " << e.weight << "\n";
    }
    outMST.close();

    std::vector<Item> items;
    for (const auto& c : customers) {
        if (c.churn.find("No") != std::string::npos) {
            items.push_back({
                c.id, 
                static_cast<int>(std::round(c.totalCharges)), 
                static_cast<int>(std::round(c.monthlyCharges * 10))
            });
            if (items.size() == 50) break;
        }
    }

    int optimalValue = 0;
    std::vector<std::string> selectedIds;
    knapsackDP(items, 500, optimalValue, selectedIds);

    std::ofstream outBW("results/asignacion_bw.txt");
    outBW << "Valor optimo total: " << optimalValue << " centavos\n";
    outBW << "Numero de solicitudes seleccionadas: " << selectedIds.size() << "\nIDs seleccionados:\n";
    for (const auto& id : selectedIds) {
        outBW << id << "\n";
    }
    outBW.close();
}