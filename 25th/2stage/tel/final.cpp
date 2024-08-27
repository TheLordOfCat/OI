#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const int llINF = 9'000'000'000'000'000'000;
const int ullINF = 18'000'000'000'000'000'000;

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define MT make_tuple
#define PB push_back

int n, m;
vector<tuple<char,int,int,int>> promts;

PII& operator+=(PII& lhs, const PII& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

pair<ll, ll>& operator+=(pair<ll, ll>& lhs, const pair<ll, ll>& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

void getData(){
    promts.clear();

    cin>>n>>m;
    for(int i =0 ; i<m; i++){
        char t;
        cin>>t;
        int a, b, c;
        if(t == 'P'){
            cin>>a>>b>>c;
        }
        if(t == 'U'){
            cin>>a;
            b = -1; c = -1;
        }
        if(t == 'Z'){
            cin>>a>>b;
            c = -1;
        }

        promts.PB(MT(t,a,b,c));
    }
}

vector<ll> tree;
vector<pair<ll,ll>> lazy;
ll R = 0;
int depth = 0;
ll totalSize = 0;

int left(int v){
    return 2*v;
}

int right(int v){
    return 2*v+1;
}

int leaf(int v){
    return R+v;
}

int parent(int v){
    return v/2;
}

void upateTree(int v, int tl, int tr, int l, int r, ll s, ll a){
    if(l > r || tl > r || tr < l) return;

    int mid = (tl+tr)/2;
    if(tl == l && tr == r){
        if(v < R){
            lazy[left(v)] += MP(s,a);
            lazy[right(v)] += MP(s+(a*(mid-l+1)), a);
        }

        ll sum = 0;
        for(ll i = 0; i<(tr-tl+1); i++){
            sum += s+ a*i;
        }
        tree[v] += sum;
    }else{
        upateTree(left(v), tl, mid, l, min(r, mid), s, a);   
        if(mid >= l){
            upateTree(right(v), mid+1, tr, max(l, mid+1), r, s + (mid-l+1)*a, a);   
        }else{
            upateTree(right(v), mid+1, tr, max(l, mid+1), r, s, a);   
        }
        tree[v] = tree[left(v)] + tree[right(v)];
    }
}

ll query(int v, int tl, int tr, int l, int r){
    if(l > r) return 0;
    int mid = (tl+tr)/2;
    if(lazy[v].first != 0 && lazy[v].second != 0){
        ll s = lazy[v].first;
        ll a = lazy[v].second;

        ll sum = 0;
        for(ll i = 0; i<(tr-tl+1); i++){
            sum += s+ a*i;
        }
        tree[v] += sum;

        if(v < R){
            lazy[left(v)] += MP(s,a);
            lazy[right(v)] += MP(s+(a*(mid)), a); 
        }
    }
    lazy[v].first = 0; lazy[v].second = 0;

    if(tl == l && tr == r){
        return tree[v];
    }else{
        return query(left(v), tl, mid, l, min(r, mid)) + query(right(v), mid+1, tr, max(l, mid+1), r);
    }
}

vector<ll> solve(){
    tree.clear();
    lazy.clear();
    R = 0;
    depth = 0;
    totalSize = 0;

    //building the tree
    while((1<<depth) < n){
        R += (1<<depth);
        depth++;
    } 
    totalSize = R + (1<<depth);
    tree.assign(totalSize+1, 0);
    lazy.assign(totalSize+1, MP(0,0));

    //getting the ans
    vector<pair<ll,ll>> poles(n+1, MP(0,0));
    vector<ll> ans;
    for(int i = 0; i<m; i++){
        char t = get<0>(promts[i]);
        int a = get<1>(promts[i]), b = get<2>(promts[i]), c = get<3>(promts[i]); 
        if(t == 'P'){
            ll len = b/c;
            if(b%c == 0){
                len--;
            }
            
            upateTree(1,R+1, totalSize, leaf(a)-len, leaf(a), b-len*c, c);
            upateTree(1,R+1, totalSize, leaf(a)+1, leaf(a)+len, b-c, c*(-1));

            poles[a] = MP(b,c);
        }
        if(t == 'U'){
            b = poles[a].first, c = poles[a].second; 
            ll len = b/c;
            if(b%c == 0){
                len--;
            }
            upateTree(1,R+1, totalSize, leaf(a)-len, leaf(a), (b-len*c)*(-1), c*(-1));
            upateTree(1,R+1, totalSize, leaf(a)+1, leaf(a)+len, b*(-1) + c, c);

            poles[a] = MP(0,0);
        }
        if(t == 'Z'){
            ll temp = query(1,R+1, totalSize, leaf(a), leaf(b));
            ans.PB(temp/(b-a+1));
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<ll> ansS = solve();
    for(int o = 0; o<ansS.size(); o++){
        cout<<ansS[o]<<"\n";
    }

    return 0;
}