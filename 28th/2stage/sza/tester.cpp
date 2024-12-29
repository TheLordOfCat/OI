#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PB push_back
#define MT make_tuple
#define PIC pair<int,char>

int n;
vector<tuple<int,int,char>> edges;

void getData(){
    edges.clear();

    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        char c;
        edges.PB(MT(a,b,c));
    }
}

void getRandom(){
    edges.clear();

    n = rand()%10+1;
    int ind = 2;
    for(int i = 1; i<n-1; i++){
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            char c = rand()%2 + 'A';
            edges.PB(MT(i,ind,c));
            ind++;
            if(ind>n){
                break;
            }
        }
        if(ind>n){
            break;
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<get<0>(edges[i])<<" "<<get<1>(edges[i])<<" "<<get<2>(edges[i])<<"\n";
    }
}

void genOpsBrute(vector<string>& ops){
    stack<string> S;
    while(!S.empty()){
        string s = S.top();
        S.pop();
        
        ops.PB(s);
        for(int i = 1; i>=0; i--){
            string temp = s;
            temp.PB('A' + i);

            S.push(temp);
        }
    }
}

void bfsBrute(string s, vector<bool>& marked, vector<vector<PIC>> &graph){
    for(int i = 1; i<=n; i++){
        vector<int> pr(n+1, 0);
        stack<PII> S;
        pr[i] = -1;
        for(int j = 0; j<graph[i].size(); j++){
            PIC cur = graph[i][j];
            if(cur.second == s.front()){
                S.push(MP(cur.first, 1));
                pr[cur.first] = i;
            }
        }

        while(!S.empty()){
            PII v = S.top();
            S.pop();

            if(v.second == s.size()){
                //backtrack
                int p = v.first;
                while(p != i){
                    marked[p] = true;
                    p = pr[p];
                }
                marked[i] = true;
            }else{
                for(int j = 0; j<graph[v.first].size(); j++){
                    PIC cur = graph[v.first][j];
                    if(pr[cur.first] == 0){
                        if(s[v.second] == cur.second){
                            S.push(MP(cur.first, v.second+1));
                            pr[cur.first] = v.first;
                        }
                    }
                }
            }
        }
    }
}

vector<string> brute(){
    //create graph
    vector<vector<pair<int,char>>> graph(n+1, vector<pair<int,char>>());
    for(int i =0 ; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]);
        char c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    //get ops
    vector<string> ops;
    genOpsBrute(ops);

    //vefrify
    vector<string> ans;

    for(int i = 0; i< ops.size(); i++){
        string s = ops[i];

        vector<bool> marked(n+1, false);
        bfsBrute(s, marked, graph);

        bool ok = true;
        for(int j = 1; j<=n; j++){
            if(!marked[j]){
                ok = false;
            }
        }
        if(ok){
            ans.PB(s);
        }
    }

    return ans;
}

vector<string> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"Test nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<string> ansB = brute();
        vector<string> ansS = solve();
        bool ok = true;
        if(ansB.size() != ansS.size()){
            ok = false;
        }else{
            for(int i = 0; i<ansB.size(); i++){
                if(ansB[i] != ansS[i]){
                    ok = false;
                    break;
                }
            }
        }
        if(!ok){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<ansB.size()<<"\n";
            for(int i =0 ; i<ansB.size(); i++){
                cout<<ansB[i]<<"\n";
            }
            cout<<"SOLVE: \n";
            cout<<ansS.size()<<"\n";
            for(int i =0 ; i<ansS.size(); i++){
                cout<<ansS[i]<<"\n";
            }
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}