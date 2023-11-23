// Roll no: 31274
// Batch N2

#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

void distance_vector_routing_algorithm() {
    // Initializing Graph
    int numNodes;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    int distanceGraph[numNodes][numNodes] = {0};
    char nodeNames[numNodes];
    for (int i = 0; i < numNodes; i++) {
        cout << "Enter the name for node " << i + 1 << ": ";
        char nodeName;
        cin >> nodeName;
        nodeNames[i] = nodeName;
    }
    for (int i = 0; i < numNodes; i++) {
        for (int j = i; j < numNodes; j++) {
            if (i == j) {
                distanceGraph[i][j] = 0;
            } else {
                int distance;
                cout << "Enter the distance between " << nodeNames[i] << "-" << nodeNames[j] << ": ";
                cin >> distance;
                distanceGraph[i][j] = distance;
                distanceGraph[j][i] = distance;
            }
        }
    }
    int finalDistances[numNodes][numNodes];
    char viaNode[numNodes][numNodes];
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            viaNode[i][j] = -1;
            finalDistances[i][j] = INT_MAX;
        }
    }
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            for (int k = 0; k < numNodes; k++) {
                if (distanceGraph[i][j] > -1 && distanceGraph[j][k] > -1) {
                    if (finalDistances[i][k] > (distanceGraph[i][j] + distanceGraph[j][k])) {
                        finalDistances[i][k] = distanceGraph[i][j] + distanceGraph[j][k];
                        viaNode[i][k] = nodeNames[j];
                        finalDistances[k][i] = finalDistances[i][k];
                        viaNode[k][i] = viaNode[i][k];
                    }
                }
            }
            for (int k = 0; k < numNodes; k++) {
                if (finalDistances[i][k] == INT_MAX && finalDistances[i][j] != INT_MAX && finalDistances[j][k] != INT_MAX) {
                    if (finalDistances[i][k] > (finalDistances[i][j] + finalDistances[j][k])) {
                        finalDistances[i][k] = finalDistances[i][j] + finalDistances[j][k];
                        viaNode[i][k] = nodeNames[j];
                        finalDistances[k][i] = finalDistances[i][k];
                        viaNode[k][i] = viaNode[i][k];
                    }
                }
            }
        }
    }
    cout << "After Update:" << endl;
    for (int i = 0; i < numNodes; i++) {
        cout << nodeNames[i] << " Table:" << endl;
        cout << "Node\tDistance\tVia" << endl;
        for (int j = 0; j < numNodes; j++) {
            cout << nodeNames[j] << "\t" << finalDistances[i][j] << "\t";
            if (viaNode[i][j] == -1) {
                cout << "-" << endl;
            } else {
                cout << viaNode[i][j] << endl;
            }
        }
    }
}

void link_state_routing_protocol() {
    int numNodes;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    char nodeNames[numNodes];
    for (int i = 0; i < numNodes; i++) {
        cout << "Enter the name for node " << i + 1 << ": ";
        char nodeName;
        cin >> nodeName;
        nodeNames[i] = nodeName;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    vector<pair<int, int>> adjList[numNodes];
    for (int i = 0; i < numNodes; i++) {
        for (int j = i + 1; j < numNodes; j++) {
            if (i == j) {
                adjList[i].push_back({j, 0});
            } else {
                int distance;
                cout << "Enter the distance between " << nodeNames[i] << "-" << nodeNames[j] << ": ";
                cin >> distance;
                if (distance != -1) {
                    adjList[i].push_back({j, distance});
                    adjList[j].push_back({i, distance});
                }
            }
        }
    }
    vector<int> shortestDistances(numNodes);
    for (int i = 0; i < numNodes; i++) {
        shortestDistances[i] = 1e9;
    }
    shortestDistances[0] = 0;
    minHeap.push({0, 0});
    while (!minHeap.empty()) {
        int minDist = minHeap.top().first;
        int currentNode = minHeap.top().second;
        minHeap.pop();
        for (auto it : adjList[currentNode]) {
            int adjacentNode = it.first;
            int edgeWeight = it.second;
            if (minDist + edgeWeight < shortestDistances[adjacentNode]) {
                cout << nodeNames[currentNode] << "-" << nodeNames[adjacentNode] << endl;
                shortestDistances[adjacentNode] = minDist + edgeWeight;
                minHeap.push({shortestDistances[adjacentNode], adjacentNode});
            }
        }
    }
    for (int i = 0; i < numNodes; i++) {
        cout << "Distance between " << nodeNames[0] << "-" << nodeNames[i] << ": " << shortestDistances[i] << endl;
    }
}

int main() {
    distance_vector_routing_algorithm();
    link_state_routing_protocol();
    return 0;
}
