#include<iostream>
#include <vector>

#include <cstdlib>
#include <ctime>


using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int z;
int n,m;
vector<vector<int>> logs;

void getData(){
    logs.clear();
    cin>>n>>m;
    logs.assign(n+1, vector<int>());
    for(int o = 0; o<m; o++){
        int t,j,i;
        cin>>t>>j>>i;
        logs[o].PB(t);
        logs[o].PB(j);
        logs[o].PB(i);
    }
}

void getRandom(){
    srand(time(0));
    n =rand()%5+1;
    m = rand()%10+1;
    logs.clear();
    logs.assign(n+1, vector<int>());
    for(int o = 0; o<m; o++){
        int t = rand()%m+1,j = rand()%n+1,i = rand()%n;
        logs[o].PB(t);
        logs[o].PB(j);
        logs[o].PB(i);
    }
}

void printData(){
    cout<<n<<" "<<m<<"\n";
    for(int o = 0; o<m; o++){
        cout<<logs[o][0]<<" "<<logs[o][1]<<" "<<logs[o][2]<<"\n";
    }
}

vector<int> brute(){

}

vector<int> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cin>>z;
    // z= 1;
    for(int i =0; i<z; i++){
        int op = 1;
        for(int test = 1; test<=1; test++){
            cout<<"TEST nr."<<test<<" = ";
            if(op == 1){
                getData();
            }else{
                getRandom();
            }
            vector<int> ansB = brute();
            vector<int> ansS = solve();
            for(int i =0 ; i<ansB.size(); i++){
                if(ansB[i] != ansS[i]){
                    cout<<"ERROR\n";
                    cout<<"BRUTE: ";
                    for(int i =0; i<ansB.size(); i++){
                        cout<<ansB[i]<<" ";
                    }
                    cout<<"SOLVE: ";
                    for(int i =0; i<ansS.size(); i++){
                        cout<<ansS[i]<<" ";
                    }
                    return 0;
                }
            }
            cout<<"CORRECT\n";
        }
    }

    return 0;
}