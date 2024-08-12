#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define PIC pair<int,char>

int n, m;
vector<pair<PII,char>> edges;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        char c;
        cin>>c;
        edges.PB(MP(MP(a,b),c));
    }
}

void getRandom(){
    edges.clear();

    srand(time(0));

    n = rand()%10+1;
    m = 0;
    for(int i = 1; i <= n; i++){
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            int temp = i;
            while(temp == i){
                temp = rand()%n+1;
            }
            int type = rand()%2+1;
            char c;
            if(type == 1){
                c = 'a';
            }else{
                c = 'b';
            }
            edges.PB(MP(MP(i,temp),c));
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i= 0; i<edges.size(); i++){
        cout<<edges[i].first.first<<" "<<edges[i].first.second<<" "<<edges[i].second<<"\n";
    }
}

vector<pair<int,vector<char>>> brute(){
    
}

vector<pair<int,vector<char>>> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<= 1; test ++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<pair<int,vector<char>>> ansB = brute();
        vector<pair<int,vector<char>>> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: \n";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j].first<<" ";
                    for(int o = 0; o<ansB[j].second.size(); o++){
                        cout<<ansB[j].second[o];
                    }
                    cout<<"\n";
                } 
                cout<<"SOLVE: \n";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j].first<<" ";
                    for(int o = 0; o<ansS[j].second.size(); o++){
                        cout<<ansS[j].second[o];
                    }
                    cout<<"\n";
                } 
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}