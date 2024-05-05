#include<iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int MAXN = 100'000;
const int MAXS = 100'000;
const int MAXM = 200'000;
const int INF = 2'000'000'000;

int n, m, s;
vector<PII> stable;
vector<pair<PII,vector<int>>> depend;

void getData(){
    cin>>n>>s>>m;
    for(int i = 0; i<s; i++){
        int a, b;
        cin>>a>>b;
        stable.PB(MP(a,b));
    }
    for(int i =0; i<m; i++){
        int l,r,k;
        cin>>l>>r>>k;
        vector<int> deeper;
        for(int j = 0; j<k; j++){
            int x;
            cin>>x;
            deeper.PB(x);
        }
        depend.PB(MP(MP(l,r),deeper));
    }
}

void getRandom(){
    srand(time(0));
    stable.clear();
    depend.clear();

    n = rand()%10+1;
    s = rand()%n+1;
    m = rand()%n+1;
    vector<bool> welled(n+1, false);
    for(int i = 0; i<s; i++){
        int a = rand()%n+1;
        if(!welled[a]){
            welled[a] = true;
            stable.PB(MP(a,rand()%100+1));
        }else{
            i--;
        }
    }
    for(int i = 0; i<m; i++){
        int l = rand()%n+1;
        int r = rand()%n+1;
        if(r<=l){
            int temp = l;
            r = l;
            l = temp;
            if(l == 1){
                r++;
            }else{
                l--;
            }
        }
        int k = rand()%(l-r+1)+1;
        vector<int> x;
        vector<int> used(n+1, false);
        for(int j = 0; j<k; j++){
            int a = l + rand()%(l-r+1);
            if(!used[a]){
                used[a] = true;
                x.PB(a);
            }else{
                i--;
            }
        }
        sort(x.begin(),x.end());
        depend.PB(MP(MP(l,r),x));
    }
}

void printData(){
    cout<<n<<" "<<s<<" "<<m<<"\n";
    for(auto a:stable){
        cout<<a.first<<"  "<<a.second<<"\n";
    }
    for(auto a:depend){
        cout<<a.first.first<<" "<<a.first.second<<" "<<a.second.size()<<" ";
        for(auto b:a.second){
            cout<<b<<" ";
        }
        cout<<"\n";
    }
}

pair<bool,vector<int>> brute(){
    vector<vector<int>> graph(n+1, vector<int>());
    vector<int> depth(n+1, INF);
    for(int i = 0; i<s; i++){
        depth[stable[i].first] = stable[i].second;
    }
    vector<int> inEdges(n+1, 0);
    for(int i = 0; i<m; i++){
        int l = depend[i].first.first;
        int r = depend[i].first.second;
        vector<int> x = depend[i].second;
        x.PB(INF+1);
        vector<int> lower;
        int ind = 0;
        for(int j = l;j <=r ; j++){
            if(j == x[ind]){
                ind++;
            }else{
                lower.PB(j);
            }
        }
        for(int j = 0; j<lower.size();j++){
            for(int o =0; o<x.size()-1; o++){
                graph[x[o]].PB(lower[j]);
                inEdges[lower[j]]++;
            }
        }
    }

    vector<bool> vis(n+1, false);
    for(int i = 1; i<=n; i++){
        if(inEdges[i] == 0 && !vis[i]){
            stack<int> S;
            S.push(i);
            vis[i] = true;
            while(!S.empty()){
                int v = S.top();
                S.pop();
                vis[v] = true;
                for(int j = 0; j<graph[v].size();j++){
                    int cur = graph[v][j];
                    inEdges[cur]--;
                    depth[cur] = min(depth[cur], depth[v]-1);
                    if(inEdges[cur] == 0 && !vis[cur]){
                        vis[cur] = true;
                        S.push(cur);
                    }
                }
            }
        }
    }

    bool ok = true;
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            ok = false;
            break;
        }
    }

    if(ok){
        return MP(ok, depth);
    }else{
        return MP(ok, vector<int>(n+1, -1));
    }
}

int R = 1;
int depth = 1;

int parent(int v){
    return v/2;
}

int left(int v){
    return 2*v;
}

int right(int v){
    return 2*v+1;
}

int leaf(int v){
    return R+v;
}

