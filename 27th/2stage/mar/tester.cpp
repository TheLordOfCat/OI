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

int n, m;
vector<int> digits;
vector<int> querys;

void getData(){
    cin>>n>>m;
    for(int i =0 ; i<n; i++){
        char c;
        cin>>c;
        digits.PB(c-'0');
    }
    for(int i =0 ; i<m; i++){
        int temp;
        cin>>temp;
        querys.PB(temp);
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    m = rand()%5+1;
    for(int i =0 ; i<n; i++){
        int temp = rand()%2;
        digits.PB(c-'0');
    }
    for(int i =0 ; i<m; i++){
        int temp;
        cin>>temp;
        querys.PB(temp);
    }
}

void printData(){

}

vector<int> brute(){

}

vector<int> solve(){

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
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERORR\n";
                cout<<"BRUTE: ";
                for(int j =0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j =0; j<ansS.size(); j++){
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