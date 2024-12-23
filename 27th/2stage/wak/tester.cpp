#include <algorithm>
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int, int>
#define PB push_back
#define MT make_tuple

int n;
vector<int> w;
vector<PII> edges;

void getData() {
    w.clear();
    edges.clear();

    cin >> n;
    w.PB(-INF);
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        w.PB(temp);
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        edges.PB(MP(a, b));
    }
}

void getRandom() {
    w.clear();
    edges.clear();

    srand(time(0));

    n = rand() % 10 + 1;
    w.PB(-INF);
    for (int i = 0; i < n; i++) {
        int temp = rand() % 10 + 10;
        w.PB(temp);
    }
    int ind = 2;
    for (int i = 1; i <= n; i++) {
        if (ind > n) {
            break;
        }
        int con = rand() % 3 + 1;
        for (int j = 0; j < con; j++) {
            if (ind > n) {
                break;
            }
            edges.PB(MP(i, ind));
            ind++;
        }
    }
}

void printData() {
    cout << n << "\n";
    for (int i = 1; i < w.size(); i++) {
        cout << w[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < edges.size(); i++) {
        cout << edges[i].first << " " << edges[i].second << "\n";
    }
}

pair<ll, vector<int>> bruteRecDfs(int v, int p, int type, vector<vector<int>>& graph) {
    pair<ll, vector<int>> ans = MP(0, vector<int>());
    if (type == 0) {
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != p){
                pair<ll,vector<int>> temp = bruteRecDfs(cur, v, 1, graph);
                if(temp.first > ans.first){
                    ans.first = temp.first;
                    ans.second = temp.second;
                }
            }
        }
        
        ans.first += w[v];
        ans.second.PB(v);
    } else {
        ll sum = 0;
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != p){
                sum += w[cur];
            }
        }

        int best = -1;
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != p){
                pair<ll,vector<int>> temp = bruteRecDfs(cur, v, 0, graph);
                if(temp.first + sum - w[cur] > ans.first){
                    ans.first = temp.first + sum - w[cur];
                    ans.second = temp.second;
                    best = cur;
                }
            }
        }

        //fill up
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != p && cur != best){
                ans.second.PB(v);
                ans.second.PB(cur);
            }
        }
        ans.second.PB(v);
    }

    return ans;
}

tuple<ll, int, vector<int>> brute() {
    // create graph
    vector<vector<int>> graph(n + 1, vector<int>());
    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    ll answ = -1;
    int ansVis = 0;
    vector<int> ansTown;
    for (int i = 1; i <= n; i++) {
        pair<ll, vector<int>> temp = bruteRecDfs(i, -1, 0, graph);
        if (temp.first > answ) {
            answ = temp.first;
            ansTown = temp.second;
            ansVis = (ansTown.size() - 1) / 2;
        }
    }
    reverse(ansTown.begin(), ansTown.end());
    return MT(answ, ansVis, ansTown);
}

vector<int> getParent(vector<vector<int>> &graph) {
    stack<int> S;
    S.push(1);
    vector<int> parent(n + 1, -1);
    parent[1] = 0;
    while (!S.empty()) {
        int v = S.top();
        S.pop();

        for (int i = 0; i < graph[v].size(); i++) {
            int cur = graph[v][i];
            if (parent[v] != cur) {
                S.push(cur);
                parent[cur] = v;
            }
        }
    }

    return parent;
}

pair<vector<ll>, vector<int>> getDpDown(vector<int>& parent, vector<vector<int>>& graph) {
    vector<ll> dp(n+1, 0);
    vector<int> dep(n+1, 0);
    stack<pair<int, bool>> S;
    S.push(MP(1, false));

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();

        if(b){
            ll temp = 0;
            int best = 0;

            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                for(int j = 0; j<graph[cur][j]; j++){
                    int m = graph[v][j];
                    if(dp[m] > temp){
                        dp[m] = temp;
                        best = cur;
                    }
                }
            }
            
            dp[v] = temp + w[v];
            dep[v] = best;
        }

        S.push(MP(v,true));
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != parent[v]){
                S.push(MP(cur,false));
            }
        }
    }

    return MP(dp,dep);
}

pair<vector<ll>, vector<PII>> getDpUp(vector<int>& parent, vector<vector<int>>& graph, vector<ll> dpDown) {
    vector<ll> dp(n+1, 0);
    vector<PII> dep(n+1, MP(0,0));
    stack<int> S;

    S.push(1);
    dp[1] = w[1];
    while(!S.empty()){
        int v = S.top();
        S.pop();

        //get two best
        vector<pair<ll,int>> best;
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != parent[v]){
                if(best.size() < 2){
                    best.PB(MP(dpDown[cur], cur));
                }else if(best.back().first < dpDown[cur]){
                    best.back().first = dpDown[cur];
                    best.back().second = cur;
                    if(best.back().first > best.front().first){
                        swap(best.front(), best.back());
                    }
                }
            }
        }

        //adding the up
        if(best.size() < 2){
            best.PB(MP(dp[parent[v]], parent[v]));
        }else if(best.back().first < dp[parent[v]]){
            best.back().first = dp[parent[v]];
            best.back().second = parent[v];
            if(best.back().first > best.front().first){
                swap(best.front(), best.back());
            }
        }

        //sum neighbours
        ll sum = 0;
        for(int i = 0; i< graph[v].size(); i++){
            int cur = graph[v][i];
            sum += w[cur];
        }

        //assing best
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != parent[v]){
                if(cur == best.front().second){
                    dp[cur] = best.back().first;
                    dep[cur].first = best.back().second;
                    if(best.back().second == parent[v]){
                        dep[cur].second = 1;
                    }else{
                        dep[cur].second = 0;
                    }
                }else{
                    dp[cur] = best.front().first;
                    dep[cur].first = best.front().second;
                    if(best.front().second == parent[v]){
                        dep[cur].second = 1;
                    }else{
                        dep[cur].second = 0;
                    }
                }
            }
        }
    }

    return MP(dp,dep);
}

