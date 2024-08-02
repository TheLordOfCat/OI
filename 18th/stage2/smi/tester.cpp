#include<iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <tuple>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int n, m;
vector<tuple<int,int,int,int>> edges;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b, s,t;
        cin>>a>>b>>s>>t;
        edges.PB(MT(a,b,s,t));
    }
}

void getRandom(){
    edges.clear();

    srand(time(0));

    n = rand()%2+3;
    m = 0;

    for(int i = 1; i<=n; i++){
        edges.PB(MT(i,(i+1)%n,1,0));
        m++;
    }

    for(int i = 1; i<=n; i++){
        int con = rand()%2+2;
        edges.PB(MT(i,n+1, 0, 1));
        for(int j = 0; j<con-1; j++){
            n++;
            edges.PB(MT(n,n+1, 0,1));
        }
        n++;
        edges.PB(MT(n,i,0,1));
        m += con+1;
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<get<0>(edges[i])<<" "<<get<1>(edges[i])<<" "<<get<2>(edges[i])<<" "<<get<3>(edges[i])<<"\n";
    }
}

bool verify(vector<vector<int>> cycles){

}

vector<vector<int>> solve(){
   
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test = 1; test<=10'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<vector<int>> ansS = solve();
        if(!verify(ansS)){
            cout<<"ERORR\n";
            cout<<"SOLVE: \n";
            cout<<ansS.size()<<"\n";
            for(int i = 0; i<ansS.size(); i++){
                for(int j = 0; j <ansS[i].size(); j++){
                    int cur = ansS[i][j];
                    cout<<cur<<" ";
                }
                cout<<"\n";
            }
            cout<<"\n";
        }
        cout<<"CORRECT\n";
    }

    return 0;
}