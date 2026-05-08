#include "parser.hpp"
#include "mergesort.hpp"
#include "binary_search.hpp"
#include "graph.hpp"
#include "kruskal.hpp"
#include "knapsack.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

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

    auto customers_copy_for_full = customers;
    std::vector<Customer> shuffledCustomers = customers;
    std::mt19937 rng(42);
    std::shuffle(shuffledCustomers.begin(), shuffledCustomers.end(), rng);

    int n1 = std::min(1000, static_cast<int>(shuffledCustomers.size()));
    int n2 = std::min(3500, static_cast<int>(shuffledCustomers.size()));
    std::vector<Customer> sample1(shuffledCustomers.begin(), shuffledCustomers.begin() + n1);
    std::vector<Customer> sample2(shuffledCustomers.begin(), shuffledCustomers.begin() + n2);

    std::chrono::duration<double, std::milli> timeA_full{0};
    std::chrono::duration<double, std::milli> time_s1{0};
    std::chrono::duration<double, std::milli> time_s2{0};

    if (!customers_copy_for_full.empty()) {
        auto startA_full = std::chrono::high_resolution_clock::now();
        mergeSort(customers_copy_for_full, 0, static_cast<int>(customers_copy_for_full.size()) - 1);
        auto endA_full = std::chrono::high_resolution_clock::now();
        timeA_full = endA_full - startA_full;
    }

    if (!sample1.empty()) {
        auto start_s1 = std::chrono::high_resolution_clock::now();
        mergeSort(sample1, 0, static_cast<int>(sample1.size()) - 1);
        auto end_s1 = std::chrono::high_resolution_clock::now();
        time_s1 = end_s1 - start_s1;
    }

    if (!sample2.empty()) {
        auto start_s2 = std::chrono::high_resolution_clock::now();
        mergeSort(sample2, 0, static_cast<int>(sample2.size()) - 1);
        auto end_s2 = std::chrono::high_resolution_clock::now();
        time_s2 = end_s2 - start_s2;
    }

    std::ofstream outOrd("results/solicitudes_ordenadas.csv");
    outOrd << "customerID,tenure,MonthlyCharges,TotalCharges,Churn\n";
    for (const auto& c : customers_copy_for_full) {
        outOrd << c.id << "," << c.tenure << "," << c.monthlyCharges << "," << c.totalCharges << "," << c.churn << "\n";
    }
    outOrd.close();

    int queries[] = {72, 60, 45, 30, 12};
    std::ofstream outQA("results/busquedas_A.txt");
    for (int q : queries) {
        int idx = customers_copy_for_full.empty() ? -1 : binarySearch(customers_copy_for_full, 0, static_cast<int>(customers_copy_for_full.size()) - 1, q);
        if (idx != -1) {
            outQA << "Q_A: " << q << " -> customerID: " << customers_copy_for_full[idx].id << " (tenure: " << customers_copy_for_full[idx].tenure << ")\n";
        } else {
            outQA << "Q_A: " << q << " -> No encontrado\n";
        }
    }
    outQA << "Tiempo MergeSort (n=1000, muestra barajada): " << std::fixed << std::setprecision(5) << time_s1.count() << " ms\n";
    outQA << "Tiempo MergeSort (n=3500, muestra barajada): " << std::fixed << std::setprecision(5) << time_s2.count() << " ms\n";
    outQA << "Tiempo MergeSort (n=" << customers_copy_for_full.size() << ", conjunto completo): " << std::fixed << std::setprecision(5) << timeA_full.count() << " ms\n";
    outQA.close();

    auto edges = buildGraph(customers_copy_for_full);
    double mstWeight = 0.0;
    auto mst = kruskalMST(edges, 20, mstWeight);

    std::ofstream outMST("results/mst_red.txt");
    outMST << "Peso total del MST: " << mstWeight << "\nAristas incluidas:\n";
    for (const auto& e : mst) {
        outMST << "(" << e.u << ", " << e.v << ") -> " << e.weight << "\n";
    }
    outMST.close();

    std::vector<Item> items;
    for (const auto& c : customers_copy_for_full) {
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
    if (!items.empty()) {
        knapsackDP(items, 500, optimalValue, selectedIds);
    }

    std::ofstream outBW("results/asignacion_bw.txt");
    outBW << "Valor optimo total: " << optimalValue << " centavos\n";
    outBW << "Numero de solicitudes seleccionadas: " << selectedIds.size() << "\nIDs seleccionados:\n";
    for (const auto& id : selectedIds) {
        outBW << id << "\n";
    }

    if (items.size() >= 3) {
        std::string idA = items[0].id;
        std::string idB = items[1].id;
        std::string idC = items[2].id;

        outBW << "\nContraejemplo didactico al enfoque codicioso por ratio:\n";
        outBW << "Se usan tres IDs reales como etiquetas, pero los pesos y valores son construidos solo para ilustrar el fallo.\n";
        outBW << "Solicitudes: " << idA << ", " << idB << ", " << idC << "\n";
        outBW << "Ejemplo numerico construido:\n";
        outBW << "- " << idA << ": peso=6, valor=30 (ratio=5.0)\n";
        outBW << "- " << idB << ": peso=5, valor=24 (ratio=4.8)\n";
        outBW << "- " << idC << ": peso=5, valor=20 (ratio=4.0)\n";
        outBW << "Capacidad W_demo = 10\n";
        outBW << "Codicioso (por ratio) selecciona: {" << idA << "} -> valor total = 30 (no cabe otra)\n";
        outBW << "Programacion Dinamica (optimo) selecciona: {" << idB << ", " << idC << "} -> valor total = 44\n";
        outBW << "Conclusion: el enfoque codicioso por ratio no produce la solucion optima en este caso construido.\n";
    }

    outBW.close();
}