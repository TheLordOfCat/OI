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
    dp[n] = blocks.size();
    for(int i = n-1; i>= 1; i--){
        int ind = 0;
        vector<int> next;
        int delta = 0;
        while(ind < blocks.size()){
            do{
                //process the first block
                next.PB(blocks[ind]);
                if(i < task[blocks[ind]]){
                    delta -= (i-task[blocks[ind]])*blocksSize[blocks[ind]];
                    task[blocks[ind]] = i;
                }
                if(i > task[blocks[ind]]){
                    if(delta > i - task[blocks[ind]]){
                        delta -= (i-task[blocks[ind]])*blocksSize[blocks[ind]];
                        task[blocks[ind]] = i;
                    }else{
                        task[blocks[ind]] += delta;
                        delta = 0;
                    }
                }

                if(ind == blocks.size()-1){
                    ind++;
                    break;
                }

                if(delta == 0){
                    ind++;
                    break;
                }

                //merge second
                if(ind < blocks.size()-1){
                    int b = blocks[ind] + blocksSize[blocks[ind]];
                    if(blocksSize[b] == 1 && task[b] + delta < i){
                        task[b] += delta;
                        delta = 0;
                        next.PB(b);
                    }else{
                        delta -= (i-task[b])*blocksSize[b];
                        blocksSize[blocks[ind]] += blocksSize[b];
                    }
                    ind += 2;
                }
            }while(delta > 0 && ind < blocks.size());
            
        }

        if(delta > 0){
            int b = next.back() + blocksSize[next.back()];
            int len = delta/i;
            blocksSize[next.back()] += len;
            delta -= len*i;
            task[next.back()] = i;
            if(delta > 0){
                task[b + len] += delta;
                delta = 0;
                next.PB(b + len); 
            }
        }

        blocks = next;
        dp[i] = next.back() + blocksSize[next.back()]-1;
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