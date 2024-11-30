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
    srand(time(0));

    n = rand()%10+1;
    q = rand()%3+1;

    for(int i = 0; i<q; i++){
        int temp = rand()%10+1;
        k.PB(temp);
    }
    
    for(int i = 0; i<n; i++){
        int temp = rand()%10+1;
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
    for(int i = 0; i<n; i++){
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
                ans[v] += ans[cur];
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

vector<int> solve(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i<a.size(); i++){
        int cur = a[i];
        graph[cur].PB(i+2); //starts with a_2
    }

    vector<int> depth = getDetph(graph);

    //process verticies
    vector<int> dp(n+1, 0);

    vector<int> task(n+1, 0);
    vector<int> blocks;
    vector<int> blocksSize(n+1, 1);
    int totalSize = n;
    for(int i = n-1; i>= 1; i--){
        int ind = 0;
        vector<int> next;
        while(ind < blocks.size()){
            int delta = 0;
            do{
                if(task[blocks[ind]] > i){
                    delta = blocksSize[blocks[ind]];
                }
                if(delta == 0){
                    ind++;
                    break;
                } 
                next.PB(blocks[ind]);

                int b = blocks[ind] + blocksSize[blocks[ind]];
                if(blocksSize[b] == 1 && task[b] + delta < i){
                    task[b] += delta;
                    delta = 0;
                    next.PB(b);
                }else{
                    delta -= (i-task[b])*blocksSize[b];
                    blocksSize[blocks[ind]] += blocksSize[b];
                }

                ind++;
            }while(delta > 0);
        }

        blocks = next;
        dp[i] = next.size();
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

    int op = 1;
    for(int test = 1; test<=1; test++){
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
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}