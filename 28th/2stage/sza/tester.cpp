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

void getRandom(){
    edges.clear();

    n = rand()%10+1;
    int ind = 2;
    for(int i = 1; i<n-1; i++){
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            char c = rand()%2 + 'A';
            edges.PB(MT(i,ind,c));
            ind++;
            if(ind>n){
                break;
            }
        }
        if(ind>n){
            break;
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<get<0>(edges[i])<<" "<<get<1>(edges[i])<<" "<<get<2>(edges[i])<<"\n";
    }
}

void genOpsBrute(vector<string>& ops){
    stack<string> S;
    S.push(string());
    while(!S.empty()){
        string s = S.top();
        S.pop();
        
        if(!s.empty()){
            ops.PB(s);
        }
        if(s.size() < n){
            for(int i = 1; i>=0; i--){
                string temp = s;
                temp.PB('A' + i);

                S.push(temp);
            }
        }
    }
}

void bfsBrute(string s, vector<bool>& marked, vector<vector<PIC>> &graph){
    for(int i = 1; i<=n; i++){
        vector<int> pr(n+1, 0);
        stack<PII> S;
        pr[i] = -1;
        for(int j = 0; j<graph[i].size(); j++){
            PIC cur = graph[i][j];
            if(cur.second == s.front()){
                S.push(MP(cur.first, 1));
                pr[cur.first] = i;
            }
        }

        while(!S.empty()){
            PII v = S.top();
            S.pop();

            if(v.second == s.size()){
                //backtrack
                int p = v.first;
                while(p != i){
                    marked[p] = true;
                    p = pr[p];
                }
                marked[i] = true;
            }else{
                for(int j = 0; j<graph[v.first].size(); j++){
                    PIC cur = graph[v.first][j];
                    if(pr[cur.first] == 0){
                        if(s[v.second] == cur.second){
                            S.push(MP(cur.first, v.second+1));
                            pr[cur.first] = v.first;
                        }
                    }
                }
            }
        }
    }
}

vector<string> brute(){
    //create graph
    vector<vector<pair<int,char>>> graph(n+1, vector<pair<int,char>>());
    for(int i =0 ; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]);
        char c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    //get ops
    vector<string> ops;
    genOpsBrute(ops);

    //vefrify
    vector<string> ans;

    for(int i = 0; i< ops.size(); i++){
        string s = ops[i];

        vector<bool> marked(n+1, false);
        bfsBrute(s, marked, graph);

        bool ok = true;
        for(int j = 1; j<=n; j++){
            if(!marked[j]){
                ok = false;
            }
        }
        if(ok){
            ans.PB(s);
        }
    }

    return ans;
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
                if(tree[0][s[i-1]-'A'] == -1){
                    vector<int> temp(26, -1);
                    tree.PB(temp);
                    tree[0][s[i-1]-'A'] = tree.size()-1;
                }
                p = tree[0][s[i-1]-'A'];
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

void mark(int v, vector<int>& depth, vector<vector<PIC>>& graph, vector<vector<int>>& tree, vector<vector<tuple<int,int,int>>> &trio){
    stack<tuple<PII, tuple<int,int,int>>> S;
    S.push(MT(MP(v,0), MT(v,v,v)));

    while(!S.empty()){
        PII v = get<0>(S.top());
        tuple<int,int,int> t = get<1>(S.top());
        S.pop();

        trio[v.second].PB(t);

        for(int j = 0; j<graph[v.first].size(); j++){
            PIC cur = graph[v.first][j];
            if(tree[v.second][cur.second-'A'] != -1){
                int nextT = tree[v.second][cur.second-'A'];
                tuple<int,int,int> tc = t;
                if(depth[get<1>(tc)] > depth[cur.first]){
                    get<1>(tc) = cur.first;
                }
                if(depth[get<2>(tc)] < depth[cur.first]){
                    get<2>(tc) = cur.first;
                }
                S.push(MT(MP(cur.first, nextT), tc));
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

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"Test nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<string> ansB = brute();
        vector<string> ansS = solve();
        bool ok = true;
        if(ansB.size() != ansS.size()){
            ok = false;
        }else{
            for(int i = 0; i<ansB.size(); i++){
                if(ansB[i] != ansS[i]){
                    ok = false;
                    break;
                }
            }
        }
        if(!ok){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<ansB.size()<<"\n";
            for(int i =0 ; i<ansB.size(); i++){
                cout<<ansB[i]<<"\n";
            }
            cout<<"SOLVE: \n";
            cout<<ansS.size()<<"\n";
            for(int i =0 ; i<ansS.size(); i++){
                cout<<ansS[i]<<"\n";
            }
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}