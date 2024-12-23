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

void getRandom(){
    code.clear();

    m = rand()%2+1;

    stack<PII> S;
    S.push(MP(1, 0));
    int ind = 2;
    while(!S.empty()){
        PII v = S.top();
        S.pop();

        if(v.second == m){
            for(int i = 0; i<4; i++){
                code.PB(rand()%2);
            }
            continue;
        }

        int con = rand()%3;
        if(con == 0){
            code.PB(0);            
        }else if(con == 1){
            code.PB(1);
        }else if(con == 2){
            code.PB(4);
            for(int i = 0; i<4; i++){
                S.push(MP(ind, v.second+1));
                ind++;
            }
        }
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

PII brute(){
    vector<vector<int>> plane((1<<m), vector<int>((1<<m), 0));

    //fill the plane
    stack<pair<PII,int>> S;
    S.push(MP(MP(0,0), 0));
    int ind = 0;

    while(!S.empty()){
        PII pos = S.top().first;
        int depth = S.top().second;
        S.pop();

        if(code[ind] == 1){
            int len = (1<<(m-depth));
            for(int i = pos.first; i<pos.first + len; i++){
                for(int j = pos.second; j<pos.second+len; j++){
                    plane[i][j] = 1;
                }
            }
        }else if(code[ind] == 4){
            int len = (1<<(m-depth-1));
            S.push(MP(pos, depth+1));
            S.push(MP(MP(pos.first, pos.second+len), depth+1));
            S.push(MP(MP(pos.first+len, pos.second), depth+1));
            S.push(MP(MP(pos.first+len, pos.second+len), depth+1));
        }
        ind++;
    }

    //get ans
    PII ans = MP(0,0);
    vector<vector<bool>> used((1<<m), vector<bool>((1<<m), false));
    for(int i = 0; i<(1<<m); i++){
        for(int j = 0; j<(1<<m); j++){
            if(used[i][j] || plane[i][j] == 0){
                continue;
            }
            stack<PII> S;
            S.push(MP(i,j));
            used[i][j] = true;
            int area = 1;
            while(!S.empty()){
                PII v = S.top();
                S.pop();

                if(v.first > 0){
                    if(!used[v.first-1][v.second] && plane[v.first-1][v.second] == 1){
                        used[v.first-1][v.second] = true;
                        area++;
                        S.push(MP(v.first-1, v.second));
                    }
                }
                if(v.second > 0){
                    if(!used[v.first][v.second-1] && plane[v.first][v.second-1] == 1){
                        used[v.first][v.second-1] = true;
                        area++;
                        S.push(MP(v.first, v.second-1));
                    }
                }
                if(v.first+1 < (1<<m)){
                    if(!used[v.first+1][v.second] && plane[v.first+1][v.second] == 1){
                        used[v.first+1][v.second] = true;
                        area++;
                        S.push(MP(v.first+1, v.second));
                    }
                }
                if(v.second+1 < (1<<m)){
                    if(!used[v.first][v.second+1] && plane[v.first][v.second+1] == 1){
                        used[v.first][v.second+1] = true;
                        area++;
                        S.push(MP(v.first, v.second+1));
                    }
                }
            }

            ans.first++;
            ans.second = max(ans.second, area);
        }
    }

    return ans;
}

PII solve(){
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        PII ansB = brute();
        PII ansS = solve();
        if(ansB.first != ansS.first || ansB.second != ansS.second){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<ansB.first<<"\n"<<ansB.second<<"\n";
            cout<<"SOLVE: \n";
            cout<<ansS.first<<"\n"<<ansS.second<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}