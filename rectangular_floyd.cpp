#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <climits>
#include <chrono>
using namespace std;
using namespace chrono;
const double INF = std::numeric_limits<double>::infinity();

void solve(const vector<vector<double>>&dist,const int num_vertices){
    for(int j=0;j<num_vertices;j++){
        for(int i=0;i<num_vertices;i++){
            double r=dist[i][j];
            if (r == INF)
                continue;
                 for (int k = 0; k < num_vertices; ++k) {
                double t = dist[j][k];
                if (t == INF|| i == j || k == j || i==k)
                    continue;
                double s = dist[i][k];
                if (s > r + t) {
                    s = r + t;
                }
            }
        }
    }
}
int main() {
    string fileName = "adjacencymatrix_2048.txt";
    int n;
    
    // Read graph from file
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Unable to open file: " << fileName << endl;
        return 1;
    }

    inputFile >> n;
    vector<vector<double>> graph(n, vector<double>(n, INF));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> graph[i][j];
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;
            }
        }
    }

    inputFile.close();

    // Apply Floyd-Warshall algorithm
    vector<vector<double>> distance = graph;

    // Measure time for Floyd-Warshall algorithm
    auto start = high_resolution_clock::now();
    solve(distance,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout<<duration.count()<<endl;

    return 0;
}