tuple<ll, int, vector<int>> solve() {
    // create graph
    vector<vector<int>> graph(n + 1, vector<int>());
    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    vector<int> parent = getParent(graph);

    pair<vector<ll>, vector<int>> dpDown = getDpDown(parent, graph);
    pair<vector<ll>, vector<PII>> dpUp = getDpUp(parent, graph, dpDown.first);

    ll answ = -1;
    int ansVis = 0;
    vector<int> bestVec;
    vector<int> ansTown;
    for(int i = 1; i<=n; i++){
        vector<pair<ll,int>> best;
        for(int j = 0; j<graph[i].size(); j++){
            int cur = graph[i][j];
            if(cur != parent[i]){
                if(best.size() < 2){
                    best.PB(MP(dpDown.first[cur], cur));
                }else if(best.back().first < dpDown.first[cur]){
                    best.back().first = dpDown.first[cur];
                    best.back().second = cur;
                    if(best.back().first > best.front().first){
                        swap(best.front(), best.back());
                    }
                }
            }else{
                if(best.size() < 2){
                    best.PB(MP(dpUp.first[cur], cur));
                }else if(best.back().first < dpUp.first[cur]){
                    best.back().first = dpUp.first[cur];
                    best.back().second = cur;
                    if(best.back().first > best.front().first){
                        swap(best.front(), best.back());
                    }
                }
            }
        }

        if(answ < best.front().first + best.back().first){
            answ = best.front().first + best.back().first;
            bestVec.clear();
            bestVec.PB(i);
            bestVec.PB(best.front().second);
            bestVec.PB(best.back().second);
        }
    }

    // recreate the path
    for(int i = 1; i<bestVec.size(); i++){
        vector<int> temp;
        bool upType = false;  
        if(bestVec[i] == parent[bestVec[0]]) upType = true;

        PII con = MP(bestVec[i],0);
        while(con.first != -1){
            temp.PB(con.first);
            for(int j =0 ; j< graph[con.first].size(); j++){
                int cur = graph[con.first][j];
                if(upType){
                    if(dpUp.second[con.first].second == 0){
                        
                    }else if(dpUp.second[con.first].second == 1){

                    }
                }else{
                    if(dpDown.second[con.first] != cur){
                        temp.PB(cur);
                        temp.PB(con.first);
                    }
                }
            }
            if(upType){ 
                if(){

                }
            }else{
                temp.PB(dpDown.second[con.first]);
                temp.PB(con.first);
            }
        }

        reverse(temp.begin(), temp.end());
        for(int i =0 ; i< temp.size(); i++){
            ansTown.PB(temp[i]);
        }
        ansTown.PB(bestVec[0]);
    }

    return MT(answ, ansVis, ansTown);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for (int test = 1; test <= 1; test++) {
        cout << "TEST nr." << test << " = ";
        if (op == 1) {
            getData();
        } else {
            getRandom();
        }
        tuple<ll, int, vector<int>> ansB = brute();
        tuple<ll, int, vector<int>> ansS = solve();
        bool ok = true;

        if (get<0>(ansB) != get<0>(ansS)) {
            ok = false;
        } else if (get<1>(ansB) != get<1>(ansS)) {
            ok = false;
        } else {
        // vector<int> c = get<2>(ansB);
        // vector<int> d = get<2>(ansS);
        // for(int i = 0; i<c.size(); i++){
        //     if(c[i] !=d[i]){
        //         ok = false;
        //         break;
        //     }
        // }
        }

        if (!ok) {
            cout << "ERROR\n";
            cout << "BURTE: \n";
            ll a = get<0>(ansB);
            int b = get<1>(ansB);
            vector<int> c = get<2>(ansB);
            cout << a << "\n" << b << "\n";
            for (int i = 0; i < c.size(); i++) {
                cout << c[i] << " ";
            }
            cout << "\n";

            cout << "SOLVE: \n";
            a = get<0>(ansS), b = get<1>(ansS), c = get<2>(ansS);
            cout << a << "\n" << b << "\n";
            for (int i = 0; i < c.size(); i++) {
                cout << c[i] << " ";
            }
            cout << "\n";
            printData();
            return 0;
        } else {
            cout << "CORRECT\n";
        }
    }

    return 0;
}