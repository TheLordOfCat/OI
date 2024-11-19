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
    n = rand()%10+1;
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
  
            if(i-j - j <= d){
                ull temp1 = f(j,i-j);
                ull temp2 = f(i-j,j);
                if(temp1 < m){
                    m = temp1;
                    bestJ = j;
                }
                if(temp2 < m){
                    m = temp2;
                    bestJ = j;
                }
            }
        }
        dp[i] = m + dp[bestJ] + dp[i-bestJ];
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
        S.push(MP(r.first/2-d/2-2, r.second/2+d/2+2));
    }

    //get base
    int baseRight = S.top().second;
    vector<ull> dp(baseRight+1, 0);
    for(int i = 2; i<=baseRight; i++){
        ull m = ullINF;
        ull bestJ = ullINF;
        for(ull  j = i/2+d/2+2; j>= max(0, i/2-d/2-2); j--){
            ull dif;
            if(i-j > j) {
                dif = i-j-j;
            }else{
                dif = j-(i-j);
            }

            if(i-j - j <= d){
                ull temp1 = f(j,i-j);
                ull temp2 = f(i-j,j);
                if(temp1 < m){
                    m = temp1;
                    bestJ = j;
                }
                if(temp2 < m){
                    m = temp2;
                    bestJ = j;
                }
            }
        }
        dp[i] = m + dp[bestJ] + dp[i-bestJ];
    }

    //process ranges
    ull firstElement = 1;
    while(!S.empty()){
        PII r = S.top();
        S.pop();
        
        vector<ull> nextDp(r.second+1, 0);
        for(int i = 2; i<=r.second; i++){
            ull m = ullINF;
            ull bestJ = ullINF;
            for(ull  j = i/2+d/2+2; j>= max(0, i/2-d/2-2); j--){
                ull dif;
                if(i-j > j) {
                    dif = i-j-j;
                }else{
                    dif = j-(i-j);
                }

                if(i-j - j <= d){
                    ull temp1 = f(j,i-j);
                    ull temp2 = f(i-j,j);
                    if(temp1 < m){
                        m = temp1;
                        bestJ = j;
                    }
                    if(temp2 < m){
                        m = temp2;
                        bestJ = j;
                    }
                }
            }
            nextDp[i] = m + dp[bestJ-firstElement] + dp[i-bestJ-firstElement];
        }

        dp = nextDp;
        firstElement = r.first;
    }

    return dp.front();
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