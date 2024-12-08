#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using ll = long long int;
using ull = unsigned long long int;

const int MAXN = 1'000'000;
const int MAXQ = 1'000'000;

int n, q;
// vector<int> k;
// vector<int> a; 

int k[MAXN], a[MAXQ];

void getData(){
    cin>>n>>q;
    for(int i = 0; i <q; i++){
        int temp;
        cin>>temp;
        // k.PB(temp);
        k[i] = temp;
    }
    for(int i =0; i<n-1; i++){
        int temp;
        cin>>temp;
        // a.PB(temp);
        a[i] = temp;
    }
}

vector<int> traverseGraph(vector<vector<int>>& graph){
    vector<int> ans(n+1, 0);

    queue<int> Q;
    Q.push(1);
    ans[1] = 1;

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            ans[cur] = ans[v] + 1;
            Q.push(cur);
        }
    }

    return ans;
}

vector<int> solve(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i<n; i++){
        int cur = a[i];
        graph[cur].PB(i+2); //starts with a_2
    }

    vector<int> depth = traverseGraph(graph);

    //process verticies
    vector<int> task(n+1, 0);
    vector<vector<int>> blocks(n+1, vector<int>());
    vector<int> blocksSize(n+1, 1);
    vector<bool> startBlock(n+1, false);

    int maxDepth = 0;
    for(int i = 1; i<depth.size(); i++){
        task[depth[i]]++;
        maxDepth = max(maxDepth, depth[i]);
    }

    vector<int> dp(n+1, maxDepth);

    for(int i = 1; i<= n; i++){
        if(task[i] > 0){
            blocks[task[i]].PB(i);
        }
        startBlock[i] = true;
    }

    for(int i = n-1; i>= 1; i--){
        for(int j = 0; j<blocks[i+1].size(); j++){
            int cur = blocks[i+1][j];
            if(startBlock[cur] && task[cur] == i+1){
                int delta = blocksSize[cur];
                task[cur] = i;
                blocks[i].PB(cur);              
                while(delta > 0){
                    int ind = cur + blocksSize[cur];
                    dp[i] = max(dp[i], ind + blocksSize[ind]-1);
                    if(blocksSize[ind] == 1 && task[ind] + delta < i){
                        task[ind] += delta;
                        delta = 0;
                        blocks[task[ind]].PB(ind);
                    }else{
                        blocksSize[cur] += blocksSize[ind];
                        delta -= (i-task[ind])*blocksSize[ind];
                        startBlock[ind] = false;
                    }
                }
            }
        }
    }

    //get ans
    vector<int> ans;
    for(int i = 0; i<q; i++){
        if(k[i] > n){
            ans.PB(dp[n]);
        }else{
            ans.PB(dp[k[i]]);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();
        
    vector<int> ansS = solve();
    for(int j = 0; j<ansS.size(); j++){
        cout<<ansS[j]<<" ";
    }
    cout<<"\n";

    return 0;
}