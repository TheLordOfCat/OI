#include <iostream>
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
#define PB push_back
#define MT make_tuple

int n;
vector<vector<char>> plane;

void getData(){
    cin>>n;
    plane.PB(vector<char>(n+1, '0'));
    for(int i = 1; i<=n; i++){
        plane.PB(vector<char>());
        plane[i].PB('0');
        for(int j = 1; j<=n; j++){
            char c;
            cin>>c;
            plane[i].PB(c);
        }
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+2;
    plane.PB(vector<char>(n+1, '0'));
    for(int i = 1; i<=n; i++){
        plane.PB(vector<char>());
        plane[i].PB('0');
        for(int j = 1; j<=n; j++){
            int type = rand()%3;
            char c;
            if(type == 0 || type == 1){
                c = '.';
            }else{
                c = '#';
            }
            plane[i].PB(c);
        }
    }

    PII P = MP(rand()%n+1, rand()%n+1);
    PII K = P;
    while(K.first == P.first && K.second == P.second){
        K = MP(rand()%n+1, rand()%n+1);
    }

    plane[P.first][P.second] = 'P';
    plane[K.first][K.second] = 'K';
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            cout<<plane[i][j];
        }
        cout<<"\n";
    }
}

tuple<int, PII, vector<int>> brute(){

}

tuple<int, PII, vector<int>> solve(){

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
        tuple<int,PII,vector<int>> ansB = brute();
        tuple<int,PII,vector<int>> ansS = solve();
        if(get<0>(ansB) != get<0>(ansS)){
            cout<<"ERROR\n";
            cout<<"BURTE: ";
            cout<<get<0>(ansB)<<"\n";
            cout<<get<1>(ansB).first<<" "<<get<1>(ansB).second<<"\n";
            for(int i = 0; i<get<2>(ansB).size(); i++){
                cout<<get<2>(ansB)[i]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: ";
            cout<<get<0>(ansS)<<"\n";
            cout<<get<1>(ansS).first<<" "<<get<1>(ansS).second<<"\n";
            for(int i = 0; i<get<2>(ansS).size(); i++){
                cout<<get<2>(ansS)[i]<<" ";
            }
            cout<<"\n";
            printData();
        }    
        cout<<"CORRECT\n";
    }

    return 0;
}