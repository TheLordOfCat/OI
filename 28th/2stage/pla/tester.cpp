#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PB push_back

int n, X, z;
vector<int> x;
vector<int> k;

void getData(){
    x.clear();
    k.clear();

    cin>>n>>X>>z;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0; i<z; i++){
        int temp;
        cin>>temp;
        k.PB(temp);
    }
}

void getRandom(){
    x.clear();
    k.clear();

    srand(time(0));

    n = rand()%10+2;
    X = rand()%10+1;
    z = rand()%10+1;

    vector<bool> used(n+1, false);
    used[0] = true; used[n] = true;

    x = {0,X};
    for(int i = 0; i<n; i++){
        int a = 0;
        while(used[a]){
            a = rand()%n+1;
        }
        x.PB(a);
    }
    sort(x.begin(), x.end());

    for(int i = 0; i<z; i++){
        int temp = rand()%10+1;
        k.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<X<<" "<<z<<"\n";
    for(int i = 0; i<x.size(); i++){
        cout<<x[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<k.size(); i++){
        cout<<k[i]<<" ";
    }
    cout<<"\n";
}

bool compareQuery(PLL a, PLL b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    return a.first < b.first;
}

vector<PLL> brute(){
    vector<PLL> ans(k.size(), MP(0,0));

    //avoid fractions
    ll maxDiv = 1<<30;
    vector<ll> pla;
    for(int i = 0; i < x.size(); i++){
        ll temp = x[i];
        temp *= maxDiv;
        pla.PB(temp);
    }

    //sort querys
    vector<PLL> querys;
    for(int i = 0; i<k.size(); i++){
        querys.PB(MP(k[i], i));
    } 

    sort(querys.begin(), querys.end(), compareQuery);

    int ind = 0;
    for(int i = 0; i<querys.size(); i++){
        PLL bestDist = MP(-1,-1);
        
        while(ind != querys[i].first){
            ind++;
            bestDist = MP(-1,-1);

            //fiding the best place
            for(int j = 1; j<pla.size(); j++){
                ll len = pla[j] - pla[j-1];
                if(len > bestDist.first){
                    bestDist.first = len;
                    bestDist.second = pla[j-1]+len/2;
                }
            }

            pla.PB(0);
            for(int j = 1; j<pla.size(); j++){
                ll len = pla[j] - pla[j-1];
                if(len == bestDist.first){
                    for(int o = pla.size()-1; o>j; o--){
                        pla[o] = pla[o-1];
                    }
                    pla[j] = pla[j-1] + len/2;
                    break;
                }
            }

        }

        //back to fractions
        int pwr = 30;
        while(bestDist.second %2 == 0 && pwr > 0){
            bestDist.second /= 2;
            pwr--;
        }
        ans[querys[i].second] = MP(bestDist.second, (1<<pwr));
    }

    return ans;
}

vector<PLL> solve(){

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
        vector<PLL> ansB = brute();
        vector<PLL> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j].first<<"/"<<ansB[j].second<<"  ";
                } 
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j].first<<"/"<<ansS[j].second<<"  ";
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