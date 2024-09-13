#include <iostream>
#include <vector>
#include <stack>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int n;
vector<int> atr;
vector<PII> edges;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        atr.PB(temp);
    }
    for(int i =0 ; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    for(int i = 0; i<n; i++){
        int temp = rand()%10+10;
        atr.PB(temp);
    }
    int ind = 2;
    for(int i = 1; i<=n; i++){
        if(ind > n){
            break;
        }
        int con = rand()%3+1;
        for(int  j = 0; j<con; j++){
            if(ind > n){
                break;
            }
            edges.PB(MP(i,ind));
            ind++;
        }
    }
}

void printData(){
    cout<<n<<"\n";
    for(int i = 0; i<atr.size(); i++){
        cout<<atr[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

tuple<int,int,vector<int>> brute(){

}

tuple<int,int,vector<int>> solve(){
    
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
        tuple<int,int, vector<int>> ansB = brute(); 
        tuple<int,int, vector<int>> ansS = solve();
        bool ok = true;

        if(get<0>(ansB) != get<0>(ansS)){
            ok = false;
        }else if(get<1>(ansB) != get<1>(ansS)){
            ok = false;
        }else{
            // use based on way of coding
            //
            // vector<int> c = get<2>(ansB);
            // vector<int> d = get<2>(ansS);
            // for(int i = 0; i<c.size(); i++){
            //     if(c[i] !=d[i]){
            //         ok = false;
            //         break;
            //     }
            // }
        }


        if(!ok){
            cout<<"ERROR\n";
            cout<<"BURTE: \n";
            int a = get<0>(ansB), b = get<1>(ansB); vector<int> c = get<2>(ansB);
            cout<<a<<"\n"<<b<<"\n";
            for(int i = 0; i< c.size(); i++){
                cout<<c[i]<<" ";
            }
            cout<<"\n";

            cout<<"SOLVE: \n";
            a = get<0>(ansS), b = get<1>(ansS); c = get<2>(ansS);
            cout<<a<<"\n"<<b<<"\n";
            for(int i = 0; i< c.size(); i++){
                cout<<c[i]<<" ";
            }
            cout<<"\n";
            printData();
            return 0;
        } else{
            cout<<"CORRECT\n";
        }
    }

    return 0;
}