#include<iostream>
#include<vector>
#include <stack>
#include <queue>

#include <cstdlib>
#include <ctime>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

int n, q;
vector<int> parent;
vector<int> k;

void getData(){
    cin>>n>>q;

    for(int i = 0; i<q; i++){
        int temp;
        cin>>temp;
        k.PB(temp);
    }

    parent.PB(-1);
    parent.PB(-1);
    for(int i = 2; i<=n; i++){
        int temp;
        cin>>temp;
        parent.PB(temp);
    }
}

void getRandom(){
    srand(time(0));
    n = rand()%10+1;
    q = rand()%10+1;
    for(int i = 0; i<q; i++){
        int temp = rand()%10+1;
        k.PB(temp);
    }
    parent.clear();
    parent.PB(-1);
    parent.PB(-1);
    for(int i = 2; i<=n; i++){
        int temp = rand()%i+1;
        if(temp == i) temp--;
        parent.PB(temp);
    }
}

void printData(){
    cout<<n<<" "<<q<<"\n";
    for(int i = 0; i<q; i++){
        cout<<k[i]<<" ";
    }
    cout<<"\n";
    for(int i = 2;i<=n; i++){
        cout<<parent[i]<<" ";
    }
    cout<<"\n";
}

struct CustomComparator {
    bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        if (p1.second == p2.second) {
            return p1.first > p2.first;
        }
        return p1.second < p2.second;
    }
};

vector<int> brute(){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 2; i<=n; i++){
        graph[parent[i]].PB(i);
    }

    vector<int> maxDepth(n+1,0);
    stack<pair<int,bool>> S;
    S.push(MP(1,false));

    //filing maxDepth
    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();
        if(b){
            for(int i = 0; i<graph[v].size(); i++){
                maxDepth[v] = max(maxDepth[v], maxDepth[graph[v][i]]+1);
            }
        }else{
            S.push(MP(v,true));
            for(int i = 0; i<graph[v].size(); i++){
                S.push(MP(graph[v][i],false));
            }
        }
    }

    //simulating
    vector<int> ans;
    for(int i =0 ; i<q; i++){
        int turns = 0;
        int left = n;
        priority_queue<PII> Q;
        Q.push(MP(1,maxDepth[1]));

        while(left > 0){
            vector<int> next;
            for(int j = 0; j<k[i]; j++){
                if(!Q.empty()){
                    next.PB(Q.top().first);
                    Q.pop();
                    left--;
                }else{
                    break;
                }
            }
            turns++;
            for(int j = 0; j<next.size(); j++){
                for(int o = 0; o <graph[next[j]].size(); o++){
                    int cur = graph[next[j]][o];
                    Q.push(MP(cur, maxDepth[cur]));
                }
            }
        }
        ans.PB(turns);
    }

    return ans;
}

vector<int> solve(){

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
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERRROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                return 0;
            }
        }
        cout<<"COORECT\n";
    }

    return 0;
}