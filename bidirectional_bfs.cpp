/*  Bidirectional Breadth first search implementation in C++ 
    Time Complexity: O(b^(d/2)) where 
    Space Complexity: O(b^(d/2)) where 
*/

#include<bits/stdc++.h>
using namespace std;

bool bfs_step(queue<int> &q, vector<bool> &visited, vector<bool> &otherVisited, vector<int> &parent, vector<vector<int>> &adj, int &meet){
    int sz = q.size();
    while (sz--) {
        int u = q.front(); q.pop();

        for (int nb : adj[u]) {
            if (!visited[nb]) {
                visited[nb] = true;
                parent[nb] = u;
                q.push(nb);

                // intersection found
                if (otherVisited[nb]) {
                    meet = nb;
                    return true;
                }
            }
        }
    }
    return false;
}

vector<int> bidirectional_bfs(int v, int src, int tgt, vector<vector<int>> &adj){
    if (src == tgt) return {src};

    queue<int> sq, tq;
    vector<bool> sv(v, false), tv(v, false);
    vector<int> sparent(v, -1), tparent(v, -1);

    sq.push(src);
    tq.push(tgt);
    sv[src] = true;
    tv[tgt] = true;

    int meet = -1;

    while (!sq.empty() && !tq.empty()) {
        if (bfs_step(sq, sv, tv, sparent, adj, meet))
            break;

        if (bfs_step(tq, tv, sv, tparent, adj, meet))
            break;
    }

    if (meet == -1) return {};

    // ---- Path reconstruction ----
    vector<int> path;

    int cur = meet;
    while (cur != -1) {
        path.push_back(cur);
        cur = sparent[cur];
    }
    reverse(path.begin(), path.end());

    cur = tparent[meet];
    while (cur != -1) {
        path.push_back(cur);
        cur = tparent[cur];
    }

    return path;
}

int main(){
    int v = 11;
    int src = 0, tgt = 10;
    vector<vector<int>> adj(v);
    vector<vector<int>> edges = {{0,2}, {0,1}, {1,3}, {2,4}, {3,5}, {4, 5}, {5, 6}, {5, 7}, {6,8}, {7,9}, {8,10}, {9,10}};
    for(int i = 0; i < edges.size(); i++){
        int a = edges[i][0], b = edges[i][1];
        adj[a].push_back(b);
        adj[b].push_back(a); 
    }
    vector<int> path = bidirectional_bfs(v,src,tgt,adj);
    if(!path.empty()){
        cout<<"Path from "<<src<<"-"<<tgt<<": ";
        for(int node: path) cout<<node<<" ";
        cout<<endl;
    }else{
        cout<<"Target Not found"<<endl;
    }
    return 0;
}