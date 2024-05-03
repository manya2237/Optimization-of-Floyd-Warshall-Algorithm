#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

const double INF = numeric_limits<double>::infinity(); // means there is no connection between them

void floydWarshall(vector<vector<double>>& distance) {
    int n = distance.size();

    // Main loop
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Update the distance using vertex k as an intermediate point
                if (distance[i][k] != INF && distance[k][j] != INF) {
                    distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
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
    vector<vector<double>> graph(n, vector<double>(n, 0));
        string mytext;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                inputFile >> mytext;
                if (mytext == "0.000000" && i != j) {
                    graph[i][j] = INF;
                } else {
                    graph[i][j] = stod(mytext);
                }
            }
        }

    inputFile.close();

    // Apply Floyd-Warshall algorithm
    vector<vector<double>> distance = graph;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<distance[i][j]<<" ";
        }
        cout<<endl;
    }

    // Measure time for Floyd-Warshall algorithm
    auto start = high_resolution_clock::now();
    floydWarshall(distance);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    // Write result matrix to the output file
ofstream matrixFile("output_matrix.txt");
if (!matrixFile.is_open()) {
    cerr << "Unable to open output file for matrix." << endl;
    return 1;
}
matrixFile << "Floyd-Warshall Result Matrix:\n";
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        if (distance[i][j] == INF) {
            matrixFile << "INF ";
        } else {
            matrixFile << distance[i][j] << " ";
        }
    }
    matrixFile << "\n";
}
matrixFile.close();
    return 0;
}

