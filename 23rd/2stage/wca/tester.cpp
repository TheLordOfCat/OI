#include<iostream>
#include<vector>

#include <cstdlib>
#include <ctime>

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using namespace std;

using ll = long long int;

int n;
vector<int> a;

void getData(){
    cin>>n;
    for(int i =0 ; i<n; i++){
        int temp;
        cin>>temp;
        a.PB(temp);
    }
}

void getRandom(){
    a.clear();
    srand(time(0));
    n = rand()%5+1;
    for(int i = 0; i<n; i++){
        a.PB(rand()%10+1);
    }
}

void printData(){
    cout<<n<<"\n";
    for(int i = 0; i<a.size(); i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

ll brute(){

}

ll solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op=  1;
    for(int test = 1; test<=1; test++){
        cout<<"Test nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        ll ansB = brute();
        ll ansS = solve();
        if(ansS != ansB){
            cout<<"ERRROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}