#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 2'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back

int n,m,k,d;
vector<PII> query;

void getData(){
    cin>>n>>m>>k>>d;
    for(int i =0; i<m; i++){
        int r, x;
        cin>>r>>x;
        query.PB(MP(r,x));
    }
}

struct ver{
    ll psoms;
    ll pref;
    ll suf;
    ll sum;
    ver(ll a, ll b, ll c, ll d){
        psoms = a;
        pref = b;
        suf = c;
        sum = d;
    }
};

vector<ver> tree;
int R = 1;
int depth = 0;

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

void update(int r, int x){
    int V = leaf(r);
    tree[V].sum += x;
    tree[V].psoms = max(tree[V].sum, (ll)0);
    tree[V].pref = max(tree[V].sum, (ll)0);
    tree[V].suf = max(tree[V].sum, (ll)0);

    V = parent(V);
    while(V >= 1){
        ver L = tree[left(V)];
        ver R = tree[right(V)];

        tree[V].sum += L.sum + R.sum;
        tree[V].pref = max(L.pref, L.sum + R.pref);
        tree[V].suf = max(L.sum + R.suf, R.suf);
        tree[V].psoms = max(max(L.psoms, R.psoms), L.suf + R.pref);
        V = parent(V);
    }
}

vector<int> solve(){
    tree.clear();
    //initializing the tree
    while((1<<depth) < n){
        R += (1<<depth);
        depth++;
    }
    depth++;
    ll totalSize = (1<<depth) + R;

    tree.assign(totalSize+1, ver(-INF,-INF,-INF,0));

    for(int i = totalSize; i>=1; i--){
        if(i > R){
            tree[i].sum = -k;
            tree[i].psoms = 0; 
            tree[i].pref = 0;
            tree[i].suf = 0;
        }else{
            tree[i].sum = tree[left(i)].sum + tree[right(i)].sum;
        }
    }

    //processing querys
    vector<int> ans;
    for(int i = 0; i<m; i++){
        update(query[i].first, query[i].second);
        if(tree[1].psoms <= d*k){
            ans.PB(1);
        }else{
            ans.PB(0);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    vector<int> ansS = solve();
    for(int j =0 ;j<ansS.size(); j++){
        if(ansS[j] == 0){
            cout<<"NIE\n";
        }else{
            cout<<"TAK\n";
        }
    }

    return 0;
}