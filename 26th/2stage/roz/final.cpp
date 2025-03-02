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
int q;
vector<tuple<char,int,int>> query;

void getData(){
    cin>>M;
    cin>>q;
    for(int i = 0; i<q; i++){
        char t;
        cin>>t;
        int a, b = -INF;
        if(t == 'd'){
            cin>>a;
        }else if(t == 'k'){
            cin>>a>>b;
        }else if(t == 's'){
            cin>>a;
        }
        query.PB(MT(t,a,b));
    }
}

void getRandom(){
    srand(time(0));
    M = rand()%10+1;
    q = rand()%10+1;
    int totalSize = 0;
    for(int i = 0; i<q; i++){
        char t;
        int temp = rand()%3;
        if(temp == 0 || totalSize < 2){
            t = 'd';
        }else if(temp == 1){
            t = 'k';
        }else if(temp == 2){
            t = 's';
        }
        int a, b = -INF;
        if(t == 'd'){
            a = rand()%10+1;
            totalSize++;
        }else if(t == 'k'){
            a = rand()%totalSize+1;
            b = rand()%10+1;
        }else if(t == 's'){
            a = rand()%totalSize+1;
        }
        query.PB(MT(t,a,b));
    }
    query.PB(MT('s', totalSize, -INF));
}

void printData(){
    cout<<"DATA:\n";
    cout<<M<<"\n";
    cout<<q<<"\n";
    for(int i =0 ;i<q; i++){
        char t = get<0>(query[i]);
        int a = get<1>(query[i]), b = get<2>(query[i]);
        cout<<t<<" "<<a<<" "<<b<<"\n";
    }
}

vector<ll> tree;
ll R;
ll ptrEnd;

void inicjuj(int m){
    M = m;

    R = 0;
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

void updateSingle(int p, int val){
    int v = leaf(p);
    tree[v] += val;
    v = parent(v);
    
    while(v>=1){
        tree[v] += val;
        v = parent(v);
    }
}

ll queryRange(int l, int r){
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
    if(i <= ptrEnd+1){
        ans = queryRange(ptrEnd-(i-1), ptrEnd);
    }else{
        ll temp1 = queryRange(0, ptrEnd), temp2 = queryRange(M-(i-(ptrEnd+1)), M-1);
        ans = temp1 + temp2;
    }
    return ans;
}

vector<ll> solve(){
    inicjuj(M);

    vector<ll> ans;
    for(int i = 0; i<q; i++){
        char t = get<0>(query[i]);
        int a = get<1>(query[i]), b = get<2>(query[i]);
        if(t == 'd'){
            dodaj(a);
        }else if(t == 'k'){
            koryguj(a,b);
        }else if(t == 's'){
            ll temp = suma(a);
            ans.PB(temp);
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<ll> ansS = solve();
        for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<" ";
    }

    return 0;
}