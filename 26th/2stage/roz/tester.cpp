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
    query.clear();
    srand(time(0));
    // M = rand()%1000+100;
    M = 30;
    // q = rand()%100+50;
    q = 50;
    int totalSize = 0;
    for(int i = 0; i<q-1; i++){
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
            a = rand()%1000+1;
            totalSize++;
            if(totalSize > M) totalSize = M;
        }else if(t == 'k'){
            a = rand()%totalSize+1;
            b = rand()%1000+1;
        }else if(t == 's'){
            a = rand()%M+1;
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

vector<ll> brute(){
    vector<ll> vec;

    vector<ll> ans;
    int curM = -1;
    for(int i = 0; i<q; i++){
        char t = get<0>(query[i]); 
        int a = get<1>(query[i]), b = get<2>(query[i]);
        if(t == 'd'){
            vec.PB(a);
            curM++;
        }else if(t == 'k'){
            vec[curM-(a-1)] += b;
        }else if(t == 's'){
            ll count = 0;
            for(int j = max(curM-(a-1), 0); j<=curM; j++){
                count += vec[j];
            }
            ans.PB(count);
        }
    }

    return ans;
}

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

    int op = 0;
    for(int test = 1; test<=100'000'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<ll> ansB = brute();
        vector<ll> ansS = solve();
        for(int i =0 ; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++) cout<<ansB[j]<<" ";
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<" ";
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}