vector<int> cover(int l, int r){
    vector<int> ans;
    int vL = leaf(l);
    int vR = leaf(r);
    ans.PB(vL);
    if(vL != vR) ans.PB(vR);
    
    while(parent(vL) != parent(vR)){
        if(vL == left(parent(vL))){
            ans.PB(right(parent(vL)));
        }
        if(vR == right(parent(vR))){
            ans.PB(left(parent(vR)));
        }
        vL = parent(vL);
        vR = parent(vR);
    }
    return ans;
}

pair<bool, vector<int>> solve(){
    R = 1;
    depth = 1;
    vector<int> tree(4*n+1, INF);
    while(1<<depth < n){
        R += 1<<depth;
        depth++;
    }

    for(int i = 0; i<s; i++){
        tree[leaf(stable[i].first)] = stable[i].second;
    }

    vector<int> inEdge(4*n+1, 0);
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        int l = depend[i].first.first;
        int r = depend[i].first.second;
        vector<int> x = depend[i].second;
        vector<int> vec;

        graph.PB(vector<int>());
        for(auto t: x){
            graph[t].PB(graph.size()-1);
        }
        
        //left to first of x
        if(l != x.front()){
            vector<int> temp = cover(l, x.front()-1);
            for(auto t: temp) vec.PB(t);
        }
        //last of x to right
        if(r != x.back()){
            vector<int> temp = cover(x.back()+1, r);
            for(auto t: temp) vec.PB(t);
        }

        //between x
        vector<int> temp;
        if(x.size() > 1){
            for(int i = 0; i<x.size()-1; i++){
                if(x[i] != x[i+1]-1)
                temp = cover(x[i] +1, x[i+1]-1);
                for(auto t: temp) vec.PB(t);
            }
        }

        for(auto v:vec){
            graph.back().PB(v);
            inEdge[v]++;
        }
    }

    vector<bool> vis(n+1, false);
    stack<int> S;
    S.push(1);
    while(!S.empty()){
        int v = S.top();
        S.pop();
        vis[v] = true;
        if(v < R){
            if(inEdge[left(v)] == 0){
                tree[left(v)] = min(tree[v],tree[left(v)]);
                S.push(left(v));
            }
            if(inEdge[right(v)] == 0){
                tree[right(v)] = min(tree[v],tree[right(v)]);
                S.push(right(v));
            }
        }else{
            v -= R;
            if(graph[v].size() > 0){
                for(int i = 0; i<graph[v].size(); i++){
                    int cur = graph[v][i];
                    for(int j = 0; j<graph[cur].size(); j++){
                        tree[graph[cur][j]] = min(tree[graph[cur][j]], tree[leaf(v)]-1);
                        inEdge[graph[cur][j]]--;
                        if(inEdge[graph[cur][j]] == 0){
                            S.push(graph[cur][j]);
                        }
                    }
                }
            }
        }
    }
    
    bool ok = true;
    for(int i = 1; i<=n; i++){
        if(!vis[i] || tree[leaf(i)] <= 0){
            ok = false;
            break;
        }
    }

    if(ok){
        vector<int> ans = {INF};
        for(int i = leaf(1); i<= leaf(n); i++){
            ans.PB(tree[i]);
        }
        return MP(true, ans);
    }else{
        return MP(false, vector<int>());
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr. "<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        pair<bool, vector<int>> ansB = brute();
        pair<bool, vector<int>> ansS = solve();
        if(ansB.first != ansS.first){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB.first<<" \n";
            for(auto v:ansB.second){
                cout<<v<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: "<<ansS.first<<" \n";
            for(auto v:ansS.second){
                cout<<v<<" ";
            }
            cout<<"\n";
            return 0;
        }else{
            for(int i = 0; i<ansB.second.size(); i++){
                if(ansB.second[i] != ansS.second[i]){
                    cout<<"ERROR\n";
                    cout<<"BRUTE: "<<ansB.first<<" \n";
                    for(auto v:ansB.second){
                        cout<<v<<" ";
                    }
                    cout<<"\n";
                    cout<<"SOLVE: "<<ansS.first<<" \n";
                    for(auto v:ansS.second){
                        cout<<v<<" ";
                    }
                    cout<<"\n";
                    return 0;
                }
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}