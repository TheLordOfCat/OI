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

void inicjuj()
{
    t.assign(n, 0);
    N = n, K = k;
    for (int i = 0; i < n; i++) t[i] = D[i];
}

void podlej(int a, int b)
{
    t[a] += 1;
    t[b] += 1;
}

int dojrzale(int a, int b)
{
    return (t[a] >= K) + (t[b] >= K); /* cos glupiego */
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