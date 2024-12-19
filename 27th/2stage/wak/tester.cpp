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

pair<ll, vector<int>> bruteRecDfs(int v, int type, vector<bool> used, vector<int> moves, vector<vector<int>>& graph) {
    moves.PB(v);
    used[v] = true;

    pair<ll, vector<int>> ans = MP(0, vector<int>());
    if (type == 0) {
        for (int i = 0; i < graph[v].size(); i++) {
            int cur = graph[v][i];
            if (!used[cur]) {
                pair<ll, vector<int>> temp = bruteRecDfs(cur, 1, used, moves, graph);
                if (temp.first > ans.first) {
                ans = temp;
                }
            }
        }
    } else {
        for (int i = 0; i < graph[v].size(); i++) {
            int cur = graph[v][i];
            pair<ll, vector<int>> temp = bruteRecDfs(cur, 0, used, moves, graph);
        }
    }

    ans.first += w[v];
    ans.second.PB(v);

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
        vector<bool> used(n + 1, false);
        pair<ll, vector<int>> temp = bruteRecDfs(i, 1, used, vector<int>(), graph);
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

pair<vector<ll>, vector<int>> getDpDown() {}

pair<vector<ll>, vector<int>> getDpUp() {}

tuple<ll, int, vector<int>> solve() {
    // create graph
    vector<vector<int>> graph(n + 1, vector<int>());
    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    vector<int> parent = getParent(graph);

    pair<vector<ll>, vector<int>> dpDown = getDpDown();
    pair<vector<ll>, vector<int>> dpUp = getDpUp();

    ll answ = -1;
    int ansVis = 0;
    vector<int> ansTown;
    bool upTypeAns = false;
    pair<int, int> marked;
    for (int i = 1; i <= n; i++) {
        ll sumNeigh = 0;
        for (int j = 0; j < graph[i].size(); j++) {
            int cur = graph[i][j];
            sumNeigh += w[cur];
        }

        vector<int> best;
        ll tempAns = 0;
        for (int j = 0; j < graph[i].size(); j++) {
            int cur = graph[i][j];
            if (cur != parent[i]) {
                if (best.size() < 2) {
                    best.PB(cur);
                } else {
                    if (dpDown.first[best.back()] < dpDown.first[cur]) {
                        dpDown.first.back() = cur;
                    }
                    if (best.front() < best.back()) {
                        swap(best.front(), best.back());
                    }
                }
            }

            bool upType = false;
            if (best.back() < dpUp.first[parent[i]]) {
                upType = true;
                dpDown.first.back() = parent[i];
            }

            ll temp = sumNeigh - w[best.front()] - w[best.back()];
            temp += dpDown.first[best.front()];
            if (upType) {
                temp += dpUp.first[best.back()];
            } else {
                temp += dpDown.first[best.back()];
            }

            if (temp > answ) {
                answ = temp;
                upTypeAns = upType;
                marked = MP(best.front(), best.back());
            }
        }
    }

    // recreate the path
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