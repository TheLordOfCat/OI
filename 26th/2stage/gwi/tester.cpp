#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdlib>
#include <ctime>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF =  9'000'000'000'000'000'000;
const ull ullINF =  18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PIV pair<int,vector<int>>
#define PLLV pair<ll,vector<int>>
#define PULLV pair<ull,vector<int>>
#define PB push_back

int n, s;
vector<PII> opsCost;

void getData(){
    cin>>n>>s;
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        opsCost.PB(MP(a,b));
    }
}

void getRandom(){
    opsCost.clear();

    srand(time(0));

    n = rand()%10+1;
    s = rand()%n+1;
    for(int i = 0; i<n-1; i++){
        int a, b;
        a = rand()%10+1;
        b = rand()%10+1;
        opsCost.PB(MP(a,b));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<s<<"\n";
    for(int i = 0; i<opsCost.size(); i++){
        cout<<opsCost[i].first<<" "<<opsCost[i].second<<"\n";
    }
}

PULLV brute(){
    PULLV ans = MP(ullINF, vector<int>());

    ll totalComb = 1<<(n-1);
    for(int i = 0; i<totalComb; i++){
        bool ok = true;

        vector<bool> used(n+1, false);
        used[s] = true;
        
        ull sum = 0;
        vector<PII> turns;
        for(int j = 0; j<n-1; j++){
            if(i & (1<<j)){
                sum += opsCost[j].first;
                
                if(turns.size() > 0){
                    if(turns.back().first == 1){
                        turns.back().second++;
                    }else{
                        turns.PB(MP(1,1));
                    }
                }else{
                    turns.PB(MP(1,1));
                }
            }else{
                sum += opsCost[j].second;

                if(turns.size() > 0){
                    if(turns.back().first == 0){
                        turns.back().second++;
                    }else{
                        turns.PB(MP(0,1));
                    }
                }else{
                    turns.PB(MP(0,1));
                }
            }
        }
        vector<int> vec = {s};

        for(int o = 0; o<turns.size(); o++){
            int v = vec.back();
            vector<int> temp;
            int ind = 0;

            if(turns[o].first == 0){
                for(int j = 1; j<=n; j++){
                    if(ind == turns[o].second){
                        break;
                    }
                    if(j == v){
                        ok = false;
                        break;
                    }
                    if(!used[j]){
                        used[j] = true;
                        temp.PB(j);
                        ind++;
                    }
                }
            }else{
                for(int j = n; j>=1; j--){
                    if(ind == turns[o].second){
                        break;
                    }
                    if(j == v){
                        ok = false;
                        break;
                    }
                    if(!used[j]){
                        used[j] = true;
                        temp.PB(j);
                        ind++;
                    }
                }
            }

            if(!ok) break;
            for(int j = temp.size()-1; j>=0; j--){
                vec.PB(temp[j]);
            }
        }

        if(!ok){
            continue;
        }

        if(sum < ans.first){
            ans.first = sum;
            ans.second = vec;
        }
    }

    return ans;
}

PULLV solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<"\n";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        PULLV ansB = brute();
        PULLV ansS = solve();
        if(ansB.first != ansS.first){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n"<<ansB.first<<"\n";
            for(int i = 0; i<ansB.second.size(); i++){
                cout<<ansB.second[i]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: \n"<<ansS.first<<"\n";
            for(int i = 0; i<ansS.second.size(); i++){
                cout<<ansS.second[i]<<" ";
            }
            cout<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}