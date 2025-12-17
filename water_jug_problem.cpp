#include<bits/stdc++.h>
using namespace std;

class Glass{
public:
    int curr, max_;
    Glass(){}
    Glass(int max_){
        this->max_ = max_;
        this->curr = 0;
    }
    Glass(int max_, int curr){
        this->max_ = max_;
        this->curr = curr;
    }
};

class WaterJugSolver{
    Glass A, B;
    int target;

public:
    WaterJugSolver(Glass a, Glass b, int target){
        this->A = a;
        this->B = b;
        this->target = target;
        printf("Glass A: (curr=%d,max=%d), Glass B: (curr=%d,max=%d), Target: %d\n",A.curr,A.max_, B.curr, B.max_,this->target);
    }

    /* -------- BFS-SAFE OPERATIONS -------- */

    pair<int,int> fill_glass(int a, int b, int idx){
        if(idx == 1) a = A.max_;
        else b = B.max_;
        return {a,b};
    }

    pair<int,int> empty_glass(int a, int b, int idx){
        if(idx == 1) a = 0;
        else b = 0;
        return {a,b};
    }

    pair<int,int> pour_water(int a, int b, bool reverse=false){
        if(!reverse){
            // A -> B
            int B_rem = B.max_ - b;
            int pour = min(a, B_rem);
            a -= pour;
            b += pour;
        }else{
            // B -> A
            int A_rem = A.max_ - a;
            int pour = min(b, A_rem);
            b -= pour;
            a += pour;
        }
        return {a,b};
    }

    void print_path(vector<string>& path){
        for(string s : path)
            cout << s << " ";
        cout << "\n";
    }

    /* ---------------- BFS SOLVER ---------------- */

    bool solve(){
        queue<pair<pair<int,int>, vector<string>>> q;
        set<pair<int,int>> visited;

        q.push({{0,0}, {}});
        visited.insert({0,0});

        while(!q.empty()){
            auto cur = q.front(); q.pop();
            int a = cur.first.first;
            int b = cur.first.second;
            vector<string> path = cur.second;

            if(a == target || b == target){
                print_path(path);
                cout << "Final State: (" << a << "," << b << ")\n";
                return true;
            }

            vector<pair<pair<int,int>, string>> nextStates;

            nextStates.push_back({ fill_glass(a,b,1), "FULL_A" });
            nextStates.push_back({ fill_glass(a,b,2), "FULL_B" });
            nextStates.push_back({ empty_glass(a,b,1), "EMPTY_A" });
            nextStates.push_back({ empty_glass(a,b,2), "EMPTY_B" });
            nextStates.push_back({ pour_water(a,b,false), "POUR_AB" });
            nextStates.push_back({ pour_water(a,b,true),  "POUR_BA" });

            for(auto &ns : nextStates){
                int na = ns.first.first;
                int nb = ns.first.second;

                if(visited.find({na, nb}) == visited.end()){
                    visited.insert({na, nb});
                    vector<string> newPath = path;
                    newPath.push_back(ns.second);
                    q.push({{na, nb}, newPath});
                }
            }
        }
        return false;
    }
};

int main(int argc, char** argv){
    int x, y ,t;
    if(argc < 4){
        cout << "Usage: ./water_jug_problem <X> <Y> <TARGET>\n";
        cin>> x >> y >> t;
    }else{
        x = stoi(argv[1]);
        y = stoi(argv[2]);
        t = stoi(argv[3]);
    }
    Glass a(x,0), b(y,0);
    int target = t;

    WaterJugSolver solver(a, b, target);
    bool solved = solver.solve();

    if(!solved)
        cout << "Can't be solved\n";

    return 0;
}
