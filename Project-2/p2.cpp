#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define edge pair<int, int>

class Graph {
   private:
    vector<pair<int, edge> > G;  // graph
    vector<pair<int, edge> > T;  // mst
    int *parent;
    int V;  // number of vertices/nodes in graph
   public:
    Graph(int V) {
        parent = new int[V];

        for (int i = 0; i < V; i++) parent[i] = i;

        G.clear();
        T.clear();
    }
    void add_edge(int u, int v, int w) {
        G.push_back(make_pair(w, edge(u, v)));
    }
    int find_set(int i) {
        // If i is the parent of itself
        if (i == parent[i])
            return i;
        else
            // Else if i is not the parent of itself
            // Then i is not the representative of his set,
            // so we recursively call Find on its parent
            return find_set(parent[i]);
    }
    void union_set(int u, int v) { parent[u] = parent[v]; }
    void kruskal() {
        int uRep, vRep;
        sort(G.begin(), G.end());
        for (size_t i = 0; i < G.size(); i++) {
            uRep = find_set(G[i].second.first);
            vRep = find_set(G[i].second.second);
            if (uRep != vRep) {
                T.push_back(G[i]);  // add to tree
                union_set(uRep, vRep);
            }
        }
    }
    void print() {
        for (size_t i = 0; i < T.size(); i++) {
            cout << T[i].second.first << " - " << T[i].second.second << endl;
        }
    }
};

int main() {
    // Kruskal's algorithm
    int v, e;
    scanf("%d", &v);
    scanf("%d", &e);

    Graph g(v);

    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        g.add_edge(u, v, w);
    }
    g.kruskal();
    g.print();

    return 0;
}