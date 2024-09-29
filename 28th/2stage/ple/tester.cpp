#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int, int>
#define MP make_pair
#define PB push_back

int n;
vector<ull> w;

void getData() {
    w.clear();

    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        w.PB(temp);
    }
}

void getRandom() {
    w.clear();

    n = rand() % 10 + 1;
    for (int i = 0; i < n; i++) {
        ull temp = rand() % 20 + 1;
        w.PB(temp);
    }
}

void printData() {
    cout << "DATA: \n";
    cout << n << "\n";
    for (int i = 0; i < w.size(); i++) {
        cout << w[i] << " ";
    }
    cout << "\n";
}

vector<ll> brute() {
    vector<ll> ans;

    ll sum = 0;
    for (int i = 0; i < w.size(); i++) {
        sum += w[i];
    }

    ll ind = 1;
    for (int i = 1; i <= n; i++) {
        ll left = ind;
        ll count = 0;

        for (int j = 0; j < w.size(); j++) {
            if (count == i) {
                break;
            }
            if (w[j] <= left) {
                left -= w[j];
                count++;
            }
        }

        if (count < i) {
            ind++;
            i--;
        } else {
            ans.PB(ind);
        }
    }

    return ans;
}

ll R;
ll depth;
ll totalSize;
vector<pair<ll,ll>> difTree;
vector<ll> changeTree;

int leaf(int v){
    return v + R;
}

int parent(int v){
    return v/2;
}

int left(int v){
    return v*2;
}

int right(int v){
    return v*2+1;
}

void updateSingle(int v, ll val){
    int V = leaf(v);
    difTree[V] = MP(val,-1);
    V = parent(V);

    while(V >= 1){
        if(difTree[left(V)].first > difTree[right(V)].first){
            difTree[V] = difTree[left(V)];
        }else{
            difTree[V] = difTree[right(V)];
        }
        V = parent(V);
    }
}

void lazyUpadte(int v){
    if(changeTree[v] != 0){
        difTree[v].first += changeTree[v];
        if(v <= R){ //posibble error
            changeTree[left(v)] += changeTree[v];
            changeTree[right(v)] += changeTree[v];
        }
        changeTree[v] = 0;
    }
}

void updateRange(int l, int r, int val){
    int L = leaf(l);
    int R = leaf(r);
    changeTree[L] += val;
    if(L != R){
        changeTree[R] += val;
    }

    while(parent(L) != parent(R)){
        if(L = left(parent(L))){
            changeTree[right(parent(L))] += val;
        }
        if(R = right(parent(R))){
            changeTree[left(parent(R))] += val;
        }

        //update left
        lazyUpadte(left(L));
        lazyUpadte(right(L));
        if(difTree[left(L)].first > difTree[right(L)].first){
            difTree[L] = difTree[left(L)];
        }else{
            difTree[R] = difTree[right(R)];
        }

        //update right
        lazyUpadte(left(R));
        lazyUpadte(right(R));
        if(difTree[left(L)].first > difTree[right(L)].first){
            difTree[L] = difTree[left(L)];
        }else{
            difTree[R] = difTree[right(R)];
        }

        L = parent(L);
        R = parent(R);
    }

    int V = parent(L);
    while(V >= 1){
        if(difTree[left(V)].first > difTree[right(V)].first){
            difTree[V] = difTree[left(V)];
        }else{
            difTree[V] = difTree[right(V)];
        }
        V = parent(V);
    }
}

pair<ll,ll> getRange(int l, int r, int lb, int rb, int v){
    if(l > r) return MP(llINF, -1);

    lazyUpadte(v);
    
    if(l == lb && r == rb){
        return difTree[v];
    }else{
        ll mb = (lb+rb)/2;
        pair<ll,ll> pl = getRange(l, min(r,rb), lb, mb, left(v));
        pair<ll,ll> pr = getRange(max(l,lb), r, mb, rb, right(v));

        if(pl.first > pr.first){
            return pl;
        }else{
            return pr;
        }
    }
}

vector<ll> solve() {
    changeTree.clear();
    difTree.clear();
    
    //prepare the tree
    R = 1;
    depth = 1;
    while(1<<(depth) < n){
        R += 1<<depth;
        depth++;
    } 
    totalSize = R + (1<<depth);

    //geting the s vector
    vector<ll> s;
    ll sum = 0;
    for(int i = w.size()-1; i>= 0; i--){
        s.PB(w[i]-sum);
        sum += w[i];
    }

    reverse(s.begin(),s.end());

    //create seg trees
    changeTree.assign(totalSize+1, 0);
    difTree.assign(totalSize+1, MP(0,-1));
    
    for(int i = totalSize; i>=1; i--){
        if(i > R && i <= R+n){
            difTree[i] = MP(s[i-R],i);
        }else if(i <= R){
            if(difTree[left(i)].first > difTree[right(i)].first){
                difTree[i] = difTree[left(i)];
            }else{
                difTree[i] = difTree[right(i)];
            }
        }
    }

    //get ans
    vector<ll> ans;

    ll sum = 0;
    for(int i = 1; i<=n; i++){
        pair<ull,ull> p = getRange(0, n-1, 0, totalSize-1, 1);
        sum += p.first;
        ans.PB(sum);
        updateSingle(p.second, -llINF);
        updateRange(0,p.second-1, p.first);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for (int test = 1; test <= 1; test++) {
        cout << "TEST nr." << test << " = ";
        if (op == 1) {
            getData();
        } else {
            getRandom();
        }
        vector<ll> ansB = brute();
        vector<ll> ansS = solve();
        for (int i = 0; i < ansB.size(); i++) {
            if (ansB[i] != ansS[i]) {
                cout << "ERROR\n";
                cout << "BRUTE: \n";
                for (int j = 0; j < ansB.size(); j++) {
                    cout << ansB[j] << " ";
                }
                cout << "\n";
                cout << "SOLVE: \n";
                for (int j = 0; j < ansS.size(); j++) {
                    cout << ansS[j] << " ";
                }
                cout << "\n";
                return 0;
            }
        }
        cout << "CORRECT\n";
    }

    return 0;
}
