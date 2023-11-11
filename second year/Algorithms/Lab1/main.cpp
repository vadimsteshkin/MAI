#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

// Функция для отображения матрицы смежности
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int weight : row) {
            if (weight == INF) {
                std::cout << "INF\t";
            } else {
                std::cout << weight << "\t";
            }
        }
        std::cout << std::endl;
    }
}

// Функция для сравнения ребер по весу
bool compareEdges(const std::pair<int, std::pair<int, int>>& a, const std::pair<int, std::pair<int, int>>& b) {
    return a.first < b.first;
}

// Функция для поиска подмножества вершины i
int find(std::vector<int>& parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Функция объединения двух подмножеств в одно подмножество
void unionSets(std::vector<int>& parent, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    parent[xroot] = yroot;
}

// Алгоритм Дейкстры для поиска кратчайшего пути
void dijkstra(const std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    std::vector<int> distance(n, INF);
    std::vector<bool> visited(n, false);

    distance[start] = 0;

    for (int i = 0; i < n - 1; ++i) {
        int minDist = INF, minIndex = -1;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && distance[j] < minDist) {
                minDist = distance[j];
                minIndex = j;
            }
        }

        visited[minIndex] = true;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && graph[minIndex][j] != INF &&
                distance[minIndex] != INF &&
                distance[minIndex] + graph[minIndex][j] < distance[j]) {
                distance[j] = distance[minIndex] + graph[minIndex][j];
            }
        }
    }

    // Вывод результатов
    std::cout << "Кратчайший путь Дейкстры от вершины " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "Вершина " << i << ": Расстояние = " << distance[i] << std::endl;
    }
}

// Алгоритм Беллмана-Форда для поиска кратчайшего пути
void bellmanFord(const std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    std::vector<int> distance(n, INF);
    distance[start] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] != INF && distance[u] != INF &&
                    distance[u] + graph[u][v] < distance[v]) {
                    distance[v] = distance[u] + graph[u][v];
                }
            }
        }
    }

    // Проверка наличия циклов отрицательного веса
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != INF && distance[u] != INF &&
                distance[u] + graph[u][v] < distance[v]) {
                std::cerr << "График содержит цикл с отрицательным весом." << std::endl;
                return;
            }
        }
    }

    // Вывод результатов
    std::cout << "Минимальное связующее дерево(Беллман-Форд) " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "Вершина " << i << ": Расстояние = " << distance[i] << std::endl;
    }
}

// Алгоритм Флойда-Уоршелла для поиска кратчайших путей
void floydWarshall(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<std::vector<int>> distance(graph);

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (distance[i][k] != INF && distance[k][j] != INF &&
                    distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    // Вывод результатов
    std::cout << "Минимальное связующее дерево(алгоритм Флойда-Уоршелла):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << "Из веришы " << i << " в вершину " << j << ": Расстояние = ";
            if (distance[i][j] == INF) {
                std::cout << "INF\t"<<'\n';
            } else {
                std::cout << distance[i][j] << "\t"<<'\n';
            }
        }
        std::cout << std::endl;
    }
}

// Алгоритм Крускала для построения остовного дерева минимальной стоимости
void kruskal(const std::vector<std::vector<int>>& graph) {
    int V = graph.size();
    std::vector<int> parent(V, -1); // Инициализация массива предков

    std::vector<std::pair<int, std::pair<int, int>>> edges;

    // Заполняем вектор ребер из матрицы смежности
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (graph[i][j] != INF) {
                edges.push_back({graph[i][j], {i, j}});
            }
        }
    }

    // Сортируем ребра по весу
    std::sort(edges.begin(), edges.end(), compareEdges);

    std::cout << "Минимальное связующее дерево (Алгоритм Крускала):\n";
    for (const auto& edge : edges) {
        int x = find(parent, edge.second.first);
        int y = find(parent, edge.second.second);

        // Если включение данного ребра не создаст цикл, включаем его
        if (x != y) {
            std::cout << "Ребро " << edge.second.first << " - " << edge.second.second
                      << " : " << edge.first << std::endl;
            unionSets(parent, x, y);
        }
    }
}

// Алгоритм Прима для построения остовного дерева минимальной стоимости
void prim(const std::vector<std::vector<int>>& graph) {
    int V = graph.size();
    std::vector<int> parent(V, -1); // Инициализация массива предков
    std::vector<int> key(V, INF);    // Веса вершин
    std::vector<bool> inMST(V, false); // Включена ли вершина в остовное дерево

    key[0] = 0; // Начинаем с вершины 0

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != INF && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Вывод результатов
    std::cout << "Минимальное дерево(Алгоритм Прима)):\n";
    for (int i = 1; i < V; ++i) {
        std::cout << "Ребро " << parent[i] << " - " << i << " : " << graph[i][parent[i]] << std::endl;
    }
}

int main() {
    const int V = 5; // Количество вершин
    setlocale(LC_ALL, "RUSSIAN");
    // Пример матрицы смежности (INF - отсутствие ребра)
    std::vector<std::vector<int>> graph = {
        {INF, 2, INF, 1, INF},
        {2, INF, 4, 3, INF},
        {INF, 4, INF, INF, 5},
        {1, 3, INF, INF, 7},
        {INF, INF, 5, 7, INF}
    };

    // Вывод матрицы смежности
    std::cout << "Матрица смежности:\n";
    printMatrix(graph);

    // Применение алгоритмов поиска кратчайшего пути
    dijkstra(graph, 0);
    bellmanFord(graph, 0);
    floydWarshall(graph);

    // Применение алгоритмов построения остовного дерева
    kruskal(graph);
    prim(graph);

    return 0;
}