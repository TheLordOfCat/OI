#include <iostream>
#include <vector>

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