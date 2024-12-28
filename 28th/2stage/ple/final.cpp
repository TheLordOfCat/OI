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

ll R;
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

void updateVer(ll v){
    if(v > R){
        return;
    }

    if(segTree[left(v)].first < segTree[right(v)].first){
        segTree[v] = segTree[left(v)];
    }else{
        segTree[v] = segTree[right(v)];
    }
}

void buildTree(){
    segTree.clear();
    lazy.clear();

    int depth = 0;
    while(1<<depth < n){
        R += (1<<depth);
        depth++;
    }

    segTree.assign(R+(1<<depth)+1, MP(0,0));
    lazy.assign(R+(1<<depth)+1, 0);

    for(int i = 0; i<w.size(); i++){
        ll v = leaf(i);
        segTree[v] = MP(w[i],i);
    }

    for(int i = R; i>=1; i--){
        updateVer(i);
    }
}

void updateLazy(ll v){
    if(lazy[v] != 0){
        segTree[v].first += lazy[v];
        if(v < R){
            segTree[left(v)].first += lazy[v];
            segTree[right(v)].first += lazy[v];
        }
        lazy[v] = 0;
    }
}

void recAdd(ll v, ll l, ll r, ll L, ll R, ll val){
    if(r < L || l > R || r < l){
        return;
    }

    updateLazy(v);

    if(L <= l && r <= R){
        segTree[v].first += val;
        if(v < R){
            lazy[left(v)] += val;
            lazy[right(v)] += val;
        }
    }else{
        recAdd(left(v), l, r/2, L, R, val);
        recAdd(right(v), r/2+1, r, L, R, val);
        updateVer(v);
    }
}

void addRange(ll L, ll R, ll val){
    recAdd(1, 1, n, L, R, val);
}

void updateSingle(ll v){
    ll V = leaf(v);

    if(lazy[V] != 0){
        segTree[V].first += lazy[V];
        lazy[V] = 0;
    }
    segTree[V].first = -llINF;
    V = parent(V);
    while(V >= 1){
        updateVer(V);
        updateLazy(V);
        V = parent(V);
    }
}

vector<ll> solveUsed;

vector<ll> solve(){
    vector<ll> ans;
    
    ll sum = 0;
    for(int i =0 ; i<w.size(); i++){
        sum += w[i];
    }

    for(int i = 0; i<w.size(); i++){
        PLL v = segTree[1];
        ans.PB(sum);
        sum -= w[v.second];
        solveUsed.PB(v.second);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<ll> ansS = solve();
    for (int j = 0; j < ansS.size(); j++) {
        cout << ansS[j] << " ";
    }
    cout << "\n";


    return 0;
}
