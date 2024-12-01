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

int n, q;
vector<int> k;
vector<int> a; 

void getData(){
    cin>>n>>q;
    for(int i = 0; i <q; i++){
        int temp;
        cin>>temp;
        k.PB(temp);
    }
    for(int i =0; i<n-1; i++){
        int temp;
        cin>>temp;
        a.PB(temp);
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
    for(int i =0 ; i<a.size(); i++){
        int cur = a[i];
        graph[cur].PB(i+2); //starts with a_2
    }

    vector<int> depth = traverseGraph(graph);

    //process verticies
    vector<int> dp(n+1, 0);

    vector<int> task(n+1, 0);
    vector<int> blocks;
    vector<int> blocksSize(n+1, 1);

    int maxDepth = 0;
    for(int i = 1; i<depth.size(); i++){
        task[depth[i]]++;
        maxDepth = max(maxDepth, depth[i]);
    }

    for(int i = 1; i<=maxDepth; i++){
        blocks.PB(i);
    }

    int totalSize = n;
    for(int i = n-1; i>= 1; i--){
        int ind = 0;
        vector<int> next;
        while(ind < blocks.size()){
            int delta = 0;
            do{
                if(ind < blocks.size()){
                    next.PB(blocks[ind]);
                    if(task[blocks[ind]] > i){
                        delta = blocksSize[blocks[ind]];
                    }
                    if(delta == 0){
                        ind++;
                        break;
                    } 
                }

                if(ind >= blocks.size()-1){
                    int b = blocks.back() + blocksSize[blocks.back()];
                    blocksSize[blocks.back()] += delta/i;
                    delta -= delta/i;
                    if(delta > 0){
                        task[b + delta/i] += delta;
                        delta = 0;
                        next.PB(b + delta/i); 
                    }
                    task[blocks.back()] = i;
                }else{
                    int b = blocks[ind] + blocksSize[blocks[ind]];
                    if(blocksSize[b] == 1 && task[b] + delta < i){
                        task[b] += delta;
                        delta = 0;
                        next.PB(b);
                    }else{
                        delta -= (i-task[b])*blocksSize[b];
                        blocksSize[blocks[ind]] += blocksSize[b];
                    }
                    task[blocks[ind]] = i;
                    ind+=2;
                }
            }while(delta > 0);
        }

        blocks = next;
        dp[i] = next.back() + blocksSize[next.back()]-1;
    }

    //get ans
    vector<int> ans;
    for(int i = 0; i<q; i++){
        ans.PB(dp[k[i]]);
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