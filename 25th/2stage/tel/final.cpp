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
#define MT make_tuple
#define PB push_back

int n, m;
vector<tuple<char,int,int,int>> promts;

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

PII& operator+=(PII& lhs, const PII& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

vector<ll> tree;
vector<PII> seq;
int R;

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
    return R+v;
}

void buildTree(){
    R = 0;
    int depth = 0;
    while((1<<depth) < n){
        R += 1<<depth;
        depth++;
    }
    tree.assign(R+(1<<depth)+1, 0);
    seq.assign(R+(1<<depth)+1, MP(0,0));
}

ll updateReq(int v, int l, int r, int mL, int mR, int s, int a){
    if(mR < l || mL > r){
        return 0;
    }

    if(l <= mL && mR <= r){
        ll len = mR-mL+1;
        ll start = s + a*(mL-l), end = s + a*(mR-l);
        ll change = ((start + end)*len/2);
        tree[v] += change;
        if(v <= R){
            seq[left(v)] += MP(start,a);
            ll temp = start+a*(len/2);
            seq[right(v)] += MP(temp, a);
        }
        return change;
    }else{
        int len = mR-mL+1;
        ll change = 0;
        if(v <= R){
            int mid = mL+len/2-1;
            change += updateReq(left(v), l, r, mL, mid, s, a);
            change += updateReq(right(v), l, r, mid+1, mR, s, a);
        }
        tree[v] += change;
        return change;
    }
}

void updateSeq(int l, int r, int s, int a){
    updateReq(1, l, r, 1, R+1, s, a);
}

ll queryRec(int v, int l, int r, int mL, int mR){
    if(mR < l || mL > r){
        return 0;
    }

    int s = seq[v].first, a = seq[v].second;
    ll len = mR-mL+1;
    ll start = s, end = s + a*(len-1);
    ll change = ((start + end)*len/2);
    tree[v] += change;
    if(v <= R){
        seq[left(v)] += MP(s,a);
        seq[right(v)] += MP(s+a*(len/2), a);
    }
    seq[v] = MP(0,0);

    if(l <= mL && mR <= r){
        return tree[v];
    }else{
        change = 0;
        if(v <= R){
            int mid = mL+len/2-1;
            change += queryRec(left(v), l, r, mL, mid);
            change += queryRec(right(v), l, r, mid+1, mR);
        }
        return change;
    }
}

ll query(int l, int r){
    return queryRec(1,l,r,1,R+1);
}

vector<ll> solve(){
    vector<PII> poles(n+1, MP(0,0));
    vector<ll> ans;
    buildTree();

    for(int i =0 ; i<m; i++){
        char type = get<0>(promts[i]);
        if(type == 'P'){
            int x = get<1>(promts[i]), s = get<2>(promts[i]), a = get<3>(promts[i]);
            poles[x] = MP(s,a);
            int left = max(x-s/a,1), right = x+s/a;
            right = min(right,n);
            ll leftVal = s-(x-left)*a;

            updateSeq(left, x, leftVal, a);
            updateSeq(x+1, right, s-a, (-1)*a);
        }
        if(type == 'U'){
            int x = get<1>(promts[i]);
            int s = poles[x].first, a = poles[x].second;

            int left = max(x-s/a,1), right = x+s/a;
            right = min(right,n);
            ll leftVal = s-(x-left)*a;

            updateSeq(left, x, leftVal*(-1), (-1)*a);
            updateSeq(x+1, right, (-1)*(s-a), a);
        }
        if(type =='Z'){
            int x1 = get<1>(promts[i]), x2 = get<2>(promts[i]);
            ll sum = query(x1,x2);
            ans.PB(sum/(x2-x1+1));
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