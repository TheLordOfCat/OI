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
ll totalSize;
vector<pair<ll,ll>> difTree;
vector<ll> changeTree;

int leaf(int v){
    return v + R;
}

int parent(int v){
    return v/2;
}

int left(int v){
    return v*2;
}

int right(int v){
    return v*2+1;
}

void updateNode(int v){
    if(difTree[left(v)].first >= 0){
        difTree[v] = difTree[left(v)];
    }else{
        if(difTree[left(v)].first >= difTree[right(v)].first){
            difTree[v] = difTree[left(v)];
        }else{
            difTree[v] = difTree[right(v)];
        }
    } 
}

void lazyUpadte(int v){
    if(changeTree[v] != 0){
        difTree[v].first += changeTree[v];
        if(v <= R){
            changeTree[left(v)] += changeTree[v];
            changeTree[right(v)] += changeTree[v];
        }
        changeTree[v] = 0;
    }
}

void updateSingle(int v, ll val){
    int V = leaf(v);
    difTree[V] = MP(val,-1);
    V = parent(V);

    while(V >= 1){
        if(v <= R){
            lazyUpadte(left(V));
            lazyUpadte(right(V));
        }
        updateNode(V);
        V = parent(V);
    }
    lazyUpadte(1);
}

void updateRange(int l, int r, int val){
    int vl = leaf(l);
    int vr = leaf(r);
    changeTree[vl] += val;
    lazyUpadte(vl);
    if(vl != vr){
        changeTree[vr] += val;
        lazyUpadte(vr);
    }

    while(parent(vl) != parent(vr)){
        if(vl == left(parent(vl))){
            changeTree[right(parent(vl))] += val;
            lazyUpadte(right(parent(vl)));
        }
        if(vr == right(parent(vr))){
            changeTree[left(parent(vr))] += val;
            lazyUpadte(left(parent(vr)));
        }

        if(vl <= R && vr <= R){
            updateNode(vl);
            updateNode(vr);
        }
        lazyUpadte(vl);
        lazyUpadte(vr);

        vl = parent(vl);
        vr = parent(vr);
    }

    lazyUpadte(vl);
    lazyUpadte(vr);
    if(vl <= R && vr <= R){
        updateNode(vl);
        updateNode(vr);
    }

    int V = parent(vl);
    while(V >= 1){
        lazyUpadte(V);
        updateNode(V);
        V = parent(V);
    }
}

pair<ll,ll> getRange(int l, int r, int lb, int rb, int v){
    if(l > r) return MP(-llINF, -1);

    lazyUpadte(v);
    
    if(l == lb && r == rb){
        return difTree[v];
    }else{
        int mb = (lb+rb)/2;
        pair<ll,ll> pl = getRange(l, min(r,mb), lb, mb, left(v));
        pair<ll,ll> pr = getRange(max(l,mb+1), r, mb+1, rb, right(v));

        if(pl.first >= pr.first){
            return pl;
        }else{
            return pr;
        }
    }
}

vector<ll> solve() {
    changeTree.clear();
    difTree.clear();
    
    //prepare the tree
    R = 1;
    depth = 1;
    while(1<<(depth) < n){
        R += 1<<depth;
        depth++;
    } 
    totalSize = R + (1<<depth);

    //geting the s vector
    vector<ll> s;
    ll sum = 0;
    for(int i = w.size()-1; i>= 0; i--){
        s.PB(w[i]-sum);
        sum += w[i];
    }

    reverse(s.begin(),s.end());

    //create seg trees
    changeTree.assign(totalSize+1, 0);
    difTree.assign(totalSize+1, MP(-llINF,-1));
    
    for(int i = totalSize; i>=1; i--){
        if(i > R && i <= R+n){
            difTree[i] = MP(s[i-R-1],i);
        }else if(i <= R){
            updateNode(i);
        }
    }

    //get ans
    vector<ll> ans;
    ans.PB(sum);
    for(int i = 1; i<n; i++){
        pair<ull,ull> p = getRange(1, n, 1, totalSize - R, 1);
        ll ind = p.second-R-1;
        sum -= w[ind];
        ans.PB(sum);
        updateSingle(ind+1, -llINF);
        updateRange(1, ind, w[ind]);
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
