#include<iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int ALPHA = 26;
const int INF = 2'000'000'000;

int n;
vector<char> s;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        char temp;
        cin>>temp;
        s.PB(temp);
    }
}

int solve(){
    int ans = 0;

    vector<vector<int>> next(26, vector<int>());
    for(int i = 0; i<n; i++){
        next[s[i] - 'a'].PB(i);
    }

    for(int i = 0; i<ALPHA; i++){
        next[i].PB(INF);
    }

    for(int l = 0; l<ALPHA; l++){
        for(int k = 0; k<ALPHA; k++){

            if(next[l].size() > 0 && next[k].size() > 0 ){
                int sum = 0, mini = INF, lastSum = 0;
                int len = next[l].size() + next[k].size();                
                int itrL = 0, itrK = 0;

                for(int  i = 0; i<len; i++){
                    if(next[k][itrK] > next[l][itrL]){
                        sum += 1;
                        itrL++;
                    }else if(next[k][itrK] != INF){
                        sum -= 1;
                        itrK ++;
                        mini = min(mini, lastSum);
                        lastSum = sum;
                    }
                    ans = max(ans, sum - mini);
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    int ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}