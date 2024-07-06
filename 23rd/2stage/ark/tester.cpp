#include <iostream>
#include <vector>
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

int n, m, k;
vector<PII> blocks;

void getData(){
    cin>>n>>m>>k;
    for(int i = 0; i<k ;i++){
        int a, b;
        cin>>a>>b;
        blocks.PB(MP(a,b));
    }
}

void getRandom(){
    blocks.clear();

    srand(time(0));

    n = rand()%10+1;
    m = rand()%10+1;
    k = rand()%(n*m/2)+1;
    vector<vector<bool>> vis(n+1, vector<bool>(m+1, false));
    for(int i =0 ; i<k; i++){
        int a = 0;
        int b = 0;
        while(a == b || vis[a][b]){
            a = rand()%n+1;
            b = rand()%m+1;
        }
        blocks.PB(MP(a,b));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<" "<<k<<"\n";
    for(int i = 0; i<k; i++){
        cout<<blocks[i].first<<" "<<blocks[i].second<<"\n";
    }
}

ull brute(){
    
}

ull solve(){

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1 ;test++){
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