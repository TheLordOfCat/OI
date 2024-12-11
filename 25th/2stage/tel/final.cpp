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
    tree.assign(R+(1<<depth), 0);
    seq.assign(R+(1<<depth), MP(0,0));
}

ll updateReq(int v, int l, int r, int mL, int mR, int s, int a){
    if(mR < l || mL > r){
        return 0;
    }

    if(l >= mL && mR <= r){
        int len = mR-mL+1;
        ll change = ((s + (s+a*(len-1)))/2)*len;
        tree[v] += change;
        seq[left(v)] = MP(s,a);
        seq[right(v)] = MP(s+a*(len-1), a);
        return change;
    }else{
        int len = mR-mL+1;
        ll change = 0;
        change += updateReq(left(v), l, r, mL, mL+len/2, s, a);
        change += updateReq(right(v), l, r, mL+len/2+1, mR, s+a*(len/2+1), a);
        tree[v] += change;
        return change;
    }
}

void updateSeq(int l, int r, int s, int a){
    updateReq(1, l, r, 1, n, s, a);
}

ll queryRec(int v, int l, int r, int mL, int mR){
    if(mR < l || mL > r){
        return 0;
    }

    int s = seq[v].first, a = seq[v].second;
    int len = mR-mL+1;
    tree[v] += ((s + (s+a*(len-1)))/2)*len;
    if(v < R){
        seq[left(v)] += seq[v];
        seq[right(v)] += seq[v];
        seq[v] = MP(0,0);
    }

    if(l <= mL && mR <= r){
        return tree[v];
    }else{
        ll change = 0;
        change += queryRec(left(v), l, r, mL, mL+len/2);
        change += queryRec(right(v), l, r, mL+len/2+1, mR);
        return change;
    }
}

ll query(int l, int r){
    return queryRec(1,l,r,1,n);
}

vector<ll> solve(){
    vector<PII> poles(n+1, MP(0,0));
    vector<ll> ans;

    for(int i =0 ; i<m; i++){
        char type = get<0>(promts[i]);
        if(type == 'P'){
            int x = get<1>(promts[i]), s = get<2>(promts[i]), a = get<3>(promts[i]);
            poles[x] = MP(s,a);
            int left = x-s/a, right = x+s/a;
            if(s%a != 0){
                left--;
                right++;
            }

            updateSeq(left, x, a, a);
            updateSeq(x+1, right, s-a, (-1)*a);
        }
        if(type == 'U'){
            int x = get<1>(promts[i]);
            int s = poles[x].first, a = poles[x].second;

            int left = x-s/a, right = x+s/a;
            if(s%a != 0){
                left--;
                right++;
            }

            updateSeq(left, x, (-1)*a, (-1)*a);
            updateSeq(x+1, right, (-1)*(s-a), a);
        }
        if(type =='Z'){
            int x1 = get<1>(promts[i]), x2 = get<2>(promts[i]);
            int sum = query(x1,x2);
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