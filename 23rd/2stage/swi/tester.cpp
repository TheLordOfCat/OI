#include<iostream>
#include <vector>
#include <queue>
#include <set>

#include <cstdlib>
#include <ctime>

#define PB push_back

using namespace std;

struct range{
    int a;
    int b;
    int l;
    range(int a1, int b1, int l1){
        a = a1;
        b = b1;
        l = l1;
    }
    range(){
        a = -1;
        b = -1;
        l = -1;
    }

    bool operator<(const range &other) const {
        if(l != other.l)
            return l<other.l;
        if (a != other.a)
            return a < other.a;
        return b < other.b;

    }
};

int n, m;
vector<range> R;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        range temp;
        cin>>temp.a>>temp.b>>temp.l;
        R.push_back(temp);
    }
}

void getRandom(){
    R.clear();

    srand(time(0));
    n =rand()%2000+1;
    if(n < 2) n =2;
    m = rand()%100+1;
    for(int i = 0; i<m; i++){
        range temp;
        temp.l = rand()%(n-1) +1;
        temp.a = rand()%(n-temp.l) +1;
        temp.b = rand()%(n-temp.l) +1;
        if(temp.a == temp.b){
            i--;
        }else{
            R.push_back(temp);
        }
    }
}

void printData(){
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<m; i++){
        cout<<R[i].a<<" "<<R[i].b<<" "<<R[i].l<<"\n";
    }
}

int brute(){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        range temp = R[i];
        for(int i = 0; i<temp.l; i++){
            graph[temp.a+i].push_back(temp.b+i);
            graph[temp.b+i].push_back(temp.a+i);
        }
    }

    vector<bool>vis(n+1, false);
    int ans = 0;
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            ans++;
            queue<int> Q;
            Q.push(i);
            vis[i] = true;
            while(!Q.empty()){
                int v = Q.front();
                Q.pop();
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur]){
                        Q.push(cur);
                        vis[cur] = true;
                    }
                }
            }
        }
    }

    return ans;
}

vector<range> spanningTree(vector<range> path, int before){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int r = 0; r < path.size(); r++){
        range cur = path[r];
        graph[cur.a].push_back(cur.b);
        graph[cur.b].push_back(cur.a);
    }

    vector<bool>vis(n+1, false);
    vector<range> ans;
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            queue<int> Q;
            Q.push(i);
            vis[i] = true;
            while(!Q.empty()){
                int v = Q.front();
                Q.pop();
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur]){
                        Q.push(cur);
                        vis[cur] = true;
                        ans.push_back(range(v,cur,before));
                    }
                }
            }
        }
    }

    return ans;
}

int solve(){
    vector<vector<range>> S(n+1,vector<range>());
    int maxL = 0;
    for(int i = 0; i<m; i++){
        S[R[i].l].PB(R[i]);
        maxL = max(maxL, R[i].l);
    }

    int power = 0;
    while(1<<power < maxL) power++;

    for(int i = power-1; i>= 0; i--){
        int before = 1<<(i);
        vector<range> canEdges;
        for(int j = min(1<<(i+1),n); j> before; j--){
            for(int x = 0; x < S[j].size(); x++){
                range cur = S[j][x];
                range t1 = cur;
                t1.l = before;
                canEdges.push_back(t1);
                range t2 = cur;
                t2.a = cur.a + cur.l - before;
                t2.b = cur.b + cur.l - before;
                t2.l = before;
                canEdges.push_back(t2);
            }
            S.pop_back();
        }
        vector<range> span = spanningTree(canEdges, before);
        for(int j = 0; j<span.size(); j++){
            S[before].push_back(span[j]);
        }
    }

    vector<vector<int>> graph(n+1, vector<int>());
    for(auto r = S[1].begin(); r != S[1].end(); r++){
        range cur = *r;
        graph[cur.a].push_back(cur.b);
        graph[cur.b].push_back(cur.a);
    }

    vector<bool>vis(n+1, false);
    int ans = 0;
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            ans++;
            queue<int> Q;
            Q.push(i);
            vis[i] = true;
            while(!Q.empty()){
                int v = Q.front();
                Q.pop();
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur]){
                        Q.push(cur);
                        vis[cur] = true;
                    }
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test = 1; test <= 1000; test++){
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
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}
