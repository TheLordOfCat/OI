#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, m;
vector<PII> relat;

void getData(){
    relat.clear();

    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        relat.PB(MP(a,b));
    }
}

vector<int> solve(){
    //get graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<relat.size(); i++){
        int a = relat[i].first, b = relat[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    vector<int> inEdge(n+1, 0);
    for(int i = 3; i<=n; i++){
        inEdge[i] = graph[i].size()/2;
    }

    //topo sort
    stack<int> S;
    S.push(1);

    vector<int> ans(n+1, -1);
    ans[1] = 1;
    inEdge[2] = 0;
    ans[2] = n;
    
    int ind = 2;

    while(!S.empty()){
        int v = S.top();
        S.pop();

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(inEdge[cur] > 0){
                inEdge[cur]--;
                if(inEdge[cur] == 0){
                    S.push(cur);
                    ans[cur] = ind;
                    ind++;
                }
            }
        }
    }

    //check for NIE
    for(int i = 1; i<=n; i++){
        if(ans[i] == -1){
            return vector<int>();
        }
    }

   for(int i = 3; i<=n; i++){
        int countB = 0, countS = 0;
        for(int j = 0; j<graph[i].size(); j++){
            int cur = graph[i][j];
            if(ans[i] > ans[cur]){
                countS++;
            }else{
                countB++;
            }
        }
        if(countB != countS){
            return vector<int>();
        }
    }

    //TAK
    for(int i = 0; i<n; i++){
        ans[i] = ans[i+1];
    }
    ans.pop_back();
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    vector<int> ansS = solve();
    if(ansS.size() == 0){
        cout<<"NIE\n";
    }else{
        cout<<"TAK\n";
    }
    for(int j =0 ; j<ansS.size(); j++){
        cout<<ansS[j]<<" ";
    }

    return 0;
}