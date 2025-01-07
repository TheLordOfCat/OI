#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple
#define PLL pair<ll,ll>

int N, K;
vector<int> t;

vector<ll> treeMarked;
ll RM;

vector<PLL> treeWater;
vector<ll> lazy;
ll RW;
ll bottomLevel;

int left(int v){
    return v*2;    
}

int right(int v){
    return v*2+1;
}

int leaf(int v, ll R){
    return v+ R+1;
}

int parent(int v){
    return v/2;
}

void buildTreeMarked(){
    int depth = 0;
    RM = 0;
    treeMarked.clear();
    while((1<<depth) < N){
        RM += (1<<depth);
        depth++;
    }

    treeMarked.assign(RM + (1<<depth) + 1, 0);
}

void updateLazy(int v){
    if(lazy[v] > 0){
        treeWater[v].first += lazy[v];
        if(v <= RW){
            lazy[left(v)] += lazy[v];
            lazy[right(v)] += lazy[v];
        }
        lazy[v] = 0;
    }
}

void updateTW(ll v){
    updateLazy(v);
    if(v <= RW){
        updateLazy(left(v));
        updateLazy(right(v));
        if(treeWater[left(v)].first >= treeWater[right(v)].first){
            treeWater[v] = treeWater[left(v)];
        }else{
            treeWater[v] = treeWater[right(v)];
        }
    }
}

void buildTreeWater(){
    int depth = 0;
    RW = 0;
    treeWater.clear();
    while((1<<depth) < N){
        RW += (1<<depth);
        depth++;
    }

    treeWater.assign(RW + (1<<depth) + 1, MP(0,0));
    lazy.assign(RW + (1<<depth) + 1, 0);
    bottomLevel = (1<<depth);

    //intialize the tree
    for(int i = 0; i<t.size(); i++){
        treeWater[leaf(i,RW)] = MP(t[i], i);
    }

    for(int i = RW; i>=1; i--){
        updateTW(i);
    }
}

void inicjuj(int n, int k, int *D)
{
    t.assign(n, 0);
    N = n, K = k;
    for (int i = 0; i < n; i++) t[i] = D[i];

    buildTreeMarked();
    buildTreeWater();
}

void addTW(int v, int l, int r, int vL, int vR, int val){
    if(r < vL || vR < l || r<l){
        return;
    }

    if(l<=vL && vR<=r){
        lazy[v] += val;
    }else{
        int mid = (vL+vR)/2;
        addTW(left(v), l, r, vL, mid, val);
        addTW(right(v), l, r, mid+1, r, val);
    }
    updateTW(v);
}

void updateTM(int v){
    int V = leaf(v, RM);
    while(V>=1){
        treeMarked[V] += 1;
        V = parent(V);
    }
}

void recTW(int v, int e, int l, int r){
    if(r < e || e < l){
        return;
    }
    
    updateLazy(v);

    if(l == r && l == e){
        treeWater[v].first = -INF;
        updateTM(treeWater[v].second);
    }else{
        int mid = (l+r)/2;
        recTW(left(v), e, l, mid);
        recTW(right(v), e, mid+1, r);
    }
    updateTW(v);
}

void correctTW(){
    while(treeWater[1].first >= K){
        recTW(1, treeWater[1].second, 0, bottomLevel-1);
    }
}

void podlej(int a, int b)
{
    //range add 1
    addTW(1, a, b, 0, bottomLevel-1, 1);
}

int dojrzale(int a, int b){
    correctTW();
    int ans = 0;
    
    int vA = leaf(a,RM);
    int vB = leaf(b,RM);

    ans += treeMarked[vA];
    if(vA != vB){
        ans += treeMarked[vB];
    }
    
    while(parent(vA) != parent(vB)){
        if(left(parent(vA)) == vA){
            ans += treeMarked[right(parent(vA))];
        }
        if(right(parent(vB)) == vB){
            ans += treeMarked[left(parent(vB))];
        }
        vA = parent(vA);
        vB = parent(vB);
    }

    return ans;
}