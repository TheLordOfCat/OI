#include<iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n;
vector<char> s;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        char temp;
        cin>>temp;
        s.PB(temp);
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    for(int  i = 0; i<n; i++){
        int temp = rand()%26;
        char cTemp = temp + 'a';
        s.PB(cTemp);
    }
}

void printData(){
    cout<<"DATA:\n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<s[i];
    }
    cout<<"\n";
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
    for(int test = 1; test<=1; test++){
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
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}