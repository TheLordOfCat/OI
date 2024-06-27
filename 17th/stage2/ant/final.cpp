#include<iostream>
#include <vector>
#include <algorithm>
#include <string>

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
vector<int> s;

void getData(){
    cin>>n;

    string temp;
    cin>>temp;
    for(int i = 0; i<n; i++){
        if(temp[i] == '0'){
            s.PB(0);  
        }else{
            s.PB(1);
        }
    }
}

ull solve(){
    ull ans = 0;

    vector<int> S = s;
    S.insert(S.begin(), INF);
    S.PB(INF-1);
    vector<int> negS;
    for(int i = 0; i<S.size(); i++){
        if(S[i] == 0){
            negS.PB(1);
        }else if(S[i] == 1){
            negS.PB(0);
        }else{
            negS.PB(S[i] * (-1));
        }
    }

    //edited Manacher algorithm 
    vector<int> R(S.size(), 0);
    int i = 1;
    int j = 0;    
    while(i<=S.size()-1){
        while(S[i-j] == negS[i+j+1]) j++;
        R[i] = j;
        ans += j;
        int k = 1;
        while(R[i-k] != R[i] - k && k<=j){
            R[i+k] = min(R[i-k], R[i] - k);
            ans += min(R[i-k], R[i] - k);
            k++;
        }
        j = max(j-k, 0);
        i += k;
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    ull ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}