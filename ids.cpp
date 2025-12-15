/*  Iterative deepening search implementation in C++ 
    Time Complexity: O(b^d) where b is branching factor and d is depth limit
    Space Complexity: O(d) where d is depth limit
*/
#include<bits/stdc++.h>
using namespace std;

bool dls(vector<vector<int>>& adj, int node, int target, int depth, vector<int>& path){
    path.push_back(node);

    if(node == target) return true;
    if(depth == 0){
        path.pop_back();
        return false;
    }

    for(int neighbor : adj[node]){
        if(dls(adj, neighbor, target, depth - 1, path))
            return true;
    }

    path.pop_back();
    return false;
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
    vector<int> path;
    int depth = 0, target = 7;
    while(true){
        vector<int> path;
        if(dls(adj, 0, target, depth, path)){
            cout << "Found at depth " << depth << "\nPath: ";
            for(int x : path) cout << x << " ";
            break;
        }
        depth++;
    }
    return 0;
}