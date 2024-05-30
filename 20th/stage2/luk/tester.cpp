#include<iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int MAXN = 300'000;

int n;
vector<vector<int>> graph;

void getData(){
    cin>>n;
    graph.assign(n+1, vector<int>());
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        graph[a].PB(b);
        graph[b].PB(a);
    }
}

void getRandom(){
    n = rand()%10+1;
    graph.clear();
    graph.assign(n+1,vector<int>());
    int ind = 2;
    for(int i = 1; i<n; i++){
        if(ind >n){
            break;
        }
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            graph[i].PB(ind);
            ind++;
        }
    }
}

void printData(){
    cout<<n<<"\n";
    stack<int> S;
    vector<bool> vis(n+1, false);
    for(int i =1 ;i<=n; i++){
        if(!vis[i]){
            S.push(i);
            vis[i] = true;
            while(!S.empty()){
                int v=  S.top();
                for(int j =0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    cout<<i<<" "<<cur<<"\n";
                    vis[cur] = true;
                }
            }
        }
    }
}

int brute(){
    vector<int> depth(n+1, 0);

    stack<PII> S;
    vector<bool>check(n+1, false);
    S.push(MP(1,0));
    check[1] = true;
    while(!S.empty()){
        int v = S.top().first;
        int d = S.top().second;
        S.pop();
        depth[v] = d;
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!check[cur]){
                check[cur] = true;
                S.push(MP(cur, d+1));
            }
        }
    }

    int ans = n;
    for(int i = n-1; i> 0; i--){
        bool ok = true;

        int t = 1;
        vector<int> turn(n+1, 0);
        queue<int> Q;
        vector<bool>vis(n+1, false);
        vis[1] = true;
        for(int j =0; j<graph[1].size(); j++){
            int cur = graph[1][j];
            Q.push(cur);
            vis[cur] = true;
        }
        
        while(!Q.empty()){
            for(int k = 0; k<i; k++){
                if(Q.empty()){
                    break;
                }
                int v = Q.front();
                Q.pop();
                turn[v] = t;
                if(t > depth[v]){
                    ok = false;
                    break;
                }
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur]){
                        vis[cur] = true;
                        Q.push(cur);
                    }
                }
            }
            t++;
        }

        if(ok){
            ans--;
        }else{
            break;
        }
    }

    return ans;
}

int solve(){
    vector<int> depth(n+1, 0);

    stack<PII> S;
    vector<bool>check(n+1, false);
    S.push(MP(1,0));
    check[1] = true;
    while(!S.empty()){
        int v = S.top().first;
        int d = S.top().second;
        S.pop();
        depth[v] = d;
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!check[cur]){
                check[cur] = true;
                S.push(MP(cur, d+1));
            }
        }
    }


    int left = 1, right = n-1; 
    int ans = n;
    while(left <= right){
        int mid = left + (right - left)/2;
        bool ok = true;
        int i = mid;

        int t = 1;
        vector<int> turn(n+1, 0);
        queue<int> Q;
        vector<bool>vis(n+1, false);

        vis[1] = true;
        for(int j =0; j<graph[1].size(); j++){
            int cur = graph[1][j];
            Q.push(cur);
            vis[cur] = true;
        }

        while(!Q.empty()){
            for(int k = 0; k<i; k++){
                if(Q.empty()){
                    break;
                }
                int v = Q.front();
                Q.pop();
                turn[v] = t;
                if(t > depth[v]){
                    ok = false;
                    break;
                }
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur]){
                        vis[cur] = true;
                        Q.push(cur);
                    }
                }
            }
            t++;
        }

        if(ok){
            ans = mid;
            right = mid-1;
        }else{
            left = mid+1;
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1;test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        int ansB = brute();
        int ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }
    return 0;
}