#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define PB push_back
#define PLL pair<ll,ll>
#define MT make_tuple

int M;

vector<ll> tree;
ll R;
ll ptrEnd;
ll totalSize;

void inicjuj(int m){
    M = m;

    R = 0;
    totalSize =0;
    int depth = 0;
    while((1<<depth) < M){
        R += (1<<depth);
        depth++;
    }
    tree.assign(R + (1<<depth)+1, 0);
    ptrEnd = -1;
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

int leaf(int v){
    return v+R+1;
}

void updateSingle(int p, ll val){
    int v = leaf(p);
    tree[v] += val;
    v = parent(v);
    
    while(v>=1){
        tree[v] += val;
        v = parent(v);
    }
}

ll queryRange(int l, int r){
    if(l == -1 || r == -1 || r<l) return 0;
    ll ans = 0;
    int vL = leaf(l), vR = leaf(r);

    ans += tree[vL];
    if(vL != vR) ans += tree[vR];

    while(parent(vL) != parent(vR)){
        if(vL == left(parent(vL))){
            ans += tree[right(parent(vL))];
        }
        if(vR == right(parent(vR))){
            ans += tree[left(parent(vR))];
        }
        vL = parent(vL);
        vR = parent(vR);
    }

    return ans;
}

void dodaj(int k){
    ptrEnd = (ptrEnd+1)%M;
    totalSize++;
    if(totalSize > M) totalSize = M;
    updateSingle(ptrEnd, tree[leaf(ptrEnd)]*(-1));
    updateSingle(ptrEnd, k);
}   

void koryguj(int i, int k){
    if(i <= ptrEnd+1){ // no wrapping
        updateSingle(ptrEnd-(i-1), k);
    }else{
        updateSingle(M-(i-ptrEnd-1), k);
    }
}

long long suma(int i){
    ll ans;
    if(i > totalSize){
        i = totalSize;
    }
    if(i <= ptrEnd+1){
        ans = queryRange(ptrEnd-(i-1), ptrEnd);
    }else{
        ll temp1 = queryRange(0, ptrEnd), temp2 = queryRange(M-(i-(ptrEnd+1)), M-1);
        ans = temp1 + temp2;
    }
    return ans;
}