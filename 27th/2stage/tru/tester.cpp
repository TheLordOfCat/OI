#include <iostream>
#include <vector>
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

void getData(){
    cin>>n;
}

void getRandom(){
    n = rand()%20+1;
}

void printData(){
    cout<<"DATA: \n"<<n<<"\n";
}

ull gcd(ull a, ull b){
    while(b){
        a %= b;
        swap(a,b);
    }
    return a;
}

ull numberDivsors(ull v){
    ull ans = 0;

    for(ull i = 1; i*i<=v; i++){
        if(v %i == 0){
            ans += 2;
            if(i*i == v){
                ans--;        
            }
        }
    }

    return ans;
}

tuple<ull,ull,ull> brute(){
    tuple<ull,ull,ull> ans = MT(0,0,0);

    for(ull i = 1; i <= n; i++){
        for(ull j = i; j >= 1; j--){
            ull divA = numberDivsors(i);
            ull divB = numberDivsors(j);
            ull g = gcd(i,j);
            ull divG = numberDivsors(g);

            ull temp = divA+divB-divG;
            
            if(get<0>(ans) < temp){
                ans = MT(temp, i, j);
            }
        }
    }

    return ans;
}

tuple<ull,ull,ull> solve(){

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
        tuple<ull,ull,ull> ansB = brute();
        tuple<ull,ull,ull> ansS = solve();
        if(get<0>(ansB) != get<0>(ansS)){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<get<0>(ansB)<<"\n";
            cout<<get<1>(ansB)<<" "<<get<1>(ansB)<<"\n";
            cout<<"SOLVE: \n";
            cout<<get<0>(ansS)<<"\n";
            cout<<get<1>(ansS)<<" "<<get<1>(ansS)<<"\n";
            printData();
            return 0;
        }
    }

    return 0;
}