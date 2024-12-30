#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PB push_back
#define MT make_tuple
#define PIC pair<int,char>

int n;
vector<tuple<int,int,char>> edges;

void getData(){
    edges.clear();

    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        char c;
        cin>>a>>b>>c;
        edges.PB(MT(a,b,c));
    }
}

void bfsSolve(int vS, vector<vector<int>>& tree, vector<vector<PIC>>& graph){
    vector<int> temp(26, -1);

    vector<bool> used(n+1, false);
    stack<tuple<PII, string>> S;
    S.push(MT(MP(vS, 0),string()));
    used[vS] = true;

    while(!S.empty()){
        PII v = get<0>(S.top());
        string s = get<1>(S.top());
        S.pop();

        bool moved = false;

        for(int i =0 ; i<graph[v.first].size(); i++){
            PIC cur = graph[v.first][i];
            if(!used[cur.first]){
                used[cur.first] = true;
                if(tree[v.second][cur.second-'A'] == -1){
                    tree.PB(temp);
                    tree[v.second][cur.second-'A'] = tree.size()-1;
                }
                S.push(MT(MP(cur.first, tree[v.second][cur.second-'A']), s+cur.second));
                moved = true;
            }
        }

        if(!moved){
            int p = 0;
            for(int i = s.size(); i>0; i--){
                if(tree[p][s[i-1]-'A'] == -1){
                    vector<int> temp(26, -1);
                    tree.PB(temp);
                    tree[p][s[i-1]-'A'] = tree.size()-1;
                }
                p = tree[p][s[i-1]-'A'];
            }
        }
    }
}

vector<vector<int>> getTree(vector<vector<PIC>>& graph){
    vector<int> temp(26, -1);
    vector<vector<int>> tree(1,temp);
    for(int i = 1; i<=n; i++){
        bfsSolve(i, tree, graph);
    }
    return tree;
}

void mark(int vS, vector<int>& depth, vector<vector<PIC>>& graph, vector<vector<int>>& tree, vector<vector<tuple<int,int,int>>> &trio){
    stack<tuple<PII, tuple<int,int,int>>> S;
    S.push(MT(MP(vS,0), MT(vS,vS,vS)));
    vector<bool> used(n+1, false);

    while(!S.empty()){
        PII v = get<0>(S.top());
        used[v.first] = true;
        tuple<int,int,int> t = get<1>(S.top());
        S.pop();

        trio[v.second].PB(t);

        for(int j = 0; j<graph[v.first].size(); j++){
            PIC cur = graph[v.first][j];
            if(!used[cur.first]){
                used[cur.first] = true;
                if(tree[v.second][cur.second-'A'] != -1){
                    int nextT = tree[v.second][cur.second-'A'];
                    tuple<int,int,int> tc = t;
                    if(depth[get<1>(tc)] > depth[cur.first]){
                        get<1>(tc) = cur.first;
                    }
                    get<2>(tc) = cur.first;
                    S.push(MT(MP(cur.first, nextT), tc));
                }
            }
        }
    }
}

vector<int> getLeafs(vector<vector<PIC>>& graph){
    vector<int> ans;
    for(int i = 1; i<=n; i++){
        if(graph[i].size() == 1){
            ans.PB(i);
        }
    }

    return ans;
}

vector<int> getDepth(vector<vector<PIC>>& graph){
    vector<int> ans(n+1, -1);
    ans[1] = 0;
    stack<int> S;
    S.push(1);

    while(!S.empty()){
        int v = S.top();
        S.pop();

        for(int i =0; i< graph[v].size(); i++){
            int cur = graph[v][i].first;
            if(ans[cur] == -1){
                ans[cur] = ans[v] +1;
                S.push(cur);
            }
        }
    }

    return ans;
}

bool verifyPattern(int vS, vector<vector<pair<int,char>>>& graph,  vector<vector<tuple<int,int,int>>> &trio, vector<int>& leafs){
    vector<int> dp(n+1, 0);
    for(int i = 0; i<trio[vS].size(); i++){
        int a = get<0>(trio[vS][i]), b = get<1>(trio[vS][i]), c = get<2>(trio[vS][i]);
        dp[a] += 1;
        dp[b] -= 2;
        dp[c] += 1;
    }

    stack<int> S;
    for(int i = 0; i<leafs.size(); i++){
        S.push(leafs[i]);
    }

    vector<int> t(n+1, 0);
    for(int i = 1; i<=n; i++){
        t[i] = graph[i].size()-1;
    }

    while(!S.empty()){
        int v = S.top();
        S.pop();

        for(int i = 0; i < graph[v].size(); i++){
            int cur = graph[v][i].first;
            t[cur]--;
            if(t[cur] == 0 && cur != 1){
                S.push(cur);
            }else if(t[cur] < 0 && cur != 1){
                dp[v] += dp[cur];
            }
        }
    }

    for(int i = 0; i < graph[1].size(); i++){
        int cur = graph[1][i].first;
        dp[1] += dp[cur];
    }

    bool ans = true;
    for(int i = 2; i<=n; i++){
        if(dp[i] == 0){
            ans = false;
            break;
        }
    }

    return ans;
}

vector<string> solve(){
    //create graph
    vector<vector<pair<int,char>>> graph(n+1, vector<pair<int,char>>());
    for(int i =0 ; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]);
        char c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    //generate trie
    vector<vector<int>> tree = getTree(graph);

    //get depth
    vector<int> depth = getDepth(graph);

    //get ops
    vector<vector<tuple<int,int,int>>> trio(tree.size(), vector<tuple<int,int,int>>());

    for(int i = 1; i<=n; i++){
        mark(i, depth, graph, tree, trio);
    }

    //get leafs
    vector<int> leafs = getLeafs(graph);

    //get ans
    vector<string> ans;

    stack<pair<int,string>> S;
    S.push(MP(0, string()));
    while(!S.empty()){
        int v = S.top().first;
        string s = S.top().second;
        S.pop();

        if(!s.empty()){
            bool ok = verifyPattern(v, graph, trio, leafs);
            if(ok){
                ans.PB(s);
            }
        }
        for(int i = 25; i>=0; i--){
            int cur = tree[v][i];
            if(cur != -1){
                char temp = 'A'+i;
                S.push(MP(cur, s+temp));
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<string> ansS = solve();
    cout<<ansS.size()<<"\n";
    for(int i =0 ; i<ansS.size(); i++){
        cout<<ansS[i]<<"\n";
    }

    return 0;
}