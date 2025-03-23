#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

vector<set<int>> graph;       // Adjacency list
vector<int> S, T;              // Temporary arrays for lexicographic tests
int n;                         // Number of vertices


void loadGraph(const string &filename) {
    ifstream file(filename);
    string line;
    int u, v;

    while (getline(file, line)) {
        istringstream iss(line);
        iss >> u >> v;
        u--, v--;  // Convert to zero-based indexing
        
        if (max(u, v) >= graph.size()) {
            graph.resize(max(u, v) + 1);
        }
        graph[u].insert(v);
        graph[v].insert(u);
    }
    file.close();
    n = graph.size();

    // Initialize S and T arrays
    S.assign(n, 0);
    T.assign(n, 0);
}


void UPDATE(int i, set<int> &C) {
    if (i == n + 1) {
        // Print out the current maximal clique
        cout << "Clique: { ";
        for (int v : C) cout << v + 1 << " ";
        cout << "}\n";
        return;
    }

    set<int> N_i = graph[i - 1];  // N(i)
    
    if (includes(C.begin(), C.end(), N_i.begin(), N_i.end())) {
        UPDATE(i + 1, C);
    }

    // Prepare for lexicographic tests
    for (int x : C) {
        for (int y : graph[x]) {
            if (C.find(y) == C.end() && y != i - 1) {
                T[y]++;
            }
        }
    }

    for (int x : N_i) {
        if (C.find(x) == C.end()) {
            for (int y : graph[x]) {
                if (C.find(y) == C.end() && y != i - 1) {
                    S[y]++;
                }
            }
        }
    }

    bool FLAG = true;

    // Maximality test
    for (int y : N_i) {
        if (y < i - 1 && T[y] == C.size()) {
            FLAG = false;
            break;
        }
    }
    
    // Lexicographic order test
    vector<int> C_minus_Ni;
    for (int v : C) {
        if (N_i.find(v) == N_i.end()) {
            C_minus_Ni.push_back(v);
        }
    }
    sort(C_minus_Ni.begin(), C_minus_Ni.end());

    for (int k = 0; k < C_minus_Ni.size(); ++k) {
        int jk = C_minus_Ni[k];
        for (int y : graph[jk]) {
            if (C.find(y) == C.end() && y < i - 1 && T[y] == C.size()) {
                if (y > jk) {
                    S[y]--;
                } else {
                    if (k == 0 || y < C_minus_Ni[k - 1]) {
                        if (S[y] + k >= C_minus_Ni.size() && y > C_minus_Ni[k - 1]) {
                            FLAG = false;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (FLAG) {
        set<int> SAVE;
        for (int v : C) {
            if (N_i.find(v) == N_i.end()) {
                SAVE.insert(v);
            }
        }

        C.insert(i - 1);
        UPDATE(i + 1, C);

        C.erase(i - 1);
        for (int v : SAVE) {
            C.insert(v);
        }
    }

    // Reset S and T
    for (int x : C) {
        for (int y : graph[x]) {
            if (C.find(y) == C.end() && y != i - 1) {
                T[y] = 0;
            }
        }
    }

    for (int x : N_i) {
        if (C.find(x) == C.end()) {
            for (int y : graph[x]) {
                if (C.find(y) == C.end()) {
                    S[y] = 0;
                }
            }
        }
    }
}


void CLIQUE() {
    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 0);
    sort(vertices.begin(), vertices.end(), [](int a, int b) {
        return graph[a].size() < graph[b].size();
    });

    set<int> C;
    UPDATE(1, C);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        return 1;
    }

    loadGraph(argv[1]);
    CLIQUE();

    return 0;
}

