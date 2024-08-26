#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const int llINF = 9'000'000'000'000'000'000;
const int ullINF = 18'000'000'000'000'000'000;

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define MT make_tuple
#define PB push_back

int n, m;
vector<tuple<char,int,int,int>> promts;

PII& operator+=(PII& lhs, const PII& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

pair<ll, ll>& operator+=(pair<ll, ll>& lhs, const pair<ll, ll>& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

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

void getRandom(){
    promts.clear();
    
    srand(time(0));

    n = rand()%10+2;
    m = rand()%5+1;
    vector<bool> stations(n+1, false);
    int curStations = 0;
    for(int i = 0; i<m; i++){
        char t; int a, b, c;
        int temp = rand()%3+1;

        if(temp == 2){
            if(curStations > 0){
                t = 'U';
                a = rand()%n+1;
                while(!stations[a]){
                    stations[a] = false;
                    curStations--;
                }
                b = -1;
                c = -1;
            }else{
                temp = 1;
            }
        }

        if(temp == 1){
            t = 'P';
            a = rand()%n+1;
            while(stations[a]){
                a = rand()%n+1;
            }
            b = rand()%20+5;
            c = rand()%5+5;
            curStations++;
        }

        if(temp == 3){
            t = 'Z';
            a = -1;
            b = -1;
            while(a != b){
                a = rand()%n+1;
                b = rand()%n+1;
            }
            if(a>b){
                swap(a,b);
            }
            c = -1;
        }

        promts.PB(MT(t,a,b,c));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<promts.size(); i++){
        char t = get<0>(promts[i]);
        int a = get<1>(promts[i]), b = get<2>(promts[i]), c = get<3>(promts[i]); 
        cout<<t<<" "<<a<<" "<<b<<" "<<c<<"\n";
    }
}

vector<int> brute(){
    vector<int> ans;
    vector<PII> poles(n+1, MP(0,0));
    vector<int> signal(n+1, 0);

    for(int i = 0; i<m; i++){
        char t = get<0>(promts[i]);
        int a = get<1>(promts[i]), b = get<2>(promts[i]), c = get<3>(promts[i]); 

        if(t == 'P'){
            poles[a] = MP(b,c);
            
            signal[a] = b;
            
            int temp = b-c;
            int ind = a+1;
            while(temp > 0){
                signal[ind] += temp;
                ind += 1;
                temp -= c;

                if(ind > n){
                    break;
                }
            }

            temp = b-c;
            ind = a-1;
            while(temp > 0){
                signal[ind] += temp;
                ind -= 1;
                temp -= c;

                if(ind <= 0){
                    break;
                }
            }
        }
        
        if(t == 'U'){
            b = poles[a].first;
            c = poles[a].second;

            signal[a] -= b;
            
            int temp = b-c;
            int ind = a+1;
            while(temp > 0){
                signal[ind] -= temp;
                ind += 1;
                temp -= c;
                if(ind > n){
                    break;
                }
            }

            temp = b-c;
            ind = a-1;
            while(temp > 0){
                signal[ind] -= temp;
                ind -= 1;
                temp -= c;

                if(ind <= 0){
                    break;
                }
            }

            poles[a] = MP(0,0);
        }

        if(t == 'Z'){
            int sum = 0;
            for(int i = a; i<=b; i++){
                sum+= signal[i];
            }
            ans.PB(sum / (b-a+1));
        }
    }

    return ans;
}

vector<ll> tree;
vector<pair<ll,ll>> lazy;
ll R = 0;
int depth = 0;
ll totalSize = 0;

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

void upateTree(int v, int tl, int tr, int l, int r, ll s, ll a){
    int mid = (tl+tr)/2;
    if(tl == l && tr == r){
        lazy[left(v)] += MP(s,a);
        lazy[right(v)] += MP(s+(a*(mid)), a);
        ll sum = 0;
        for(ll i = 0; i<(tr-tl+1); i++){
            if(s + a*i > 0){
                sum += s+ a*i;
            }
        }
        tree[v] += sum;
    }else{
        upateTree(left(v), tl, mid, l, min(r, mid), s, a);   
        upateTree(right(v), mid+1, tr, max(l, mid+1), r, s + (mid-tl)*a, a);   
        tree[v] = tree[left(v)] + tree[right(v)];
    }
}

ll query(int v, int tl, int tr, int l, int r){
    int mid = (tl+tr)/2;
    if(lazy[v].first != 0 && lazy[v].second != 0){
        ll s = lazy[v].first;
        ll a = lazy[v].second;

        ll sum = 0;
        for(ll i = 0; i<(tr-tl+1); i++){
            if(s + a*i > 0){
                sum += s+ a*i;
            }
        }
        tree[v] += sum;

        lazy[left(v)] += MP(s,a);
        lazy[right(v)] += MP(s+(a*(mid)), a); 
    }
    lazy[v].first = 0; lazy[v].second = 0;

    if(tl == l && tr == r){
        return tree[v];
    }else{
        return query(left(v), tl, mid, l,min(r, mid)) + query(left(v), mid+1, tr, max(l, mid+1), r);
    }
}

vector<ll> solve(){
    tree.clear();
    lazy.clear();
    R = 0;
    depth = 0;
    totalSize = 0;

    //building the tree
    while((1<<depth) < n){
        R += (1<<depth);
        depth++;
    } 
    totalSize = R + (1<<depth);
    tree.assign(totalSize+1, 0);
    lazy.assign(totalSize+1, MP(0,0));

    //getting the ans
    vector<pair<ll,ll>> poles(n+1, MP(0,0));
    vector<ll> ans;
    for(int i = 0; i<m; i++){
        char t = get<0>(promts[i]);
        int a = get<1>(promts[i]), b = get<2>(promts[i]), c = get<3>(promts[i]); 
        if(t == 'P'){
            ll len = b/c + 1;
            upateTree(1,R+1, totalSize, a-len, a, b-len*c, c);
            upateTree(1,R+1, totalSize, a, a+len, b, c*(-1));
            poles[a] = MP(b,c);
        }
        if(t == 'U'){
            ll b = poles[a].first, c = poles[a].second; 
            ll len = b/c + 1;
            upateTree(1,R+1, totalSize, a-len, a, b-len*c, c);
            upateTree(1,R+1, totalSize, a, a+len, b, c*(-1));

            poles[a] = MP(0,0);
        }
        if(t == 'Z'){
            ll temp = query(1,R+1, totalSize, a, b);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int j= 0 ; j<ansB.size(); j++){
            if(ansB[j] != ansS[j]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int o = 0; o<ansB.size(); o++){
                    cout<<ansB[o]<<" ";
                }
                cout<<"\nSOLVE: ";
                for(int o = 0; o<ansS.size(); o++){
                    cout<<ansS[o]<<" ";
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