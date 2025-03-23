
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;

class Graph {
public:
    int numVertices;
    vector<set<int>> adjList;

    Graph(int n) : numVertices(n), adjList(n) {}

    void addEdge(int u, int v) {
        if (u != v) {
            adjList[u].insert(v);
            adjList[v].insert(u);
        }
    }
};

void expand(set<int> &R, set<int> &P, set<int> &X, const vector<set<int>> &adjList, vector<vector<int>> &cliques) {
    if (P.empty() && X.empty()) {
        cliques.push_back(vector<int>(R.begin(), R.end()));
        return;
    }
    int pivot = *P.begin(); // Choose a pivot to reduce recursion depth
    for (int v : P) {
        if (adjList[v].size() > adjList[pivot].size()) {
            pivot = v;
        }
    }
    set<int> P_without_neighbors;
    for (int v : P) {
        if (!adjList[pivot].count(v)) {
            P_without_neighbors.insert(v);
        }
    }
    
    for (int v : P_without_neighbors) {
        set<int> R_new = R;
        R_new.insert(v);
        set<int> P_new, X_new;
        for (int w : P) if (adjList[v].count(w)) P_new.insert(w);
        for (int w : X) if (adjList[v].count(w)) X_new.insert(w);
        expand(R_new, P_new, X_new, adjList, cliques);
        P.erase(v);
        X.insert(v);
    }
}

vector<vector<int>> tomitaCliqueFinder(const Graph &graph) {
    vector<vector<int>> cliques;
    set<int> R, P, X;
    for (int i = 0; i < graph.numVertices; i++) P.insert(i);
    expand(R, P, X, graph.adjList, cliques);
    return cliques;
}

Graph parseGraph(const string &filename) {
    ifstream file(filename);
    string line;
    int maxNode = 0;
    vector<pair<int, int>> edges;
    while (getline(file, line)) {
        if (line[0] == '#') continue;
        stringstream ss(line);
        int u, v;
        ss >> u >> v;
        edges.push_back({u, v});
        maxNode = max({maxNode, u, v});
    }
    Graph graph(maxNode + 1);
    for (auto &[u, v] : edges) graph.addEdge(u, v);
    return graph;
}

int main() {
    vector<string> datasets = {"as-skitter.txt"};
    ofstream outFile("cliques_skitter.txt");
    if (!outFile) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }
    
    for (const auto &dataset : datasets) {
        Graph graph = parseGraph(dataset);
        auto startTime = high_resolution_clock::now();
        vector<vector<int>> cliques = tomitaCliqueFinder(graph);
        auto endTime = high_resolution_clock::now();
        
        int largestCliqueSize = 0;
        map<int, int> cliqueSizeDistribution;
        for (const auto &clique : cliques) {
            int size = clique.size();
            largestCliqueSize = max(largestCliqueSize, size);
            cliqueSizeDistribution[size]++;
        }
        
        outFile << "Dataset: " << dataset << endl;
        outFile << "Total cliques found: " << cliques.size() << endl;
        outFile << "Largest clique size: " << largestCliqueSize << endl;
        outFile << "Execution time: " << duration_cast<milliseconds>(endTime - startTime).count() << " ms" << endl;
        
        outFile << "Clique size distribution:\n";
        for (const auto &[size, count] : cliqueSizeDistribution) {
            outFile << "Size " << size << ": " << count << " cliques\n";
        }
        outFile << "-----------------------------\n";
    }
    
    outFile.close();
    cout << "Report saved to cliques_skitter.txt" << endl;
    return 0;
}
