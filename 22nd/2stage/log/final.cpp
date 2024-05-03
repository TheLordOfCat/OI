#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

using ll = long long int;

const int MAXN = 1'000'000;
const int MAXM = 1'000'000;

pair<int, ll> operator + (const pair<int, ll>& a, const pair<int, ll> b)
{
	return MP(a.first + b.first, a.second + b.second);
}

int n, m;
vector<pair<char,pair<int,ll>>> request;

void getData(){
    cin>>n>>m;
    for(int i =0; i <m; i++){
        char c;
        int a;
        ll b;
        cin>>c;
        cin>>a>>b;
        request.PB(MP(c,MP(a,b)));
    }
} 

pair<int,ll> tree[4*MAXN+1];
int val[MAXN+1];
int license[MAXN+1];
int R = 1;
int depth = 1;

int parent(int v){
    return v/2;
}

int left(int v){
    return 2*v;
}

int right(int v){
    return 2*v+1;
}

int leaf(int v){
    return R+1+v;
}

void update(int v, pair<int,ll> change){
    int V = leaf(v);
    tree[V] = tree[V] + change;
    while(V > 1){
        V = parent(V);
        tree[V] = tree[left(V)] + tree[right(V)];
    }
}

int findPos(ll value){
    int b = 0, e = m;
    while(b < e){
        int mid = (b+e)/2;
        if(val[mid] >= value){
            e = mid;
        }else{
            b = mid+1;
        }
    }
    return b;
}

ll rangeSum( ll s){
    int v = findPos(s);
    ll sum = 0;
    int l = leaf(0);
    int r = leaf(v);
    sum += tree[l].second;
    if(l != r) sum += tree[r].second;
    while(parent(l) != parent(r)){
        if(left(parent(l)) == l){
            sum += tree[right(parent(l))].second;
        }
        if(right(parent(r)) == r){
            sum += tree[left(parent(r))].second;
        }
        l = parent(l);
        r = parent(r);
    }
    l = leaf(v+1);
    r = leaf(m);
    sum += tree[l].second;
    if(l != r) sum += tree[r].second;
    while(parent(l) != parent(r)){
        if(left(parent(l)) == l){
            sum += (ll)tree[right(parent(l))].first * s;
        }
        if(right(parent(r)) == r){
            sum += (ll)tree[left(parent(r))].first * s;
        }
        l = parent(l);
        r = parent(r);
    }
    return sum;
}

vector<bool> solve(){
    //prepare the tree
    for(int i =0 ; i<m; i++){
        val[i] = request[i].second.second;
    }
    
    while(1<<depth < m){
        R += 1<<depth;
        depth++;
    }

    //procesing requests
    vector<bool> ans;
    sort(val, val+m);

    for(int i = 0; i<m; i++){
        if(request[i].first == 'U'){
            pair<int,ll> cur = request[i].second;

            if(license[cur.first] != 0){
                update(findPos(license[cur.first]), MP(-1, -license[cur.first]));
            }
            license[cur.first] = cur.second;
            update(findPos(license[cur.first]), MP(1, license[cur.first]));
        }else if(request[i].first == 'Z'){
            pair<int,ll> cur = request[i].second;

            ll sum = rangeSum(cur.second);
            if(sum >= (ll)cur.first * cur.second ){
                ans.PB(true);
            }else{
                ans.PB(false);
            }
        }
    }
    return ans;
}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    vector<bool> ansS = solve();
    for(int j = 0; j<ansS.size(); j++){
        if(ansS[j]){
            cout<<"TAK\n";
        }else{
            cout<<"NIE\n";
        }
    }

    return 0;
}