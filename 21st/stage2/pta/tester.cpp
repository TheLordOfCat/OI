#include <iostream>
#include <vector>
#include <deque>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;

int n;
vector<int> d;
int q;
vector<int> k;

void getData(){
    cin>>n;
    for(int i =0 ; i<n; i++){
        int temp;
        cin>>temp;
        d.PB(temp);
    }
    cin>>q;
    for(int i = 0; i<q; i++){
        int temp;
        cin>>temp;
        k.PB(temp);
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    for(int i =0; i<n; i++){
        int temp = rand()%10+1;
        d.PB(temp);
    }
    q = rand()%(min(25,n))+1;
    for(int i = 0; i<q; i++){
        int temp = rand()%n+1;
        k.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i =0; i<n; i++){
        cout<<d[i]<<" ";
    }
    cout<<"\n";
    cout<<q<<"\n";
    for(int i =0; i<q; i++){
        cout<<k[i]<<" ";
    }
    cout<<"\n";
}

vector<int> brute(){
    vector<int> ans;
    for(int o = 0; o<q; o++){
        int r = k[o];
        vector<int> dp(n+1, 0);
    
        for(int i = n-1; i>=1; i--){
            int val = INF;
            for(int j = i+1; j<= n && j<=i+r; j++){
                if(d[j] >= d[i]){
                    val = min(val,dp[j]);
                }else{
                    val = min(val, dp[j] + 1); 
                }
            }
            dp[i] = val;
        }

        ans.PB(dp[1]);
    }

    return ans;
}

void remQue(deque<PII>& Q, int& Qsize){
    if(Q.size() > 0){
        if(Q.front().second == 1){
            Q.pop_front();
        }else{
            Q.front().second--;
        }
        Qsize--;
    }
}

void pushQue(deque<PII>& Q, int p, int& Qsize){
    int count = 1;
    if(Q.size() > 0){
        while(Q.back().first <= p){
            count += Q.back().second;
            Q.pop_back();
            if(Q.size() == 0 ){
                break;
            }
        }
    }

    Q.push_back(MP(p,count));

    Qsize++;
}

vector<int> solve(){
    vector<int> ans;

    for(int o = 0; o<q; o++){
        int r = k[o];
        vector<int> inQ(n+1, -1);

        deque<PII> Q1,Q2;
        int Q1Size = 0, Q2Size = 0;
        pushQue(Q1, d[0], Q1Size);
        inQ[1] = 1;
        int maxQ = 2;

        for(int i = 2; i<=n; i++){
            if(Q1.front().first > d[i-1]){
                pushQue(Q1, d[i-1], Q1Size);
                inQ[i] = maxQ-1;
            }else{
                pushQue(Q2, d[i-1], Q2Size);
                inQ[i] = maxQ;
            }

            if(Q1Size + Q2Size > r){
                if(inQ[i-r] == maxQ-1){
                    remQue(Q1, Q1Size);
                }else{
                    remQue(Q2, Q2Size);
                }
            }

            if(Q1Size == 0){
                Q1 = Q2;
                Q2.clear();
                Q1Size = Q2Size;
                Q2Size = 0;
                maxQ++;
            }
        }

        if(inQ[n] == maxQ-1){
            ans.PB(maxQ-2);
        }else{
            ans.PB(maxQ-1);
        }
    }

    return ans;
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
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}