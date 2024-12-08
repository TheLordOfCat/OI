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

void getRandom(){
    k.clear(); a.clear();
    srand(time(0));

    n = rand()%10+10;
    // q = rand()%4+1;
    q = n;
    for(int i = 0; i<q; i++){
        // int temp = rand()%10+1;
        int temp = i+1;
        k.PB(temp);
    }
    
    for(int i = 2; i<=n; i++){
        int temp;
        if(i == 2){
            temp = 1;
        }else{
            temp = rand()%(i-1)+1;
        }
        a.PB(temp);
    }
}

void printData(){
    cout<<"\nDATA: \n";
    cout<<n<<" "<<q<<"\n";
    for(int i = 0; i<q; i++){
        cout<<k[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<a.size(); i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

vector<int> getDetph(vector<vector<int>>& graph){
    vector<int> ans(n+1, 0);
    stack<pair<int,bool>> S;

    S.push(MP(1,false));
    while(!S.empty()){
        int v = S.top().first;
        bool b =  S.top().second;
        S.pop();

        if(b){
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                ans[v] = max(ans[cur],ans[v]);
            }
            ans[v] += 1;
            continue;
        }

        S.push(MP(v,true));
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            S.push(MP(cur, false));
        }
    }

    return ans;
}

struct customBruteCompare{
    bool operator()(const PII a, const PII b){
        if(a.second == b.second){
            return a.first < b.first;
        }
        return a.second < b.second;
    }
};

vector<int> brute(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i<a.size(); i++){
        int cur = a[i];
        graph[cur].PB(i+2); //starts with a_2
    }

    //get depth
    vector<int> depth = getDetph(graph);

    //process queries
    vector<int> ans;
    for(int i = 0; i<q; i++){
        priority_queue<PII, vector<PII>, customBruteCompare> Q;
        Q.push(MP(1, depth[1]));
        int turns = 0;
        while(!Q.empty()){
            turns++;
            vector<int> next;
            for(int j = 0; j<k[i] && Q.size() > 0; j++){
                int v = Q.top().first;
                Q.pop();

                for(int o = 0; o<graph[v].size(); o++){
                    int cur = graph[v][o];
                    next.PB(cur);
                }
            }

            for(int j = 0; j<next.size(); j++){
                Q.push(MP(next[j], depth[next[j]]));
            }
        }
        ans.PB(turns);
    }

    return ans;
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

    int op = 0;
    for(int test = 1; test<=100000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<q; i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}