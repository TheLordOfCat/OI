#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back
#define PIV pair<int,vector<int>>

int n, s;
vector<int> a;

void getData(){
    a.clear();

    cin>>n>>s;
    for(int i =0 ; i<n; i++){
        int temp;
        cin>>temp;
        a.PB(temp);
    }
}

void getRandom(){
    a.clear();
    
    srand(time(0));

    n = rand()%10+1;
    s = rand()%10+2;
    for(int i =0 ; i<n; i++){
        int temp = rand()%20+1;
        a.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<s<<"\n";
    for(int i =0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

PIV brute(){
    PIV ans = MP(INF, vector<int>());
    vector<int> perm;
    for(int i = 0; i<n; i++){
        perm.PB(i);
    }

    do{
        int skips = 0;
        int cur = 0;
        for(int i = 0; i<perm.size(); i++){
            if(cur == s-1){
                skips++;
                cur = 0;
            }
            cur += (a[perm[i]]+1)%s;
        }

        if(skips < ans.first){
            ans.first = skips;
            vector<int> temp;
            for(int i = 0; i<perm.size(); i++){
                temp.PB(perm[i]+1);
            }
            ans.second = temp;
        }

    }while(next_permutation(perm.begin(), perm.end()));
    
    return ans;
}

struct comparePII{
    bool operator()(const PII a, const PII b){
        if(a.second == b.second){
            return a.first < b.first;
        }
        return a.second < b.second;
    }
};

PIV solve(){
    vector<vector<int>> index(s+1, vector<int>());
    vector<PII> poems;
    for(int i = 0; i<s; i++){
        poems.PB(MP(i,0));
    }
    for(int i = 0; i<n; i++){
        poems[(a[i]+1)%s].second++;
        index[(a[i]+1)%s].PB(i+1);
    }

    priority_queue<PII, vector<PII>, comparePII> Q;
    for(int i = 0; i<s; i++){
        if(poems[i].second != 0){
            Q.push(poems[i]);
        }
    }

    PIV ans = MP(0,vector<int>());

    int cur = 0;
    while(!Q.empty()){
        PII v = Q.top();
        Q.pop();
        if(cur + v.first == s-1 && !(Q.size() == 0 && v.second == 1)){
            if(Q.size() > 0){
                PII b = Q.top();
                Q.pop();

                ans.second.PB(index[b.first].back());
                index[b.first].pop_back();
                b.second--;
                cur += b.first;
                if(b.second != 0) Q.push(b);
            }else{
                ans.first++;
                
                ans.second.PB(index[v.first].back());
                index[v.first].pop_back();
                v.second--;
                cur += v.first + 1;
            }
        }else{
            ans.second.PB(index[v.first].back());
            index[v.first].pop_back();
            v.second--;
            cur += v.first;
        }
        if(v.second != 0) Q.push(v);
    
        cur = cur%s;
    }

    return ans;
}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 10; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        PIV ansB = brute();
        PIV ansS = solve();
        if(ansB.first != ansS.first){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<ansB.first<<"\n";
            for(int i = 0; i<ansB.second.size(); i++){
                cout<<ansB.second[i]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: \n";
            cout<<ansS.first<<"\n";
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