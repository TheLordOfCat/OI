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

int leftInd = 0;
int rightInd = 0;

vector<int> leftOrien;
vector<int> rightOrien;

vector<bool> used;

int mark(int& ind, vector<int> num){
    while(used[num[ind]]){
        ind++;
    }
    
    used[num[ind]] = true;
    return num[ind];
}

void procesTile(PII countSame, PULLV& ans, int& lastInd){
    vector<int> vec;
    for(int j = 0; j<countSame.second; j++){
        if(countSame.first == 1){
            ans.first += opsCost[lastInd + j].second;
            int temp = mark(rightInd, rightOrien);
            vec.PB(temp);
        }else{
            ans.first += opsCost[lastInd + j].first;
            int temp = mark(leftInd, leftOrien);
            vec.PB(temp);
        }
    }

    for(int j = vec.size()-1; j>=0; j--){
        ans.second.PB(vec[j]);
        lastInd++;
    }
}

PULLV solve(){
    used.clear();
    leftInd = 0;
    rightInd = 0;
    leftOrien.clear();
    rightOrien.clear();

    PULLV ans = MP(0,vector<int>());
    ans.second.PB(s);

    PII countSame = MP(0,0);
    if(opsCost.front().first < opsCost.front().second){
        countSame = MP(0,1);
    }else{
        countSame = MP(1,1);
    }

    //before switch
    for(int i = 1; i<opsCost.size(); i++){
        int type;
        if(opsCost[i].first < opsCost[i].second){
            type = 0;
        }else{
            type = 1;
        }

        if(type == countSame.first){
            countSame.second++;
        }else{
            break;
        }
    }

    int ind = s;
    int lastInd = 0;

    used.assign(n+1, false);
    used[s] = true;

    for(int i = 1; i<=n; i++){
        leftOrien.PB(i);
        rightOrien.PB(n-i+1);
    }

    //switch
    PII dif = MP(0,INF);
    if(countSame.first == 0){
        if(countSame.second > s- leftInd){
            for(int i = 0; i<countSame.second; i++){
                if(opsCost[i].second < dif.second){
                    dif = MP(i, opsCost[i].second);
                }
            }
        }
    }else{
        PII dif = MP(-1,INF);
        if(countSame.second > n - s){
            for(int i = 0; i<countSame.second; i++){
                if(opsCost[i].first < dif.second){
                    dif = MP(i, opsCost[i].first);
                }
            }
        }
    }
    procesTile(MP(countSame.first, dif.first-1), ans, lastInd);
    if(dif.second != INF) procesTile(MP((countSame.first+1)%2, 1), ans, lastInd);
    procesTile(MP(countSame.first, countSame.second - (dif.first+1)), ans, lastInd);

    //after switch
    if(opsCost[lastInd].first < opsCost[lastInd].second){
        countSame = MP(0, 0);
    } else{
        countSame = MP(1, 0);
    }

    for(int i = lastInd; i<opsCost.size(); i++){
        int type;
        if(opsCost[i].first < opsCost[i].second){
            type = 0;
        }else{
            type = 1;
        }

        if(type != countSame.first){
            procesTile(countSame, ans, lastInd);

            countSame = MP(type, 0);
            lastInd = i;
        }

        if(type == countSame.first){
            countSame.second++;
        }

        if(i == opsCost.size()-1){
            procesTile(countSame, ans, lastInd);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    PULLV ansS = solve();
    cout<<ansS.first<<"\n";
    for(int i = 0; i<ansS.second.size(); i++){
        cout<<ansS.second[i]<<" ";
    }
    cout<<"\n";


    return 0;
}