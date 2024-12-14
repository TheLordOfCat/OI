#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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

void correctOps(vector<int>& ops, PII con){
    if(con.first == 0){
        PII minOps = MP(-1, INF);
        for(int i = 0; i< con.second; i++){
            if(minOps.second > opsCost[i].second){
                minOps = MP(i,opsCost[i].second);
            }
        }        
        ops[minOps.first] = 1;
    }else{
        PII minOps = MP(-1, INF);
        for(int i = 0; i< con.second; i++){
            if(minOps.second > opsCost[i].second){
                minOps = MP(i,opsCost[i].second);
            }
        }        
        ops[minOps.first] = 0;
    }
}

PULLV solve(){
    vector<int> ops;
    for(int i = 0; i<opsCost.size(); i++){
        if(opsCost[i].first < opsCost[i].second){
            ops.PB(0);
        }else{
            ops.PB(1);
        }
    }

    //first consecutive
    PII firstCon = MP(ops.front(), 1);
    for(int i = 1; i<ops.size(); i++){
        if(ops[i] == firstCon.first){
            firstCon.second++;
        }else{
            break;
        }
    }

    //correct if needed
    if(firstCon.first == 0){
        if(firstCon.second < s){
            correctOps(ops, firstCon);
        }
    }else{
        if(firstCon.second < n-s){
            correctOps(ops, firstCon);            
        }
    }

    //finish
    PULLV ans = MP(0, vector<int>());
    PII con = MP(ops.front(), 1);
    deque<int> Q;
    for(int i = 1; i<=n; i++) Q.PB(i);

    for(int i = 1; i<ops.size(); i++){
        if(ops[i] == con.first){
            con.second++;
        }else{
            vector<int> moves;
            if(con.first == 0){
                for(int i = 0; i<con.second; i++){
                    if(Q.front() == s){
                        i--;
                    }else{
                        moves.PB(Q.front());
                    }
                    Q.pop_front();
                }
            }else{
                for(int i = 0; i<con.second; i++){
                    if(Q.back() == s){
                        i--;
                    }else{
                        moves.PB(Q.back());
                    }
                    Q.pop_back();
                }
            }

            while(moves.size() > 0){
                ans.second.PB(moves.back());
                moves.pop_back();
            }

            con = MP(ops[i],1);
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