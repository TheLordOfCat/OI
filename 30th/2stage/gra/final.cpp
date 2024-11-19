#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <stack>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

int n;
vector<PII> edges;
int Sa, Sb, q;
vector<int> A, B;
vector<tuple<char, char,int>> query;

void getData(){
    edges.clear(); A.clear(); B.clear(); query.clear();

    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
    cin>>Sa>>Sb>>q;
    for(int i =0; i<Sa; i++){
        int temp;
        cin>>temp;
        A.PB(temp);
    }
    for(int i =0; i<Sb; i++){
        int temp;
        cin>>temp;
        B.PB(temp);
    }
    for(int i = 0; i<q; i++){
        char Z, t;
        int w;
        cin>>Z>>t>>w;
        query.PB(MT(Z,t,w));
    }
}

vector<int> getCenter(vector<vector<int>>& graph){
    vector<int> dp(n+1, 0);

    stack<pair<int,bool>> S;
    S.push(MP(1,false));
    vector<bool> vis(n+1, false);

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();
        if(b){
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                dp[v] += dp[cur];
            }
            dp[v]++;
        }
        if(vis[v]){
            continue;
        }

        vis[v] = true;
        S.push(MP(v,true));
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!vis[cur]){
                S.push(MP(cur, false));
            }
        }
    }

    vector<int> centroids;

    queue<int> Q;
    vis.assign(n+1, false);
    vis[1] = true;
    Q.push(1);
    
    while(!Q.empty()){
        int v = Q.front();
        vis[v] = true;
        Q.pop();

        int maxim = n-dp[v];
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(vis[cur]){
                maxim = max(n-dp[cur]+1, maxim);
            }else{
                maxim = max(dp[cur], maxim);
                Q.push(cur);
            }
        }
        if(maxim <= n/2){
            centroids.PB(v);
        }
    }

    return centroids;
}

vector<int> getDistance(vector<vector<int>>& graph, vector<int>& center){
    vector<int> ans(n+1, 0);
    vector<bool> vis(n+1, false);

    queue<int> Q;
    for(int i = 0; i<center.size(); i++){
        vis[center[i]] = true;
        Q.push(center[i]);
    }

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i =0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!vis[cur]){
                vis[cur] = true;
                ans[cur] = ans[v] +1;
                Q.push(cur);
            }
        }
    }

    return ans;
}

int left(int v){
    return v*2;
}

int right(int v){
    return v*2+1;
}

int parent(int v){
    return v/2;
}

int leaf(int v, int R){
    return v+R;
}

pair<vector<int>,int> buildTree(int len){
    int R = 0;
    int depth = 0;

    while((1<<depth) < len){
        R += (1<<depth);
        depth++;
    }

    vector<int> segTree(R+ (1<<depth)+1, 0);

    return MP(segTree, R);
}

ll sumRange(int l, int r, int R, vector<int>& segTree){
    int vL = leaf(l, R);
    int vR = leaf(r, R);

    ll ans = 0;
    ans += segTree[vL];
    if(vL != vR) ans += segTree[vR];

    while(parent(vL) != parent(vR)){
        if(left(parent(vL)) == vL){
            ans += segTree[right(parent(vL))];
        }
        if(right(parent(vR)) == vR){
            ans += segTree[left(parent(vR))];
        }
        vL = parent(vL);
        vR = parent(vR);
    }

    return ans;
}

void updateTree(int v, int R, int val, vector<int>& segTree){
    int V = leaf(v, R);

    while(V >= 1){
        segTree[V] += val;
        V = parent(V);        
    }
}

vector<ll> solve(){
    //get graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    //get centorids
    vector<int> center = getCenter(graph);

    //get distance
    vector<int> distance = getDistance(graph, center);

    //get seg tree
    vector<bool> inA(n+1, false), inB(n+1, false);
    pair<vector<int>, int> segTreeA = buildTree(n), segTreeB = buildTree(n);
    for(int i = 0; i< A.size() ;i++){
        updateTree(distance[A[i]], segTreeA.second, 1, segTreeA.first);
        inA[A[i]] = true;
    }
    for(int i = 0; i< B.size() ;i++){
        updateTree(distance[B[i]], segTreeB.second, 1, segTreeB.first);
        inB[B[i]] = true;
    }

    //get the deafult
    vector<ll> ans;
    ll tempD = 0;
    for(int i = 0; i<A.size(); i++){
        ll temp = sumRange(distance[A[i]], n, segTreeB.second, segTreeB.first);
        if(inB[A[i]]) temp--;
        tempD += temp;
    }
    if(n == 2) tempD = 0;
    ans.PB(tempD);

    //process queries
    for(int o = 0; o<q; o++){
        tempD = 0; // getting the diffrence
        if(get<0>(query[o]) == 'A'){
            tempD = sumRange(distance[get<2>(query[o])], n, segTreeB.second, segTreeB.first);
            if(inB[get<2>(query[o])]) tempD--;

            int type = 1;
            inA[get<2>(query[o])] = true;
            if(get<1>(query[o]) == '-'){
                tempD *= -1;
                type *= -1;
                inA[get<2>(query[o])] = false;
            }

            updateTree(distance[get<2>(query[o])], segTreeA.second, type, segTreeA.first);
        }else{
            tempD = sumRange(1, distance[get<2>(query[o])], segTreeA.second, segTreeA.first);
            if(inA[get<2>(query[o])]) tempD--;

            int type = 1;
            inB[get<2>(query[o])] = true;
            if(get<1>(query[o]) == '-'){
                tempD *= -1;
                type *= -1;
                inB[get<2>(query[o])] = false;
            }

            updateTree(distance[get<2>(query[o])], segTreeB.second, type, segTreeB.first);
        }
        ans.PB(tempD + ans[o]);
    }   


    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<ll> ansS = solve();
    for(int j = 0; j<ansS.size(); j++){
        cout<<ansS[j]<<"\n";
    }

    return 0;
}