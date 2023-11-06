#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = INT_MAX; // Бесконечность

// Структура для представления ребра графа
struct Edge {
    int from, to, weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

// Функция для поиска кратчайших путей в графе с использованием алгоритма Дейкстры
vector<int> Dijkstra(vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF); // Массив расстояний
    vector<int> prev(n, -1); // Массив для предшествующих вершин
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (const Edge& edge : graph[i]) {
            if (dist[edge.from] < INF && dist[edge.to] > dist[edge.from] + edge.weight) {
                dist[edge.to] = dist[edge.from] + edge.weight;
                prev[edge.to] = edge.from;
            }
        }
    }

    return prev;
}

// Функция для поиска кратчайших путей в графе с использованием алгоритма Беллмана-Форда
vector<int> BellmanFord(vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF); // Массив расстояний
    vector<int> prev(n, -1); // Массив для предшествующих вершин
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (const Edge& edge : graph[u]) {
                if (dist[u] < INF && dist[edge.to] > dist[u] + edge.weight) {
                    dist[edge.to] = dist[u] + edge.weight;
                    prev[edge.to] = u;
                }
            }
        }
    }

    return prev;
}

// Функция для поиска кратчайших путей в графе с использованием алгоритма Флойда-Уоршелла
vector<vector<int>> FloydWarshall(vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist(n, vector<int>(n, INF)); // Матрица расстояний
    // Инициализация матрицы
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (const Edge& edge : graph[i]) {
            dist[edge.from][edge.to] = edge.weight;
        }
    }

    // Алгоритм Флойда-Уоршелла
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    return dist;
}

// Функция для построения остовного дерева минимальной стоимости с использованием алгоритма Крускала
vector<Edge> Kruskal(vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<Edge> result; // Ребра остовного дерева
    vector<Edge> edges; // Все ребра графа

    // Заполнение массива ребер графа
    for (int i = 0; i < n; i++) {
        for (const Edge& edge : graph[i]) {
            edges.push_back(edge);
        }
    }

    // Сортировка ребер по весу
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    // Массив для идентификации компонент связности
    vector<int> tree_id(n);
    for (int i = 0; i < n; i++) {
        tree_id[i] = i;
    }

    // Построение остовного дерева
    for (const Edge& edge : edges) {
        if (tree_id[edge.from] != tree_id[edge.to]) {
            result.push_back(edge);
            int old_id = tree_id[edge.from], new_id = tree_id[edge.to];
            for (int i = 0; i < n; i++) {
                if (tree_id[i] == old_id) {
                    tree_id[i] = new_id;
                }
            }
        }
    }

    return result;
}

int main() {
    int n = 10; // Количество вершин
    vector<vector<Edge>> graph(n);

    // Инициализация графа (здесь нужно заполнить граф своими данными)
    // Пример:
    graph[0].emplace_back(0, 1, 5);
    graph[0].emplace_back(1, 2, 3);
    graph[0].emplace_back(1, 3, 5);
    graph[0].emplace_back(2, 3, 3);
    graph[0].emplace_back(3, 4, 5);
    graph[0].emplace_back(5, 2, 5);
    graph[0].emplace_back(5, 3, 3);
    graph[0].emplace_back(3, 5, 5);
    graph[0].emplace_back(4, 2, 3);
    graph[0].emplace_back(0, 6, 5);


    // Вызов алгоритма Дейкстры
    int start_vertex = 0;
    vector<int> prevDijkstra = Dijkstra(graph, start_vertex);

    // Вывод кратчайших путей и предшествующих вершин
    cout << "Кратчайшие пути с использованием алгоритма Дейкстры:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Кратчайший путь от вершины " << start_vertex << " до вершины " << i << ": " << start_vertex << " -> ";
        int current = i;
        while (current != start_vertex) {
            cout << current << " -> ";
            current = prevDijkstra[current];
        }
        cout << i << endl;
    }

    // Вызов алгоритма Беллмана-Форда
    vector<int> prevBellmanFord = BellmanFord(graph, start_vertex);

    // Вывод кратчайших путей и предшествующих вершин
    cout << "Кратчайшие пути с использованием алгоритма Беллмана-Форда:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Кратчайший путь от вершины " << start_vertex << " до вершины " << i << ": " << start_vertex << " -> ";
        int current = i;
        while (current != start_vertex) {
            cout << current << " -> ";
            current = prevBellmanFord[current];
        }
        cout << i << endl;
    }

    // Вызов алгоритма Флойда-Уоршелла
    vector<vector<int>> distFloydWarshall = FloydWarshall(graph);

    // Вывод кратчайших путей
    cout << "Кратчайшие пути с использованием алгоритма Флойда-Уоршелла:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Кратчайший путь от вершины " << i << " до вершины " << j << ": " << distFloydWarshall[i][j] << endl;
        }
    }

    // Вызов алгоритма Крускала
    vector<Edge> min_spanning_tree = Kruskal(graph);

    // Вывод остовного дерева
    cout << "Остовное дерево минимальной стоимости (алгоритм Крускала):" << endl;
    for (const Edge& edge : min_spanning_tree) {
        cout << "Ребро: " << edge.from << " -- " << edge.to << " (вес: " << edge.weight << ")" << endl;
    }

    return 0;
}

