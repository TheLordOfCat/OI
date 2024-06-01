#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, m, k;
vector<vector<int>> graph;
vector<pair<PII,int>> query;

void getData(){
    cin>>n>>m>>k;
    graph.assign(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        graph[a].PB(b);
        graph[b].PB(a);
    }
    for(int i = 0; i<k; i++){
        int s, t, d;
        cin>>s>>t>>d;
        query.PB(MP(MP(s,t),d));
    }
}

bool customCompare(pair<pair<PII,int>, int> a, pair<pair<PII,int>, int> b) {
    return a.first.first.first < b.first.first.first; 
}

vector<bool> solve(){
    vector<pair<pair<PII,int>, int>> que;
    for(int i =0; i<query.size(); i++){
        if(query[i].first.first > query[i].first.second){
            int temp = query[i].first.first;
            query[i].first.first = query[i].first.second;
            query[i].first.second = temp;
        }
        que.PB(MP(query[i], i));
    }

    sort(que.begin(), que.end(), customCompare);

    vector<bool> ans(k, false);
    int p = -1;
    vector<PII> shortPath(n+1, MP(-1,-1));
    for(int i = 0; i<que.size(); i++){
        int beg = que[i].first.first.first;
        int end = que[i].first.first.second;
        int len = que[i].first.second;

        if(beg != p){
            shortPath.clear();
            shortPath.assign(n+1, MP(-1,-1));

            queue<PII> Q;
            Q.push(MP(beg, 0));
            while(!Q.empty()){
                int v = Q.front().first;
                int l = Q.front().second;
                Q.pop();
                bool next = true;

                if(l%2 == 0){
                    if(shortPath[v].first == -1){
                        shortPath[v].first = l;
                    }else{
                        next = false;        
                    }
                }else{
                    if(shortPath[v].second == -1){
                        shortPath[v].second = l;
                    }else{
                        next = false;        
                    }
                }

                if(next){
                    for(int j = 0; j<graph[v].size(); j++){
                        int cur =graph[v][j];
                        Q.push(MP(cur, l+1));
                    }
                }
            }
        }

        bool ok = false;
        if(len%2 == 0){
            if(shortPath[end].first <= len && shortPath[end].first != -1){
                ok = true;
            }
        }else{
            if(shortPath[end].second <= len && shortPath[end].second != -1){
                ok = true;
            }
        }

        ans[que[i].second] = ok;
        p = beg;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<bool> ansS = solve();
    for(int j =0;j <ansS.size(); j++){
        if(ansS[j]){
            cout<<"TAK\n";
        }else{
            cout<<"NIE\n";
        }
    }
    
    return 0;
}