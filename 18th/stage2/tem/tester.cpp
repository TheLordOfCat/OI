#include<iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using ll = long long int;
using ull = unsigned long long int;

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;
const int MAXN = 1'000'0000;

int n;
vector<int> x;
vector<int> y;

void getData(){
    cin>>n;
    for(int i =0 ; i<n; i++){
        int a, b;
        cin>>a>>b;
        x.PB(a);
        y.PB(b);
    }
}

void getRandom(){
    srand(time(0));
    
    x.clear();
    y.clear();

    int range = 10;

    n = rand()%10+1;
    for(int i =0; i<n; i++){
        int a = rand()%10+1;
        int b=  rand()%10+1;
        if(a > b){
            swap(a,b);
        }
        x.PB(a);
        y.PB(b);
    }
}

int brute(){
    int ans = 0;
    for(int i = 0; i<n; i++){
        int len = 1;
        int cur = x[i];
        int j = i+1;
        while(j < n){
            if(y[j] >= cur){
                cur = max(cur, x[j]);
                len++;
                j++;
            }else{
                break;
            }
        }
        ans = max(ans,len);
    }
    return ans;
}

deque<PII> Q;
int QLen = 0;

void add(int v){
    QLen++;
    PII temp = MP(v,1);
    while(Q.size() > 0){
        if(Q.front().first <= temp.first){
            temp.second += Q.front().second;
            Q.pop_front();  
        }else{
            break;
        }
    }
    Q.push_front(temp);
}

void rem(){
    if(Q.back().second == 1){
        Q.pop_back();
    }else{
        Q.back().second--;
    }
    QLen--;
}

int curTemp(){
    if(Q.size() == 0){
        return -INF;
    }
    return Q.back().first;
}

int solve(){
    int ans = 0;
    add(x[0]);

    for(int i = 1; i<n; i++){
        if(curTemp() > y[i]){
            ans = max(ans, QLen);
            while(curTemp() > y[i]){
                rem();
            }
        }
        add(x[i]);
    }

    return ans;
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
        int ansB = brute();
        int ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        } 
        cout<<"CORRECT\n";
    }

    return 0;
}