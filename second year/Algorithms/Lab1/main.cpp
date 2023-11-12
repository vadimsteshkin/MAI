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

/* Алгоритм Дейкстры для поиска кратчайшего пути от одной вершины ко всем осталным.
 * В каждой итерации выбирается вершина с наименьшим расстоянием, а затем обновляются
 * расстояния до её соседей. Это повторяется до тех пор, пока все вершины не будут посещены.
 * @param graph Матрица смежности графа.
 * @param start Начальная вершина.
 */
void dijkstra(const std::vector<std::vector<int>>& graph, int start) {

    int n = graph.size();
    std::vector<int> distance(n, INF);   // Массив для хранения расстояний от начальной вершины
    std::vector<bool> visited(n, false); // Массив для отслеживания посещенных вершин

    distance[start] = 0;

    // Основной цикл алгоритма Дейкстры
    for (int i = 0; i < n - 1; ++i) {
        int minDist = INF, minIndex = -1;

        // Находим вершину с минимальным расстоянием
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && distance[j] < minDist) {
                minDist = distance[j];
                minIndex = j;
            }
        }

        visited[minIndex] = true;

        // Обновляем расстояния до смежных вершин
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

/**
 * Алгоритм Беллмана-Форда находит кратчайшие пути от заданной начальной вершины ко всем остальным.
 * Он релаксирует рёбра в графе V-1 раз, где V - количество вершин. Затем проверяется наличие
 * циклов отрицательного веса.
 * @param graph Матрица смежности графа.
 * @param start Начальная вершина.
 */
void bellmanFord(const std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    std::vector<int> distance(n, INF); // Массив для хранения расстояний от начальной вершины
    distance[start] = 0;

    // Основной цикл алгоритма Беллмана-Форда
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                // Релаксация ребра (обновление расстояния)
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

/**
 * Алгоритм Флойда-Уоршелла находит кратчайшие пути между всеми парами вершин в графе.
 * Используется тройной вложенный цикл для обновления расстояний между всеми парами вершин.
 * @param graph Матрица смежности графа.
 */
void floydWarshall(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<std::vector<int>> distance(graph);

    // Основной цикл алгоритма Флойда-Уоршелла
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

/**
 * Алгоритм Крускала строит остовное дерево минимальной стоимости, добавляя рёбра в порядке
 *возрастания их весов и не создавая циклов. Для этого используется система непересекающихся
 * множеств (Union-Find).
 * @param graph Матрица смежности графа.
 */
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

/**
 * Алгоритм Прима строит остовное дерево минимальной стоимости, добавляя к текущему дереву
 * вершину с минимальным весом ребра, соединяющего текущее дерево с ещё не включенными вершинами.
 * @param graph Матрица смежности графа.
 */
void prim(const std::vector<std::vector<int>>& graph) {
    int V = graph.size();
    std::vector<int> parent(V, -1);    // Инициализация массива предков
    std::vector<int> key(V, INF);       // Веса вершин
    std::vector<bool> inMST(V, false);  // Включена ли вершина в остовное дерево

    key[0] = 0; // Начинаем с вершины 0

    // Основной цикл алгоритма Прима
    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        // Обновляем ключи для смежных вершин
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
    {INF, 3, INF, INF, 7, INF, INF, INF, INF, INF},
    {3, INF, 2, INF, INF, INF, INF, INF, INF, INF},
    {INF, 2, INF, 5, INF, INF, INF, INF, INF, INF},
    {INF, INF, 5, INF, INF, 4, INF, INF, INF, INF},
    {7, INF, INF, INF, INF, INF, 1, INF, INF, INF},
    {INF, INF, INF, 4, INF, INF, 6, 2, INF, INF},
    {INF, INF, INF, INF, 1, 6, INF, INF, INF, INF},
    {INF, INF, INF, INF, INF, 2, INF, INF, 3, INF},
    {INF, INF, INF, INF, INF, INF, INF, 3, INF, 4},
    {INF, INF, INF, INF, INF, INF, INF, INF, 4, INF}
    };
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