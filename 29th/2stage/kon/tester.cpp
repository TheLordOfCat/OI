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

int q;
vector<pair<char,int>> input;

void getData(){
    cin>>q;
    for(int i = 0; i<q; i++){
        char c;
        cin>>c;
        int x;
        cin>>x;
        input.PB(MP(c,x));
    }
}

void getRandom(){
    srand(time(0));

    q = rand()%10+1;
    int guests = 2;
    for(int i =0 ; i< q; i++){
        int type = rand()%3+1;
        char c;
        if(type == 1){
            c = 'W'; 
            guests++;
        }else if(type == 2){
            c = 'Z';
            guests++;
        }else{
            c = '?';
        }
        int x = rand()%guests+1;
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<q<<"\n";
    for(int i = 0; i<input.size(); i++){
        cout<<input[i].first<<" "<<input[i].second<<"\n";
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
                cout<<"ERROR\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}