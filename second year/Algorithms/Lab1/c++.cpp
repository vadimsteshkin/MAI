#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = INT_MAX; // Р‘РµСЃРєРѕРЅРµС‡РЅРѕСЃС‚СЊ

// РЎС‚СЂСѓРєС‚СѓСЂР° РґР»СЏ РїСЂРµРґСЃС‚Р°РІР»РµРЅРёСЏ СЂРµР±СЂР° РіСЂР°С„Р°
struct Edge {
    int from, to, weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

// Р¤СѓРЅРєС†РёСЏ РґР»СЏ РїРѕРёСЃРєР° РєСЂР°С‚С‡Р°Р№С€РёС… РїСѓС‚РµР№ РІ РіСЂР°С„Рµ СЃ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµРј Р°Р»РіРѕСЂРёС‚РјР° Р”РµР№РєСЃС‚СЂС‹
vector<int> Dijkstra(vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF); // РњР°СЃСЃРёРІ СЂР°СЃСЃС‚РѕСЏРЅРёР№
    vector<int> prev(n, -1); // РњР°СЃСЃРёРІ РґР»СЏ РїСЂРµРґС€РµСЃС‚РІСѓСЋС‰РёС… РІРµСЂС€РёРЅ
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

// Р¤СѓРЅРєС†РёСЏ РґР»СЏ РїРѕРёСЃРєР° РєСЂР°С‚С‡Р°Р№С€РёС… РїСѓС‚РµР№ РІ РіСЂР°С„Рµ СЃ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµРј Р°Р»РіРѕСЂРёС‚РјР° Р‘РµР»Р»РјР°РЅР°-Р¤РѕСЂРґР°
vector<int> BellmanFord(vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF); // РњР°СЃСЃРёРІ СЂР°СЃСЃС‚РѕСЏРЅРёР№
    vector<int> prev(n, -1); // РњР°СЃСЃРёРІ РґР»СЏ РїСЂРµРґС€РµСЃС‚РІСѓСЋС‰РёС… РІРµСЂС€РёРЅ
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

// Р¤СѓРЅРєС†РёСЏ РґР»СЏ РїРѕРёСЃРєР° РєСЂР°С‚С‡Р°Р№С€РёС… РїСѓС‚РµР№ РІ РіСЂР°С„Рµ СЃ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµРј Р°Р»РіРѕСЂРёС‚РјР° Р¤Р»РѕР№РґР°-РЈРѕСЂС€РµР»Р»Р°
vector<vector<int>> FloydWarshall(vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist(n, vector<int>(n, INF)); // РњР°С‚СЂРёС†Р° СЂР°СЃСЃС‚РѕСЏРЅРёР№
    // Р�РЅРёС†РёР°Р»РёР·Р°С†РёСЏ РјР°С‚СЂРёС†С‹
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (const Edge& edge : graph[i]) {
            dist[edge.from][edge.to] = edge.weight;
        }
    }

    // РђР»РіРѕСЂРёС‚Рј Р¤Р»РѕР№РґР°-РЈРѕСЂС€РµР»Р»Р°
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

// Р¤СѓРЅРєС†РёСЏ РґР»СЏ РїРѕСЃС‚СЂРѕРµРЅРёСЏ РѕСЃС‚РѕРІРЅРѕРіРѕ РґРµСЂРµРІР° РјРёРЅРёРјР°Р»СЊРЅРѕР№ СЃС‚РѕРёРјРѕСЃС‚Рё СЃ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµРј Р°Р»РіРѕСЂРёС‚РјР° РљСЂСѓСЃРєР°Р»Р°
vector<Edge> Kruskal(vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<Edge> result; // Р РµР±СЂР° РѕСЃС‚РѕРІРЅРѕРіРѕ РґРµСЂРµРІР°
    vector<Edge> edges; // Р’СЃРµ СЂРµР±СЂР° РіСЂР°С„Р°

    // Р—Р°РїРѕР»РЅРµРЅРёРµ РјР°СЃСЃРёРІР° СЂРµР±РµСЂ РіСЂР°С„Р°
    for (int i = 0; i < n; i++) {
        for (const Edge& edge : graph[i]) {
            edges.push_back(edge);
        }
    }

    // РЎРѕСЂС‚РёСЂРѕРІРєР° СЂРµР±РµСЂ РїРѕ РІРµСЃСѓ
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    // РњР°СЃСЃРёРІ РґР»СЏ РёРґРµРЅС‚РёС„РёРєР°С†РёРё РєРѕРјРїРѕРЅРµРЅС‚ СЃРІСЏР·РЅРѕСЃС‚Рё
    vector<int> tree_id(n);
    for (int i = 0; i < n; i++) {
        tree_id[i] = i;
    }

    // РџРѕСЃС‚СЂРѕРµРЅРёРµ РѕСЃС‚РѕРІРЅРѕРіРѕ РґРµСЂРµРІР°
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
    int n = 10; // РљРѕР»РёС‡РµСЃС‚РІРѕ РІРµСЂС€РёРЅ
    vector<vector<Edge>> graph(n);

    // Р�РЅРёС†РёР°Р»РёР·Р°С†РёСЏ РіСЂР°С„Р° (Р·РґРµСЃСЊ РЅСѓР¶РЅРѕ Р·Р°РїРѕР»РЅРёС‚СЊ РіСЂР°С„ СЃРІРѕРёРјРё РґР°РЅРЅС‹РјРё)
    // РџСЂРёРјРµСЂ:
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


    // Р’С‹Р·РѕРІ Р°Р»РіРѕСЂРёС‚РјР° Р”РµР№РєСЃС‚СЂС‹
    int start_vertex = 0;
    vector<int> prevDijkstra = Dijkstra(graph, start_vertex);

    // Р’С‹РІРѕРґ РєСЂР°С‚С‡Р°Р№С€РёС… РїСѓС‚РµР№ Рё РїСЂРµРґС€РµСЃС‚РІСѓСЋС‰РёС… РІРµСЂС€РёРЅ
    cout << "РљСЂР°С‚С‡Р°Р№С€РёРµ РїСѓС‚Рё СЃ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµРј Р°Р»РіРѕСЂРёС‚РјР° Р”РµР№РєСЃС‚СЂС‹:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "РљСЂР°С‚С‡Р°Р№С€РёР№ РїСѓС‚СЊ РѕС‚ РІРµСЂС€РёРЅС‹ " << start_vertex << " РґРѕ РІРµСЂС€РёРЅС‹ " << i << ": " << start_vertex << " -> ";
        int current = i;
        while (current != start_vertex) {
            cout << current << " -> ";
            current = prevDijkstra[current];
        }
        cout << i << endl;
    }

