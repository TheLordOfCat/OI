#include <iostream>
#include <vector>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

ull K;

void getData(){
    cin>>K;
}

void getRandom(){
    srand(time(0));

    K = rand()%20+1;
}

void printData(){
    cout<<"DATA: \n"<<K<<"\n";
}

bool verify(vector<vector<int>>& plane){
    vector<vector<ull>> dp(plane.size(), vector<ull>(plane.size(), 0));

    for(int i = 0; i<plane.size(); i++){
        for(int j = 0; j<plane[i].size(); j++){
            if(plane[i][j] == 1){
                ull sum = 0;
                if(i > 0){
                    sum += dp[i-1][j];
                }
                if(j > 0){
                    sum += dp[i][j-1];
                }
                dp[i][j] = sum;
            }
        }
    }
    if(dp[plane.size()-1][plane.size()-1] == K){
        return true;
    }else{
        return false;
    }
}

vector<vector<int>> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 1; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<vector<int>> ansS = solve();
        if(verify(ansS)){
            cout<<"ERROR\n";
            cout<<"SOLVE: ";
            cout<<ansS.size()<<"\n";
            for(int i = 0; i<ansS.size(); i++){
                for(int j = 0; j<ansS[i].size(); j++){
                    if(ansS[i][j] == 0){
                        cout<<"#";
                    }else{
                        cout<<".";
                    }
                }
                cout<<"\n";
            }
        }
    }

    return 0;
}