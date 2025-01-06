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

int n, k;
vector<int> D;
int q;
vector<tuple<int,int,int>> query;

void getData(){
    D.clear(); query.clear();

    cin>>n>>k;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        D.PB(temp);
    }
    cin>>q;
    for(int i =0 ; i<q; i++){
        int t, a, b;
        cin>>t>>a>>b;
        query.PB(MT(t,a,b));
    }
}

void getRandom(){
    D.clear(); query.clear();

    srand(time(0));

    n = 4;
    k = rand()%10+1;
    for(int i =0 ; i<n; i++){
        int temp = rand()%10+1;
        D.PB(temp);
    }

    q = rand()%10+1;
    for(int i =0 ; i<q; i++){
        int t =rand()%2+1;
        int a = rand()%n, b= rand()%n;
        if(a > b){
            swap(a,b);
        }
        query.PB(MT(t,a,b));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<k<<"\n";
    for(int i = 0; i<D.size(); i++){
        cout<<D[i]<<" ";
    }
    cout<<"\n";
    cout<<q<<"\n";
    for(int i =0; i<query.size(); i++){
        cout<<get<0>(query[i])<<" "<<get<1>(query[i])<<" "<<get<2>(query[i])<<"\n";
    }
}

vector<ll> brute(){
    vector<ll> ans;
    vector<int> Dcopy = D;
    for(int i = 0; i<q; i++){
        int t = get<0>(query[i]), a = get<1>(query[i]), b = get<2>(query[i]);
        if(t == 0){//podlej
            for(int i = a; i<= b; i++){
                Dcopy[i]++;
            }
        }else{ //dojrzale
            ll count = 0;
            for(int i = a; i<=b; i++){
                if(Dcopy[i] >= k){
                    count++;
                }
            }
            ans.PB(count);
        }
    }
    return ans;
}

int N, K;
vector<int> t;

vector<ll> treeMarked;
ll RM;

vector<PLL> treeWater;
ll RW;

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
    while((1<<depth) < n){
        RM += (1<<depth);
        depth++;
    }

    treeMarked.assign(RM + (1<<depth) + 1, 0);
}

void updateTW(int v){
    if(v <= RW){
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
    while((1<<depth) < n){
        RW += (1<<depth);
        depth++;
    }

    treeWater.assign(RW + (1<<depth) + 1, MP(0,0));

    //intialize the tree
    for(int i = 0; i<t.size(); i++){
        treeWater[leaf(i,RW)] = MP(t[i], i);
    }

    for(int i = RW; i>=1; i--){
        updateTW(i);
    }
}

void inicjuj()
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

    if(vL<=l && r<=vR){
        treeWater[v].first += val;
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

void podlej(int a, int b)
{
    //range add 1
    addTW(1, a, b, 0, n, 1);

    //update tree marked
    while(treeWater[1].first >= K){
        updateTM(treeWater[1].second);
        int V = leaf(treeWater[1].second, RW);
        treeWater[V].first = -INF;
        while(V >= 1){
            updateTW(V);
        }
    }
}

int dojrzale(int a, int b){
   int ans = 0;
   
   int vA = leaf(a,RM);
   int vB = leaf(b,RM);

    ans += treeMarked[vA];
    if(vA != vB){
        ans += treeMarked[vB];
    }
    
    while(parent(vA) != parent(vB)){
        if(left(parent(vA)) == vA){
            ans += right(parent(vA));
        }
        if(right(parent(vB)) == vB){
            ans += left(parent(vA));
        }
        vA = parent(vA);
        vB = parent(vB);
    }

    return ans;
}

vector<ll> solve(){
    vector<ll> ans;
    inicjuj();
    for(int i = 0; i<q; i++){
        int t = get<0>(query[i]), a = get<1>(query[i]), b = get<2>(query[i]);
        if(t == 0){//podlej
            podlej(a,b);
        }else{ //dojrzale
            ll count = dojrzale(a,b);
            ans.PB(count);
        }
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<"=";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<ll> ansB = brute();
        vector<ll> ansS = solve();
        for(int i = 0; i< ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE:";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }
    return 0;
}