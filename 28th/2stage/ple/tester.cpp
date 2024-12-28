#include <iostream>
#include <stack>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int, int>
#define MP make_pair
#define PB push_back
#define PLL pair<ll,ll>

int n;
vector<ull> w;

void getData() {
    w.clear();

    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        w.PB(temp);
    }
}

void getRandom() {
    w.clear();

    srand(time(0));
    
    n = rand() % 10 + 1;
    // n = 8;
    for (int i = 0; i < n; i++) {
        ull temp = rand() % 300 + 10;
        w.PB(temp);
    }
}

void printData() {
    cout << "DATA: \n";
    cout << n << "\n";
    for (int i = 0; i < w.size(); i++) {
        cout << w[i] << " ";
    }
    cout << "\n";
}

vector<vector<ll>> bruteUsed;

vector<ll> brute() {
    vector<ll> ans;
    vector<vector<ll>> used;

    ll sumTotal = 0;
    for(int i =0; i<w.size(); i++){
        sumTotal += w[i];
    }

    int lastCount = 0;
    for(ll i = 1; i<= sumTotal; i++){
        //simulate
        int count = 0;
        ll sum = i;
        vector<ll> temp;
        for(int j = 0; j< w.size(); j++){
            if(w[j] <= sum){
                count++;
                sum -= w[j];
                temp.PB(j);
            }
        }
        if(count > lastCount){
            ans.PB(i);
            bruteUsed.PB(temp);
            lastCount = count;
        }
    }

    return ans;
}

ll R;
ll depth;
vector<PLL> segTree;
vector<ll> lazy;

ll left(ll v){
    return v*2;
}

ll right(ll v){
    return v*2+1;
}

ll parent(ll v){
    return v/2;
}

ll leaf(ll v){
    return R+v+1;
}

void updateLazy(ll v){
    if(lazy[v] != 0){
        segTree[v].first += lazy[v];
        if(v < R){
            lazy[left(v)] += lazy[v];
            lazy[right(v)] += lazy[v];
        }
        lazy[v] = 0;
    }
}

void updateVer(ll v){
    if(v > R){
        return;
    }

    updateLazy(v);
    updateLazy(left(v));
    updateLazy(right(v));

    if(segTree[left(v)].first <= 0){
        if(segTree[left(v)].first >= segTree[right(v)].first){
            segTree[v] = segTree[left(v)];
        }else{
            segTree[v] = segTree[right(v)];
        }
    }else if(segTree[left(v)].first > 0){
        segTree[v] = segTree[left(v)];
    }
}

void buildTree(){
    segTree.clear();
    lazy.clear();

    R = 0;
    depth = 0;

    while(1<<depth < n){
        R += (1<<depth);
        depth++;
    }

    segTree.assign(R+(1<<depth)+1, MP(-llINF, -1));
    lazy.assign(R+(1<<depth)+1, 0);

    ll sum = 0;
    for(int i = w.size()-1; i>=0; i--){
        ll v = leaf(i);
        segTree[v] = MP(w[i]-sum,i);
        sum += w[i];
    }

    for(int i = R; i>=1; i--){
        updateVer(i);
    }
}

void recAdd(ll v, ll l, ll r, ll tL, ll tR, ll val){
    if(r < tL || l > tR || r < l){
        return;
    }

    updateLazy(v);

    if(tL <= l && r <= tR){
        segTree[v].first += val;
        if(v < R){
            lazy[left(v)] += val;
            lazy[right(v)] += val;
        }
    }else if(v <= R){
        ll mid = (l+r)/2;
        recAdd(left(v), l, mid, tL, tR, val);
        recAdd(right(v), mid+1, r, tL, tR, val);
    }
    updateVer(v);
}

void addRange(ll vL, ll vR, ll val){
    recAdd(1, 0, (1<<depth)-1, vL, vR, val);
}

void updateSingle(ll v, ll val){
    ll V = leaf(v);

    if(lazy[V] != 0){
        segTree[V].first += lazy[V];
        lazy[V] = 0;
    }
    segTree[V].first += val;
    V = parent(V);
    while(V >= 1){
        updateVer(V);
        V = parent(V);
    }
}

PLL findBest(ll v){
    if(v > R){
        return segTree[v];
    }
    updateVer(v);
    if(segTree[left(v)].first > 0){
        return findBest(left(v));
    }else{
        return findBest(right(v));
    }
}

vector<ll> solveUsed;

vector<ll> solve(){
    vector<ll> ans;
    
    ll sum = 0;
    for(int i =0 ; i<w.size(); i++){
        sum += w[i];
    }

    buildTree();

    for(int i = 0; i<w.size(); i++){
        PLL v = findBest(1);
        ans.PB(sum);
        sum -= w[v.second];
        solveUsed.PB(v.second);
        updateSingle(v.second, -llINF);
        addRange(0, v.second-1, w[v.second]);
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for (int test = 1; test <= 100000; test++) {
        bruteUsed.clear(); solveUsed.clear();
        cout << "TEST nr." << test << " = ";
        if (op == 1) {
            getData();
        } else {
            getRandom();
        }
        vector<ll> ansB = brute();
        vector<ll> ansS = solve();
        for (int i = 0; i < ansB.size(); i++) {
            if (ansB[i] != ansS[i]) {
                cout << "ERROR\n";
                printData();
                cout << "BRUTE: \n";
                for (int j = 0; j < ansB.size(); j++) {
                    cout << ansB[j] << " ";
                }
                cout << "\n";
                cout << "SOLVE: \n";
                for (int j = 0; j < ansS.size(); j++) {
                    cout << ansS[j] << " ";
                }
                cout << "\n";
                cout<<i<<" - ";
                for(int j = 0; j<bruteUsed[i].size(); j++){
                    cout<<bruteUsed[i][j]<<" ";
                }
                cout<<"\n";
                return 0;
            }
        }
        cout << "CORRECT\n";
    }

    return 0;
}
