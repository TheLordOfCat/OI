#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PB push_back
#define MT make_tuple

int n, m, d, k;
vector<tuple<int,int,vector<int>>> edges;

void getData(){
    edges.clear();

    cin>>n>>m>>d>>k;
    for(int i = 0; i<m; i++){
        int a, b;
        vector<int> s;
        cin>>a>>b;
        for(int i = 0; i<k; i++){
            int temp;
            cin>>temp;
            s.PB(temp);
        }
        edges.PB(MT(a,b,s));
    }
}

void getRandom(){
    edges.clear();

    n = rand()%10+1;
    m = rand()%10+n;
    d = rand()%n+1;
    k = 1;

    //create path from 1 to n
    for(int i = 0; i<k; i++){
        vector<int> s;
        for(int i =0 ; i<k; i++){
            int temp = rand()%10+1;
            s.PB(temp);
        }
        edges.PB(MT(i+1, i+2, s));
    }
    get<1>(edges.back()) = n;

    //create other edges
    for(int i = k; i<m; i++){
        int a = 1, b = 1;
        while(a == b){
            a = rand()%n+1; b = rand()%n+1;
        }
        vector<int> s;
        for(int i =0 ; i<k; i++){
            int temp = rand()%10+1;
            s.PB(temp);
        }
        edges.PB(MT(a, b, s));
    }
}

void printData(){
    cout<<n<<" "<<m<<" "<<d<<" "<<k<<"\n";
    for(int i = 0; i< edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]);
        vector<int> s = get<2>(edges[i]);
        cout<<a<<" "<<b<<" ";
        for(int j = 0; j<s.size(); j++) cout<<s[i]<<" ";
        cout<<"\n";
    }
}

vector<ll> brute(){
    
}

vector<ll> solve(){

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
        for(int i = 0; i< ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++) cout<<ansB[j]<<" ";
                cout<<"\nSOVLE: ";
                for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<" ";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}