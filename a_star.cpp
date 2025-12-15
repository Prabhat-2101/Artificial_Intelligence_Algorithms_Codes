/* A-Star Algorithm Implementation in C++
   This implementation finds the shortest path from a source node to a target node in a weighted graph using the A* search algorithm.

*/
#include<bits/stdc++.h>
using namespace std;

int a_star(int v, int src, int tgt, vector<vector<pair<int,int>>> &adj, vector<int> &heuristic){
    vector<int> dist(v, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({heuristic[src], src});
    while(!pq.empty()){
        auto [cost, u] = pq.top();
        pq.pop();
        if(u == tgt) return dist[tgt];
        for(auto &[nb, w] : adj[u]){
            int newDist = dist[u] + w;
            if(newDist < dist[nb]){
                dist[nb] = newDist;
                pq.push({newDist + heuristic[nb], nb});
            }
        }
    }
    return -1;
}

int main(){
    int v = 5;
    int src = 0, tgt = 4;
    vector<vector<pair<int,int>>> adj(v);
    vector<vector<int>> edges = {{0,2,4}, {0,1,1}, {2,3,2}, {1,2,2}, {2,4,12}, {1,3,5}, {4,3,3}};
    vector<int> heuristic = {7, 6, 2, 1, 0};
    for(int i = 0; i < edges.size(); i++){
        int a = edges[i][0], b = edges[i][1], w = edges[i][2];
        adj[a].push_back({b, w});
        adj[b].push_back({a, w}); 
    }
    int cost = a_star(v,src,tgt,adj,heuristic);
    cout << "Shortest path cost from " << src << " to " << tgt << " is: " << cost << endl;
    return 0;
}