/*  Breadth first search implementation in C++ 
    Time Complexity: O(V + E) where V is number of vertices and E is number of edges
    Space Complexity: O(V) where V is number of vertices
*/

#include<bits/stdc++.h>
using namespace std;

void bfs(vector<vector<int>>& adj, int node, vector<bool>& visited, vector<int>& path){
    queue<int> q;
    q.push(node);
    visited[node] = true;
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        path.push_back(curr);
        for(int neighbor : adj[curr]){
            if(!visited[neighbor]){
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main(){
    int v = 9;
    vector<vector<int>> adj(v);
    vector<vector<int>> edges = {{0,2}, {0,1}, {1,4}, {2,5}, {2,3}, {3, 8}, {5, 6}, {6, 7}};
    for(int i = 0; i < edges.size(); i++){
        int a = edges[i][0], b = edges[i][1];
        adj[a].push_back(b);
        adj[b].push_back(a); 
    }
    vector<bool> visited(v,false);
    vector<int> path;
    bfs(adj, 0,visited,path);
    for(int node : path){
        cout << node << " ";
    }
    return 0;
}