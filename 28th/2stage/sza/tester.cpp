#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <vector>
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

int n;
vector<tuple<int,int,char>> edges;

void getData(){
    edges.clear();

    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        char c;
        edges.PB(MT(a,b,c));
    }
}

void getRandom(){
    edges.clear();

    n = rand()%10+1;
    int ind = 2;
    for(int i = 1; i<n-1; i++){
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            char c = rand()%2 + 'a';
            edges.PB(MT(i,ind,c));
            ind++;
            if(ind>n){
                break;
            }
        }
        if(ind>n){
            break;
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<get<0>(edges[i])<<" "<<get<1>(edges[i])<<" "<<get<2>(edges[i])<<"\n";
    }
}

vector<string> brute(){

}

vector<string> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"Test nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<string> ansB = brute();
        vector<string> ansS = solve();
        bool ok = true;
        if(ansB.size() != ansS.size()){
            ok = false;
        }else{
            for(int i = 0; i<ansB.size(); i++){
                if(ansB[i] != ansS[i]){
                    ok = false;
                    break;
                }
            }
        }
        if(!ok){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<ansB.size()<<"\n";
            for(int i =0 ; i<ansB.size(); i++){
                cout<<ansB[i]<<"\n";
            }
            cout<<"SOLVE: \n";
            cout<<ansS.size()<<"\n";
            for(int i =0 ; i<ansS.size(); i++){
                cout<<ansS[i]<<"\n";
            }
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}