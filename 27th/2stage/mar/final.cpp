#include <iostream>
#include <vector>
#include <string>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, m;
vector<int> digits;
vector<int> querys;

void getData(){
    cin>>n>>m;
    for(int i =0 ; i<n; i++){
        char c;
        cin>>c;
        digits.PB(c-'0');
    }
    for(int i =0 ; i<m; i++){
        int temp;
        cin>>temp;
        querys.PB(temp);
    }
}

int qSolve(int v, vector<int>& d,  vector<vector<int>>& dic){
    int R = 20;
    for(int i = max(v-R, 0); i<=v; i++){
        ll num = 0;
        for(int j = i; j<i+R && j<n; j++){
            if(d[j] == 1){
                num ^= (1<<(j-i));
            }
            if(j >= v){
                dic[j-i+1][num]--;
            }
        }
    }

    d[v] =  (d[v]+1)%2;
    for(int i = max(v-R, 0); i<=v; i++){
        ll num = 0;
        for(int j = i; j<i+R && j<n; j++){
            if(d[j] == 1){
                num ^= (1<<(j-i));
            }
            if(j >= v) dic[j-i+1][num]++;
        }
    }

    for(int l = 1; l<R; l++){
        int maxSize = (1<<l);
        bool ok = true;

        for(int i = 0; i<maxSize; i++){
            if(dic[l][i] == 0){
                ok = false;
                break;
            }
        }

        if(!ok){
            return l;
        } 
    }

    return -1;
}

vector<int> solve(){
    vector<int> ans;
    int R = 20;

    vector<int> digAlt = digits;
    vector<vector<int>> dic(R+1, vector<int>((1<<R)+1, 0));

    //initial traversal
    for(int i = 0; i<n; i++){
        ll num = 0;
        for(int j = i; j<i+R && j<n; j++){
            if(digAlt[j] == 1){
                num ^= (1<<(j-i));
            }
            dic[j-i+1][num]++;
        }
    }

    for(int l = 1; l<R; l++){
        int maxSize = (1<<l);
        bool ok = true;

        for(int i = 0; i<maxSize; i++){
            if(dic[l][i] == 0){
                ok = false;
                break;
            }
        }

        if(!ok){
            ans.PB(l);
            break;
        } 
    }

    if(ans.size() == 0) ans.PB(-1);

    //proces query
    for(int i = 0; i<querys.size(); i++){
        int temp = qSolve(querys[i]-1, digAlt, dic);
        ans.PB(temp);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<int> ansS = solve();
    for(int j =0; j<ansS.size(); j++){
        cout<<ansS[j]<<"\n";
    }

    return 0;
}