#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <stack>

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

int main() {
    int n = 10; // Количество вершин
    vector<vector<Edge>> graph(n);

    // Инициализация графа (здесь нужно заполнить граф своими данными)
    // Пример:
    graph[0].emplace_back(0, 9, 5);
    graph[0].emplace_back(0, 2, 3);
    graph[0].emplace_back(0, 7, 4);
    graph[0].emplace_back(0, 5, 5);
    graph[1].emplace_back(1, 3, 2);
    graph[2].emplace_back(2, 4, 4);
    graph[3].emplace_back(3, 4, 1);
    graph[3].emplace_back(3, 7, 1);
    graph[4].emplace_back(4, 8, 5);
    graph[4].emplace_back(4, 7, 3);
    graph[4].emplace_back(4, 0, 2);
    graph[4].emplace_back(4, 1, 3);
    graph[4].emplace_back(4, 6, 3);
    graph[5].emplace_back(5, 3, 2);
    graph[5].emplace_back(5, 7, 4);
    graph[5].emplace_back(5, 6, 4);
    graph[5].emplace_back(5, 4, 1);
    graph[6].emplace_back(6, 3, 4);
    graph[6].emplace_back(6, 8, 1);
    graph[7].emplace_back(7, 5, 5);
    graph[7].emplace_back(7, 0, 2);
    graph[7].emplace_back(7, 8, 5);
    graph[8].emplace_back(8, 2, 3);
    graph[8].emplace_back(8, 3, 2);
    graph[8].emplace_back(8, 9, 2);
    graph[9].emplace_back(9, 6, 1);
    graph[9].emplace_back(9, 4, 1);

    // Вызов алгоритма Дейкстры
    int start_vertex = 3;
    vector<int> prevDijkstra = Dijkstra(graph, start_vertex);

    // Вывод кратчайших путей и предшествующих вершин
    cout << "Кратчайшие пути с использованием алгоритма Дейкстры:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Кратчайший путь от вершины " << start_vertex << " до вершины " << i << ": ";
        int current = i;
        stack<int> path;
        while (current != -1) {
            path.push(current);
            current = prevDijkstra[current];
        }
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    return 0;
}
