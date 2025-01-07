#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

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
vector<tuple<char,int,int>> query;

void getData(){
    D.clear(); query.clear();

    if(1){
        n = 0;
        ifstream inputFile("kon1ocen.txt");
        string line;

        getline(inputFile, line);
        istringstream iss1(line); // Treat the line as a stream
        int number;

        while (iss1 >> number) { // Extract numbers from the line
            if(n == 0){
                n = number;
            }else{
                k = number;
            }
        }

        getline(inputFile, line);
        istringstream iss2(line); // Treat the line as a stream

        while (iss2 >> number) { // Extract numbers from the line
            D.push_back(number);
        }

        inputFile>>q;

        while (getline(inputFile, line)) { // Read the file line by line
            istringstream iss3(line); // Treat the line as a stream

            if (line.empty()) continue;
            char t; int a, b;
            iss3>>t; iss3>>a; iss3>>b;
            query.PB(MT(t,a,b));
        }

        inputFile.close();
    }else{
        cin>>n>>k;
        for(int i = 0; i<n; i++){
            int temp;
            cin>>temp;
            D.PB(temp);
        }
        cin>>q;
        for(int i =0 ; i<q; i++){
            char t;
            int a, b;
            cin>>t>>a>>b;
            query.PB(MT(t,a,b));
        }
    }
}

void getRandom(){
    D.clear(); query.clear();

    srand(time(0));

    // n = rand()%100+20;
    n = 2000;
    // k = rand()%50+15;
    k = 100;
    for(int i =0 ; i<n; i++){
        int temp = rand()%100+5;
        D.PB(temp);
    }

    // q = rand()%10+1;
    q = 10000;
    for(int i =0 ; i<q; i++){
        int t =rand()%2+1;
        int a = rand()%n, b= rand()%n;
        if(a > b){
            swap(a,b);
        }
        a = b;
        if(t == 0){
            query.PB(MT('p',a,b));
        }else{
            query.PB(MT('d',a,b));
        }
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
        char t = get<0>(query[i]);
        int a = get<1>(query[i]), b = get<2>(query[i]);
        if(t == 'p'){//podlej
            for(int i = a; i<= b; i++){
                Dcopy[i]++;
            }
        }else{ //dojrzale
            ll count = 0;
            for(int j = a; j<=b; j++){
                if(Dcopy[j] >= k){
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
vector<ll> lazy;
ll RW;
ll bottomLevel;

ll left(ll v){
    return v*2;    
}

ll right(ll v){
    return v*2+1;
}

ll leaf(ll v, ll R){
    return v+ R+1;
}

ll parent(ll v){
    return v/2;
}

void updateLazy(ll v){
    if(lazy[v] > 0){
        treeWater[v].first += lazy[v];
        if(v <= RW){
            lazy[left(v)] += lazy[v];
            lazy[right(v)] += lazy[v];
        }
        lazy[v] = 0;
    }
}

void updateTW(ll v){
    if(v <= RW){
        updateLazy(v);
        updateLazy(left(v));
        updateLazy(right(v));
        if(treeWater[left(v)].first >= treeWater[right(v)].first){
            treeWater[v] = treeWater[left(v)];
        }else{
            treeWater[v] = treeWater[right(v)];
        }
    }
}

void updateTM(ll v){
    ll V = leaf(v, RM);
    while(V>=1){
        treeMarked[V] += 1;
        V = parent(V);
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

    treeWater.assign(RW + (1<<depth) + 1, MP(-INF,0));
    lazy.assign(RW + (1<<depth) + 1, 0);
    bottomLevel = (1<<depth);

    //intialize the tree
    for(int i = 0; i<t.size(); i++){
        treeWater[leaf(i,RW)] = MP(t[i], i);
    }

    for(int i = RW; i>=1; i--){
        updateTW(i);
    }
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

void inicjuj()
{
    t.assign(n, 0);
    N = n, K = k;
    for (int i = 0; i < n; i++) t[i] = D[i];

    buildTreeMarked();
    buildTreeWater();
}

void addTW(ll v, ll l, ll r, ll vL, ll vR, ll val){
    if(r < vL || vR < l || r<l){
        return;
    }

    if(l<=vL && vR<=r){
        treeWater[v].first += val;
        lazy[left(v)] += val;
        lazy[right(v)] += val;
    }else{
        ll mid = (vL+vR)/2;
        addTW(left(v), l, r, vL, mid, val);
        addTW(right(v), l, r, mid+1, r, val);
    }
    updateTW(v);
}

void recTW(ll v, ll e, ll l, ll r){
    if(r < e || e < l){
        return;
    }
    
    updateLazy(v);

    if(l == r && l == e){
        treeWater[v].first = -INF;
        updateTM(treeWater[v].second);
    }else if(v <= RW){
        ll mid = (l+r)/2;
        recTW(left(v), e, l, mid);
        recTW(right(v), e, mid+1, r);
    }
    updateTW(v);
}

void correctTW(){
    while(treeWater[1].first >= K){
        recTW(1, treeWater[1].second, 0, bottomLevel-1);
    }
}

void podlej(int a, int b)
{
    //range add 1
    addTW(1, a, b, 0, bottomLevel-1, 1);
}

int dojrzale(int a, int b){
    correctTW();
    int ans = 0;
    
    ll vA = leaf(a,RM);
    ll vB = leaf(b,RM);

    ans += treeMarked[vA];
    if(vA != vB){
        ans += treeMarked[vB];
    }
    
    while(parent(vA) != parent(vB)){
        if(left(parent(vA)) == vA){
            ans += treeMarked[right(parent(vA))];
        }
        if(right(parent(vB)) == vB){
            ans += treeMarked[left(parent(vB))];
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
        cout<<i<<"\n";
        char t = get<0>(query[i]);
        int a = get<1>(query[i]), b = get<2>(query[i]);
        if(t == 'p'){//podlej
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
                cout<<"BRUTE: ";
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