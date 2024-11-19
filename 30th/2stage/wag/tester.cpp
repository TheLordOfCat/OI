#include <iostream>
#include <vector>
#include <stack>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

ull n; int d, a, b;

void getData(){
    cin>>n>>d>>a>>b;
}

void getRandom(){
    srand(time(0));
    n = rand()%50+80;
    d = rand()%10+1;
    a = rand()%10+1;
    b = rand()%10+1;
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<d<<" "<<a<<" "<<b<<"\n";
}

ull f(ull w, ull v){
    ull temp = (ull)a*w + (ull)b*v;
    return temp%1001;
}

ull brute(){
    vector<ull> dp(n+1, 0);
    
    for(ull i = 2; i<=n; i++){
        ull m = ullINF;
        ull bestJ = ullINF;
        for(ull  j = i-1; j>= 1; j--){
            ull dif;
            if(i-j > j) {
                dif = i-j-j;
            }else{
                dif = j-(i-j);
            }
  
            if(dif <= d){
                ull temp1 = min(f(j,i-j),f(i-j,j));
                if(temp1 + dp[j] + dp[i-j]  < m){
                    m = temp1+ dp[j] + dp[i-j];
                    bestJ = j;
                }
            }
        }
        dp[i] = m;
    }

    return dp[n];
}

ull solve(){
    //generate ranges
    stack<PII> S;

    S.push(MP(n,n));
    while(true){
        PII r = S.top();
        if(r.first == 1){
            break;
        }
        S.push(MP(max(r.first/2-d/2-2,1), r.second/2+d/2+2));
    }

    //get base
    int baseRight = S.top().second;
    vector<ull> dp(baseRight+1, 0);
    for(int i = 2; i<=baseRight; i++){
        ull m = ullINF;
        ull bestJ = ullINF;
        for(ull  j = min(i/2+d/2+2,i-1); j>= max(1, i/2-d/2-2); j--){
            ull dif;
            if(i-j > j) {
                dif = i-j-j;
            }else{
                dif = j-(i-j);
            }

            if(dif <= d){
                ull temp1 = min(f(j,i-j),f(i-j,j));
                if(temp1 + dp[j] + dp[i-j]  < m){
                    m = temp1+ dp[j] + dp[i-j];
                    bestJ = j;
                }
            }
        }
        dp[i] = m;
    }

    //process ranges
    S.pop();
    ull firstElement = 0;
    while(!S.empty()){
        PII r = S.top();
        S.pop();
        
        vector<ull> nextDp(r.second+1-r.first+1, 0);
        for(int i = r.first; i<=r.second; i++){
            ull m = ullINF;
            ull bestJ = ullINF;
            for(ull  j = min(i/2+d/2+2,i-1); j>= max(1, i/2-d/2-2); j--){
                ull dif;
                if(i-j > j) {
                    dif = i-j-j;
                }else{
                    dif = j-(i-j);
                }

                if(dif <= d){
                    ull temp1 = min(f(j,i-j),f(i-j,j));
                    if(temp1 + dp[j-firstElement] + dp[i-j-firstElement]  < m){
                        m = temp1+ dp[j-firstElement] + dp[i-j-firstElement];
                        bestJ = j;
                    }
                }
            }
            nextDp[i-r.first+1] = m;
        }

        dp = nextDp;
        firstElement = r.first-1;
    }

    return dp.back();
}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 1; test++){
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