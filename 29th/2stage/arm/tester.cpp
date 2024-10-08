#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

ull n, a, b;

void getData(){
    cin>>n>>a>>b;
}

void getRandom(){
    srand(time(0));

    n = rand()%50+1;
    a = rand()%10+1;
    b = rand()%10+1;
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<a<<" "<<b<<"\n";
}

ull brute(){
    vector<ull> dp(2*n, ullINF);

    dp[1] = 0;
    for(ull i = 1; i<n; i++){
        for(ull j = 1; j<n; j++){
            dp[i*j] = min(dp[i*j], dp[i] + a + (j-1)*b);
            if(i*j > n){
                break;
            }
        }
    }

    return dp[n];
}

ull solve(){
    ull ans = ullINF;
    for(ull m = 1; (1<<m) <= 2*n; m++){
        ull s = floor(pow((n+1), 1.0 / m));
        for(ull k = 0; k<=m; k++){
            ull sum = pow(s,k) * pow(s+1,m-k);
            if(sum >= n+1){
                ull cost = m*a+(s*m-k)*b;
                if(cost < ans){
                    ans = cost;
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test = 1; test <= 10'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        ull ansB = brute();
        ull ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BURTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}