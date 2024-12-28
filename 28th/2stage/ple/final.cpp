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

    getData();

    vector<ll> ansS = solve();
    for (int j = 0; j < ansS.size(); j++) {
        cout << ansS[j] << " ";
    }
    cout << "\n";

    return 0;
}
