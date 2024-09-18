#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>
#include <tuple>
#include <string>

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
vector<vector<int>> graph;
vector<int> colour;

void input(int v, int &gloInd){
    int num = code[v];

    colour.PB(num);
    if(num == 4){
        for(int i = 0; i<4; i++){
            graph.PB(vector<int>());
            graph[v].PB(gloInd);
            gloInd++;
            input(gloInd-1, gloInd);
        }
    }
}

void inputRand(int v, int depth){
    int num;
    int type = rand()%3;
    if(type == 0){
        num = 0;
    }else if(type == 1){
        num = 1;
    }else if(depth != m){
        num = 4;
    }else{
        num = 0;
    }

    colour.PB(num);
    code.PB(num);

    if(num == 4){
        for(int i = 0; i<4; i++){
            graph.PB(vector<int>());
            graph[v].PB(v+i+1);
            inputRand(v+i+1, depth + 1);
        }
    }
}

void getData(){
    cin>>m;

    string temp;
    cin>>temp;
    for(int i = 0; i<temp.size(); i++){
        code.PB(temp[i] - '0');
    }

    graph.PB(vector<int>());
    int gloInd = 1;
    input(0, gloInd);
}

void getRandom(){
    m = rand()%2+3;

    graph.PB(vector<int>());
    inputRand(0, 0);
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
    vector<vector<int>> plane(1<<m, vector<int>(1<<m, -1));

    //fill the plane
    stack<tuple<int,int, PII>> S;
    S.push(MT(0,0,MP(0,0)));

    while(!S.empty()){
        int v = get<0>(S.top());
        int d = get<1>(S.top());
        PII cord = get<2>(S.top());
        S.pop();

        int c = colour[v];

        if(c == 4){
            S.push(MT(graph[v][0], d+1, MP(cord.first, cord.second + 2*(1<<(m-d-1)))));
            S.push(MT(graph[v][1], d+1, MP(cord.first + (1<<(m-d-1)), cord.second + 2*(1<<(m-d-1)))));
            S.push(MT(graph[v][2], d+1, MP(cord.first, cord.second + (1<<(m-d-1)))));
            S.push(MT(graph[v][3], d+1, MP(cord.first + (1<<(m-d-1)), cord.second + (1<<(m-d-1)))));
        }else{
            for(int i = cord.first; i<cord.first + (1<<(m-d)); i++){
                for(int j = cord.second; j<cord.second + (1<<(m-d)); j++){
                    plane[i][j] = c;
                }                
            }
        }
    }

    //check for connected parts
    PII ans = MP(0,0);

    vector<vector<bool>> vis(1<<m, vector<bool>(1<<m, false));
    for(int i = 0; i<1<<m; i++){
        for(int j = 0; j<1<<m; j++){
            if(!vis[i][j] && plane[i][j] == 1){
                int size = 0;
                stack<PII> S;
                S.push(MP(i,j));
                
                while(!S.empty()){
                    PII v = S.top();
                    S.pop();
                    size++;

                    if(i >= 1){
                        if(!vis[i-1][j] && plane[i-1][j] == 1){
                            S.push(MP(i-1,j));
                        }
                    }
                    if(i < (1<<m)-1){
                        if(!vis[i+1][j] && plane[i+1][j] == 1){
                            S.push(MP(i+1,j));
                        }
                    }
                    if(j >= 1){
                        if(!vis[i][j-1] && plane[i][j-1] == 1){
                            S.push(MP(i,j-1));
                        }
                    }
                    if(j < (1<<m)-1){
                        if(!vis[i][j+1] && plane[i][j+1] == 1){
                            S.push(MP(i,j+1));
                        }
                    }
                }

                ans.first++;
                ans.second = max(ans.second, size);
            }
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