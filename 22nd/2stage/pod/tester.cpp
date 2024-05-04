#include<iostream>
#include <vector>

#include <cstdlib>
#include <ctime>

using namespace std;

using ull = unsigned long long int;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

const int INF = 2'000'000'000;
const int MAXN = 1'000'000;
const int MAXK = 1'000'000;

int n, k;
vector<int> r;

void getData(){
    cin>>n>>k;
    for(int i = 0; i<n; i++){
        int a;
        cin>>a;
        r.PB(a);
    }
}

void getRandom(){
    srand(time(0));
    n = rand()%10+1;
    k = rand()%10+1;
    vector<bool> used(k+1, false);
    for(int i = 0; i<n; i++){
        int a = rand()%k+1;
        used[a] = true;
        r.PB(a);
    }
    for(int i = 1; i<=k; i++){
        if(!used[i]){
            r.PB(i);
            used[i] = true;
            n++;
        }
    }
}

pair<ull, int> brute(){
    vector<int> total(k+1, 0);
    for(int i = 0; i<n; i++){
        total[r[i]]++;
    }

    pair<ull,int> ans = MP(0,INF);
    for(int i = 0; i<n; i++){
        vector<int> count(k+1, 0);
        for(int j =i; j<n; j++){
            count[r[i]]++;
            bool ok = true;
            for(int o = 1; o<=k; o++){
                if(!(count[o] == 0 || count[o] == total[o])){
                    ok = false;
                    break;
                }
            }
            if(ok){
                ans.first++;
                ans.second = min(ans.second, j-i+1);
            }
        }
    }
    return ans;
} 

int tree[4*MAXN+1];
int detph = 1;
int R = 1;

int parent(int v){
    return v/2;
}

int left(int v){
    return 2*v;
}

int right(int v){
    return 2*v+1;
}

int leaf(int v){
    return R+v;
}

PII coveredRange(int v, int d){
    PII ans = MP(v,v);
    ans.first *= 1<<(detph-d);
    ans.second =ans.first += (1<<d) - 1;
    return ans;
} 

pair<ull,int> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        pair<ull, int> ansB = brute();
        pair<ull, int> ansS = solve();
        if(ansB.first != ansS.first && ansB.second != ansS.second){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB.first<<" "<<ansB.second<<"\n";
            cout<<"SOLVE: "<<ansS.first<<" "<<ansS.second<<"\n";
        }
        cout<<"CORRECT\n";
    }

    return 0;
}