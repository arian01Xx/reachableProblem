#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

class SolutionFiftyFive{
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<vector<pair<int,int>>> adj(n);
        for(auto i: edges){
            adj[i[0]].push_back({i[1],i[2]+1});
            adj[i[1]].push_back({i[0],i[2]+1});
        }
        vector<int> dist(n,1e8);
        dist[0]=0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
        map<int,int> par;
        par[0]=0;
        q.push({0,0});

        while(!q.empty()){
            int node=q.top().second;
            int wt=q.top().first;
            q.pop();

            if(wt > maxMoves) continue;
            for(auto i: adj[node]){
                if(wt+i.second <= maxMoves && dist[i.first]>wt+i.second){
                    par[i.first]=node;
                    //se actualiza
                    dist[i.first]=wt+i.second; //igual a la suma de los dos pesos
                    q.push({dist[i.first], i.first});
                }
            }
        }
        int ans=0;
        for(auto i: edges){
            if(((par.count(i[0]) && par[i[0]]==i[1]) || (par.count(i[1]) && par[i[1]]==i[0]))){
                ans+=i[2];
            }else if(dist[i[0]]==1e8 && dist[i[1]]!=1e8){
                ans+=maxMoves - dist[i[1]];
            }else if(dist[i[0]]!=1e8 && dist[i[1]]==1e8){
                ans+=maxMoves - dist[i[0]];
            }else if(dist[i[0]]!=1e8 && dist[i[1]]!=1e8){
                ans+=min(2*maxMoves - dist[i[0]]-dist[i[1]] , i[2]);
            }
        }
        for(auto i: dist){
            ans+=(i != 1e8);
        }
        return ans;
    }
};

int main(){

    return 0;
}