#include <iostream>
#include <vector>

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
        if(temp == 0){
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
}

void printData(){
    cout<<"DATA:\n";
    cout<<M<<"\n";
}

vector<ll> brute(){
    vector<ll> vec;

    vector<ll> ans;
    for(int i = 0; i<q; i++){
        char t = get<0>(query[i]); 
        int a = get<1>(query[i]), b = get<1>(query[i]);
        if(t == 'd'){
            vec.PB(a);
        }else if(t == 'k'){
            vec[vec.size()-a] += b;
        }else if(t == 's'){
            ll count = 0;
            for(int i = vec.size()-a; i<vec.size(); i++){
                count += vec[i];
            }
            ans.PB(count);
        }
    }

    return ans;
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
    ptrEnd = 0;
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

void updateSingle(int val){
    int v = leaf(ptrEnd);
    int p = tree[v];
    tree[v] = val;
    v = parent(v);
    
    while(v>=1){
        tree[v] -= p;
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
            ans += right(parent(vL));
        }
        if(vR == right(parent(vR))){
            ans += left(parent(vR));
        }
        vL = parent(vL);
        vR = parent(vR);
    }

    return ans;
}

void dodaj(int k){
    updateSingle(k);
}   

void koryguj(int i, int k){

}

long long suma(int i){
    
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