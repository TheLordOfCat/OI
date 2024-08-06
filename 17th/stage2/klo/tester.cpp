#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using ll = long long int;
using ull = unsigned long long int;

using namespace std;

#define PB push_back
#define PII pair<int,int>
#define MP make_pair

const int i_INF = 2'000'000;
const ll ll_INF = 9'000'000'000'000'000;

int n, m;
vector<int> x;
vector<int> k;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0; i<m; i++){
        int temp;
        cin>>temp;
        k.PB(temp);
    }
}

void getRandom(){
    x.clear();
    k.clear();

    srand(time(0));

    n = rand()%10+1;
    for(int i =0 ; i<n; i++){
        int temp = rand()%10+1;
        x.PB(temp);
    }
    for(int i =0 ; i<m; i++){
        int temp = rand()%10+1;
        k.PB(temp);
    }
}

void printData(){
    cout<<"DATA:\n";
    cout<<n<<" "<<m<<"\n";
    for(int i =0 ; i<n; i++){
        cout<<x[i]<<" ";
    }
    cout<<"\n";
    for(int i =0 ; i<m; i++){
        cout<<k[i]<<" ";
    }
    cout<<"\n";
}

vector<int> brute(){
    vector<int> ans;
    for(int o = 0; o<m; o++){
        int lim = k[o];

        vector<int> w;
        for(int i = 0; i<n; i++){
            w.PB(x[i]-lim);
        }
        
        int best = 0;
        for(int i = 0; i<n; i++){
            for(int j = i; j<n; j++){

                ll sum = 0;
                for(int r = i; r<=j; r++){
                    sum += w[r];
                }

                if(sum >= 0){
                    best = max(best, j-i+1);
                }
            }
        }
        ans.PB(best);
    }

    return ans;
}

vector<int> solve(){
    vector<int> ans;

    for(int o = 0; o<m; o++){
        int lim = k[o];

        vector<int> w;
        for(int i = 0; i<n; i++){
            w.PB(x[i]-lim);
        }

        vector<int> a;
        a.PB(0);
        for(int i = 0; i<n; i++){
            a.PB(a[i]+w[i]);
        }

        ll cur = ll_INF;
        vector<int> pref;
        for(int i = 0; i<=n; i++){
            if(a[i] < cur){
                pref.PB(i);
                cur = a[i];
            }
        }

        cur = -ll_INF;
        vector<int> suf;
        for(int i = n; i >= 0; i--){
            if(a[i] > cur){
                suf.PB(i);
                cur = a[i];
            }
        }

        int best = 0;
        int sufInd = 0;
        for(int i = pref.size()-1; i>=0; i--){
            while(a[pref[i]] > a[suf[sufInd]]){
                sufInd++;
            }
            best = max(best, (suf[sufInd] - pref[i]));
        }
        ans.PB(best);
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
        for(int i = 0; i<ansS.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: \n";
                cout<<ansB.size()<<"\n";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: \n";
                cout<<ansS.size()<<"\n";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}