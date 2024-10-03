#include <iostream>
#include <vector>
#include <queue>
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

int n, X, z;
vector<int> x;
vector<int> k;

void getData(){
    x.clear();
    k.clear();

    cin>>n>>X>>z;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0; i<z; i++){
        int temp;
        cin>>temp;
        k.PB(temp);
    }
}

void getRandom(){
    x.clear();
    k.clear();

    srand(time(0));

    n = rand()%10+2;
    X = rand()%10+1;
    z = rand()%10+1;

    vector<bool> used(n+1, false);
    used[0] = true; used[n] = true;

    x = {0,X};
    for(int i = 0; i<n; i++){
        int a = 0;
        while(used[a]){
            a = rand()%n+1;
        }
        x.PB(a);
    }
    sort(x.begin(), x.end());

    for(int i = 0; i<z; i++){
        int temp = rand()%10+1;
        k.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<X<<" "<<z<<"\n";
    for(int i = 0; i<x.size(); i++){
        cout<<x[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<k.size(); i++){
        cout<<k[i]<<" ";
    }
    cout<<"\n";
}

vector<PII> brute(){

}

vector<PII> solve(){

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
        vector<PII> ansB = brute();
        vector<PII> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j].first<<"/"<<ansB[j].second<<"  ";
                } 
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j].first<<"/"<<ansS[j].second<<"  ";
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