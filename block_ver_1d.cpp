#include<iostream>
#include<omp.h>
#include<chrono>
#include<vector>
#include<limits> 
#include<cstdlib>
#include <fstream>
#include <sstream> 
using namespace std;
using namespace chrono;
const double INF = numeric_limits<double>::infinity();


void blocked_floyd_warshall(vector<double>& distance, int n, int B) {
    int b = n/B;
    for(int k = 0; k < B; k++) {
        auto dep_start = high_resolution_clock::now();
        // Dependent phase
        for(int l = b * k; l < b * (k + 1); l++) {
            
            for(int i = b * k; i < b * (k + 1); i++) {
                for(int j = b * k; j < b * (k + 1); j++) {
                    distance[i * n + j] = min(distance[i * n + j], distance[i * n + l] + distance[l * n + j]);
                }
            }
        }
        auto dep_stop = high_resolution_clock::now();
        auto dep_duration = duration_cast<milliseconds>(dep_stop - dep_start);
        cout << "Dependent phase duration: " << dep_duration.count() << " milliseconds" << endl;

        auto part_dep_start = high_resolution_clock::now();
        // Partially dependent phase
        for(int l = b * k; l < (k + 1) * b; l++) {
        for(int i = k * b; i < (k + 1) * b; i++) {
           for(int j = 0; j < n; j++) {
            if(j < k * b || j >= (k + 1) * b) {
                distance[i * n + j] = min(distance[i * n + j], distance[i * n + l] + distance[l * n + j]);
            }
        }
    }
}
        auto part_dep_stop = high_resolution_clock::now();
        auto part_dep_duration = duration_cast<milliseconds>(part_dep_stop - part_dep_start);
        cout << "Column wise partially dependent phase duration: " << part_dep_duration.count() << " milliseconds" << endl;

        auto part_dep_start_row = high_resolution_clock::now();
        // Partially dependent phase
        for(int l = b * k; l < (k + 1) * b; l++) {
            for(int i = 0; i < n; i++) {
                if(i < k * b || i >= (k + 1) * b) {
                    for(int j = k * b; j < (k + 1) * b; j++) {
                        distance[i * n + j] = min(distance[i * n + j], distance[i * n + l] + distance[l * n + j]);
                    }
                }
            }
        }
        auto part_dep_stop_row = high_resolution_clock::now();
        auto part_dep_duration_row = duration_cast<milliseconds>(part_dep_stop_row - part_dep_start_row);
        cout << "Row based partially dependent phase duration: " << part_dep_duration_row.count() << " milliseconds" << endl;

        auto ind_start = high_resolution_clock::now();
        // Independent phase
        for(int l = b * k; l < (k + 1) * b; l++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if((i < k * b || i >= (k + 1) * b) && (j < k * b || j >= (k + 1) * b)) {
                        distance[i * n + j] = min(distance[i * n + j], distance[i * n + l] + distance[l * n + j]);
                    }
                }
            }
        }
        auto ind_stop = high_resolution_clock::now();
        auto ind_duration = duration_cast<milliseconds>(ind_stop - ind_start);
        cout << "Independent phase duration: " << ind_duration.count() << " milliseconds" << endl;
    }
}
int main(){
    string fileName = "adjacencymatrix_2048.txt";
    int n;

    // Read graph from file
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Unable to open file: " << fileName << endl;
        return 1;
    }

    inputFile >> n;
    vector<double> graph(n * n, INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> graph[i * n + j];
            if (graph[i * n + j] == 0 && i != j) {
                graph[i * n + j] = INF;
            }
        }
    }

    inputFile.close();

    // Apply Floyd-Warshall algorithm
    vector<double> distance = graph;
    int B = 16;

    // Measure time for Floyd-Warshall algorithm
    auto start = high_resolution_clock::now();
    blocked_floyd_warshall(distance, n, B);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}
