#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>
#include <tuple>
#include <string>
#include <map>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back
#define MT make_tuple

const int MOD = 1'000'000'007;

int m;
vector<int> code;

void getData(){
    code.clear();

    cin>>m;

    string temp;
    cin>>temp;
    for(int i =0 ; i<temp.size(); i++){
        code.PB(temp[i]-'0');
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<m<<"\n";
    for(int i = 0; i<code.size(); i++){
        cout<<code[i];
    }
    cout<<"\n";
}

struct xDominant {
    bool operator()(const pair<PII,int>& a, const pair<PII,int>& b) const {
        if (a.first.first != b.first.first)
            return a.first.first < b.first.first;
        return a.first.second < b.first.second;
    }
};

struct yDominant {
    bool operator()(const pair<PII,int>& a, const pair<PII,int>& b) const {
        if (a.first.second != b.first.second)
            return a.first.second < b.first.second;
        return a.first.first < b.first.first;
    }
};

PII solve(){
    int maxDepth = 0;

    //fill the plane
    vector<vector<int>> graphBlock(code.size(), vector<int>());
    for(int i = 0; i<code.size(); i++){
        if(code[i] == 4){
            graphBlock[i].PB(i+1);
            graphBlock[i].PB(i+2);
            graphBlock[i].PB(i+3);
            graphBlock[i].PB(i+4);
        }
    }
    
    vector<PII> posBlockX(code.size(), MP(-1,-1));
    int globalInd = 0;
    stack<tuple<int,int,bool>> S;
    S.push(MT(0,0, false));
    while(!S.empty()){
        int v = get<0>(S.top()), type = get<1>(S.top());
        bool b = get<2>(S.top());
        S.pop();

        if(b){
            if(code[v] == 4){
                int maxim = 0, minim = 0;
                for(int i =0 ; i<graphBlock[v].size(); i++){
                    int cur = graphBlock[v][i];
                    maxim = max(maxim, posBlockX[cur].second);
                    minim = min(minim, posBlockX[cur].first);
                }
                posBlockX[v] = MP(minim, maxim);
            }else{
                if(type == 0 || type == 2){
                    posBlockX[v] = MP(globalInd, globalInd+1);
                    globalInd++;
                }else if(type == 1 || type == 3){
                    posBlockX[v] = posBlockX[v-1];
                }
            }
        }

        S.push(MT(v,type, true));
        if(graphBlock[v].size() == 4){
            S.push(MT(graphBlock[v][0], 0, false));
            S.push(MT(graphBlock[v][1], 1, false));
            S.push(MT(graphBlock[v][2], 2, false));
            S.push(MT(graphBlock[v][3], 3, false));
        }
    }

    //get area size
    stack<pair<PII,bool>> Q;
    Q.push(MP(MP(0,0),false));
    while(!Q.empty()){
        PII v = Q.top().first;
        bool b = Q.top().second;
        Q.pop();

        if(b){
            if(code[v.first] == 4){

            }else{
                
            }
        }

        Q.push(MP(v,true));
        if(code[v.first] == 4){
            Q.push(MP(MP(v.first+1, v.second+1), false));
            Q.push(MP(MP(v.first+2, v.second+1), false));
            Q.push(MP(MP(v.first+3, v.second+1), false));
            Q.push(MP(MP(v.first+4, v.second+1), false));
        }
    }
   
    //rotate
    vector<PII> posBlockY(code.size(), MP(-1,-1));
    for(int i = 0; i<posBlockX.size(); i++){
        posBlockY[i] = MP(globalInd-posBlockX[i].first, globalInd-posBlockX[i].second);
    }
    
    //create graph
    set<pair<PII,int>, xDominant> sX;
    set<pair<PII,int>, yDominant> sY;

    for(int i = 0; i<code.size(); i++){
        sX.insert(MP(MP(posBlockX[i].first, posBlockY[i].first), i));
        sX.insert(MP(MP(posBlockX[i].second, posBlockY[i].second), i));
        sY.insert(MP(MP(posBlockX[i].first, posBlockY[i].first), i));
        sY.insert(MP(MP(posBlockX[i].second, posBlockY[i].second), i));
    }



    //get ans

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    PII ansS = solve();
    cout<<ansS.first<<"\n"<<ansS.second<<"\n";

    return 0;
}