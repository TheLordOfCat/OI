#include <iostream>
#include <vector>

#include <cstdlib>
#include <ctime>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int k;

void getData(){
    cin>>k;
}

void getRandom(){
    srand(time(0));
    k = rand()%100+1;
}

void printData(){
    cout<<"DATA: "<<k<<"\n";
}

int brute(){

}

int solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;

    int p = 1;
    // cin>>p;
    for(int i = 0; i<p; i++){
        for(int test =1 ;test<=1; test++){
            cout<<"TEST nr."<<test<<" = ";
            if(op == 1){
                getData();
            }else{
                getRandom();
            }
            int ansB = brute();
            int ansS = solve();
            if(ansB != ansS){
                cout<<"ERROR\n";
                cout<<"BURUTE: "<<ansB<<"\n";
                cout<<"SOLVE: "<<ansS<<"\n";
                return 0;
            }
            cout<<"CORRECT\n";
        }
    }

    return 0;
}