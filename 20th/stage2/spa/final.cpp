#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>

int n, k;
string start, finish;
vector<string> removed;

void getData(){
    start.clear(); finish.clear(); removed.clear();

    cin>>n>>k;
    cin>>start>>finish;
    for(int i = 0; i<k; i++){
        string temp;
        cin>>temp;
        removed.PB(temp);
    }
}

bool solve(){
    //get graph
    ll vS = 0, vF = 0;
    for(int i = start.size()-1; i>=0; i--){
        if(start[i] == '1'){
            vS += (1<<(start.size()-i-1));
        }
    }
    for(int i = finish.size()-1; i>=0; i--){
        if(finish[i] == '1'){
            vF += (1<<(finish.size()-i-1));
        }
    }

    vector<bool> vR((1<<n)+1, false);
    for(int i = 0; i<removed.size(); i++){
        ll temp = 0;
        for(int j = removed[i].size()-1; j>=0; j--){
            if(removed[i][j] == '1'){
                temp += (1<<(removed[i].size()-j-1));
            }
        }
        vR[temp] = true;
    }

    vector<vector<ll>> graph((1<<n)+1, vector<ll>());
    for(int i = 1; i<(1<<n); i++){
        for(int j = 0; j <n; j++){
            int con = i ^ (1<<j);
            graph[i].PB(con);
            graph[con].PB(i);
        }
    }

    //process graph
    bool ans = false;
    vector<bool> vis((1<<n)+1, false);
    queue<ll> Q;
    Q.push(vS);

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        if(v == vF){
            ans = true;
            break;
        }

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!vis[cur]){
                Q.push(cur);
                vis[cur] = true;
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    bool ansS = solve();
    if(ansS){
        cout<<"TAK\n";
    }else{
        cout<<"NIE\n";
    }

    return 0;
}