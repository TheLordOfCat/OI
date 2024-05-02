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

void getRandom(){
    srand(time(0));
    n = rand()%10+1;
    m = rand()%10+1;
    for(int i = 0; i<m; i++){
        int type = rand()%2+1;
        if(type == 1){ //U
            int k = rand()%n+1;
            int a = rand()%10;
            request.PB(MP('Z',MP(k,a)));
        }else if(type == 2){ //Z
            int c = rand()%n+1;
            int s = rand()%10+1;
            request.PB(MP('Z',MP(c,s)));
        }
    }
}

void printData(){
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<request.size(); i++){
        cout<<request[i].first<<" "<<request[i].second.first<<" "<<request[i].second.second<<"\n";
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

    int op = 1;
    for(int test =1 ;test<=1;test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<bool> ansB = brute();
        vector<bool> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    if(ansB[j]){
                        cout<<j<<" TAK |";
                    }else{
                        cout<<j<<" NIE |";
                    }
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    if(ansS[j]){
                        cout<<"TAK ";
                    }else{
                        cout<<"NIE ";
                    }
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