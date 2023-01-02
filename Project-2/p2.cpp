#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Sets {
   private:
    int *parent, *rank;
    int n;

   public:
    Sets(int n) {
        this->n = n;
        parent = new int[n + 1];
        rank = new int[n + 1];

        for (int i = 0; i <= n; i++) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (rank[x] > rank[y])
            parent[y] = x;
        else
            parent[x] = y;
        if (rank[x] == rank[y]) rank[y]++;
    }
};

class Graph {
   private:
    int V, E;
    vector<pair<int, pair<int, int>>> edges;

   public:
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void add_edge(int u, int v, int w) {
        edges.push_back(make_pair(w, make_pair(u, v)));
    }

    int calculate_weight() {
        int total_weight = 0;
        Sets sets(V);

        sort(edges.rbegin(), edges.rend());  // sort in descending order

        for (auto it = edges.begin(); it != edges.end(); it++) {
            int u = it->second.first;
            int v = it->second.second;

            int set_u = sets.find(u);
            int set_v = sets.find(v);

            if (set_u != set_v) {
                total_weight += it->first;
                sets.merge(set_u, set_v);
            }
        }

        return total_weight;
    }
};

int main() {
    int v, e;
    scanf("%d", &v);
    scanf("%d", &e);

    Graph g(v, e);

    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        g.add_edge(u, v, w);
    }
    int mst_weight = g.calculate_weight();

    cout << mst_weight << endl;
    return 0;
}