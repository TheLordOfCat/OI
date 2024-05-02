#include <iostream>
#include <vector>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

int n, m;
vector<pair<char,PII>> request;

void getData(){
    cin>>n>>m;
    for(int i =0; i <m; i++){
        char c;
        int a,b;
        cin>>c;
        cin>>a>>b;
        request.PB(MP(c,MP(a,b)));
    }
} 

vector<bool> brute(){
    
}

vector<bool> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<bool> ansS = solve();
    for(int j = 0; j<ansS.size(); j++){
        if(ansS[j]){
            cout<<"TAK\n";
        }else{
            cout<<"NIE\n";
        }
    }

    return 0;
}