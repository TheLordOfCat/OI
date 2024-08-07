#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, m;
vector<PII> edges;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){

}

void printData(){
    cout<<"DATA:\n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<m; i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

ull brute(){
    
}

ull solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<= 1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        ull ansB = brute();
        ull ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}