    // Р’С‹Р·РѕРІ Р°Р»РіРѕСЂРёС‚РјР° Р‘РµР»Р»РјР°РЅР°-Р¤РѕСЂРґР°
    vector<int> prevBellmanFord = BellmanFord(graph, start_vertex);

    // Р’С‹РІРѕРґ РєСЂР°С‚С‡Р°Р№С€РёС… РїСѓС‚РµР№ Рё РїСЂРµРґС€РµСЃС‚РІСѓСЋС‰РёС… РІРµСЂС€РёРЅ
    cout << "РљСЂР°С‚С‡Р°Р№С€РёРµ РїСѓС‚Рё СЃ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµРј Р°Р»РіРѕСЂРёС‚РјР° Р‘РµР»Р»РјР°РЅР°-Р¤РѕСЂРґР°:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "РљСЂР°С‚С‡Р°Р№С€РёР№ РїСѓС‚СЊ РѕС‚ РІРµСЂС€РёРЅС‹ " << start_vertex << " РґРѕ РІРµСЂС€РёРЅС‹ " << i << ": " << start_vertex << " -> ";
        int current = i;
        while (current != start_vertex) {
            cout << current << " -> ";
            current = prevBellmanFord[current];
        }
        cout << i << endl;
    }

    // Р’С‹Р·РѕРІ Р°Р»РіРѕСЂРёС‚РјР° Р¤Р»РѕР№РґР°-РЈРѕСЂС€РµР»Р»Р°
    vector<vector<int>> distFloydWarshall = FloydWarshall(graph);

    // Р’С‹РІРѕРґ РєСЂР°С‚С‡Р°Р№С€РёС… РїСѓС‚РµР№
    cout << "РљСЂР°С‚С‡Р°Р№С€РёРµ РїСѓС‚Рё СЃ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµРј Р°Р»РіРѕСЂРёС‚РјР° Р¤Р»РѕР№РґР°-РЈРѕСЂС€РµР»Р»Р°:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "РљСЂР°С‚С‡Р°Р№С€РёР№ РїСѓС‚СЊ РѕС‚ РІРµСЂС€РёРЅС‹ " << i << " РґРѕ РІРµСЂС€РёРЅС‹ " << j << ": " << distFloydWarshall[i][j] << endl;
        }
    }

    // Р’С‹Р·РѕРІ Р°Р»РіРѕСЂРёС‚РјР° РљСЂСѓСЃРєР°Р»Р°
    vector<Edge> min_spanning_tree = Kruskal(graph);

    // Р’С‹РІРѕРґ РѕСЃС‚РѕРІРЅРѕРіРѕ РґРµСЂРµРІР°
    cout << "РћСЃС‚РѕРІРЅРѕРµ РґРµСЂРµРІРѕ РјРёРЅРёРјР°Р»СЊРЅРѕР№ СЃС‚РѕРёРјРѕСЃС‚Рё (Р°Р»РіРѕСЂРёС‚Рј РљСЂСѓСЃРєР°Р»Р°):" << endl;
    for (const Edge& edge : min_spanning_tree) {
        cout << "Р РµР±СЂРѕ: " << edge.from << " -- " << edge.to << " (РІРµСЃ: " << edge.weight << ")" << endl;
    }

    return 0;
}

