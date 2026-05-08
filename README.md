# ADA_PF_Monsalve_Alvarez

Compilación y ejecución:

Descripción
-----------
Proyecto de la práctica final que implementa tres módulos sobre el dataset "Telco Customer Churn":
- Módulo A: ordenación por MergeSort y búsqueda binaria sobre `tenure`.
- Módulo B: construcción de grafo por agrupamiento y cálculo del MST mediante Kruskal (Union-Find).
- Módulo C: problema 0–1 Knapsack (programación dinámica) y recuperación de selección por backtracking.

Requisitos
----------
- macOS / Linux con `g++` (soporta C++17).
- Python 3 (solo para scripts auxiliares opcionales).

Compilación
-----------
```bash

g++ -std=c++17 -O2 -o ada_pf src/*.cpp
```

Ejecución
---------
```bash

./ada_pf data/WA_Fn-UseC_-Telco-Customer-Churn.csv
```
El programa procesa el dataset y genera los ficheros de salida en el directorio `results/`.

Archivos de salida (ubicados en `results/`)
---------------------------------------
- `solicitudes_ordenadas.csv`: registros ordenados por `tenure` (descendente) usados para búsquedas y otras pruebas.
- `busquedas_A.txt`: resultados de las consultas Q_A realizadas sobre la copia ordenada (incluye algunos `customerID` de ejemplo) y los tiempos medidos de MergeSort para n = 1000, 3500 y 7043.
- `mst_red.txt`: lista de aristas del MST calculado por Kruskal y peso total del MST.
- `asignacion_bw.txt`: resultado del algoritmo de mochila (valor óptimo y lista de IDs seleccionados) y el contraejemplo pedagógico guardado para demostración.

Notas y detalles importantes
---------------------------
- Parser: cuando `TotalCharges` viene vacío, el parser asigna `TotalCharges = 0.0` (se detectaron 11 casos en este dataset).
- Búsqueda: la búsqueda binaria implementada compara igualdad con `tenure == k` (especificación corregida).
- Knapsack: la capacidad `W` y la interpretación de pesos/valores están documentadas en `src/main.cpp`. En las ejecuciones por defecto se observó que el óptimo real es 0 debido a la escala de `TotalCharges` relativa a `W`.

Regenerar resultados
--------------------
1. Compila con la instrucción de compilación arriba.
2. Ejecuta el binario con la ruta al CSV como argumento.
3. Los archivos en `results/` se sobrescribirán con la salida de la ejecución.

Comandos útiles (ejemplo)
------------------------
```bash

g++ -std=c++17 -O2 -o ada_pf src/*.cpp && ./ada_pf data/WA_Fn-UseC_-Telco-Customer-Churn.csv

```

Estructura del repositorio
--------------------------
- `src/` : código fuente C++ (implementaciones de MergeSort, binary search, graph, kruskal, knapsack, parser y `main.cpp`).
- `data/` : `WA_Fn-UseC_-Telco-Customer-Churn.csv` (dataset de entrada).
- `results/` : salidas generadas por el programa.
- `report/` : borrador del informe en PDF.

Resolución de problemas
-----------------------
- Si la compilación falla por falta de memoria o límites, reduce optimizaciones o compila sin `-O2` para depurar.
- Si el programa no encuentra el CSV, use la ruta absoluta o compruebe la ubicación relativa desde la raíz del repo.


