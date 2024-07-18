#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#include <cstdlib>
#include <ctime>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using ll = long long int;
using ull = unsigned long long int;

int n, q;
vector<int> k;
vector<int> a; 

void getData(){
    cin>>n>>q;
    for(int i = 0; i <q; i++){
        int temp;
        cin>>temp;
        k.PB(temp);
    }
    for(int i =0; i<n-1; i++){
        int temp;
        cin>>temp;
        a.PB(temp);
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    q = rand()%3+1;

    for(int i = 0; i<q; i++){
        int temp = rand()%10+1;
        k.PB(temp);
    }
    
    for(int i = 0; i<n; i++){
        int temp = rand()%10+1;
        a.PB(temp);
    }
}

void printData(){
    cout<<"\nDATA: \n";
    cout<<n<<" "<<q<<"\n";
    for(int i = 0; i<q; i++){
        cout<<k[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

struct Compare {
    bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        return p1.second < p2.second;
    }
};

vector<int> brute(){
    //build the tree
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<n-1; i++){
        graph[a[i]].PB(i+2);
    }

    //getting the depths
    vector<int> depth(n+1, 0);
    stack<pair<int,bool>> S;
    S.push(MP(1,false));
    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();
        if(b){
            int temp = 0;
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                temp = max(temp, depth[cur] + 1);
            }
            depth[v] = temp;
            continue;
        }

        S.push(MP(v,true));
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            S.push(MP(cur, false));
        }
    }

    //iterate through k
    vector<int> ans;
    for(int i = 0; i<q; i++){
        priority_queue<PII, vector<PII>, Compare> Q;
        Q.push(MP(1,depth[1]));
        int turns = 0;
        while(Q.size() > 0){
            turns++;
            vector<int> used;
            for(int j = 0; j<k[i]; j++){
                used.PB(Q.top().first);
                Q.pop();
                if(Q.size() <= 0){
                    break;
                }
            }
            for(int j = 0; j<used.size(); j++){
                for(int o = 0; o<graph[used[j]].size(); o++){
                    int cur = graph[used[j]][o];
                    Q.push(MP(cur, depth[cur]));
                }
            }
        }
        ans.PB(turns);
    }    

    return ans;
}

vector<int> solve(){
    vector<int> opsTurns(n+1, 0);

    vector<PII> blocks(n+1, MP(0,0));
    for(int i = 0; i<n; i++){
        blocks.PB(MP(a[i], 1));
    }

    for(int op = n; op >0; op--){
        int len = 0;
        vector<PII> nextBlocks;

        int delta = 0;
        for(int i = 0; i<blocks.size(); i++){
            if(blocks[i].first >= op){
                //too many blocks
                delta += (blocks[i].first - op) * blocks[i].second;
                if(nextBlocks.size() > 0){
                    if(nextBlocks.back().first == op){
                        nextBlocks.back().second += blocks[i].second;
                    }else{
                        nextBlocks.PB(MP(op, blocks[i].second));
                    }
                }else{
                    nextBlocks.PB(MP(op, blocks[i].second));
                }

            }else{
                //too little blocks
                int excess = (op - blocks[i].first) * blocks[i].second;
                if(excess >= delta){
                    vector<PII> parts;

                    //part 1
                    int num = delta/(op - blocks[i].first);
                    parts.PB(MP(op, num));
                    delta -= (op - blocks[i].first)* num;
                    // part 2
                    if(delta > 0) parts.PB(MP(delta, 1));
                    //part 3
                    if(delta > 0){
                        parts.PB(MP(blocks[i].first, blocks[i].second - 1 - num));
                    }else{
                        parts.PB(MP(blocks[i].first, blocks[i].second - num));
                    }

                    if(nextBlocks.size() > 0){
                        if(nextBlocks[nextBlocks.size()-1].first == parts[0].first){
                            nextBlocks[nextBlocks.size()-1].second += parts[0].second;
                        }else{
                            nextBlocks.PB(MP(op, parts[0].second));
                        }
                    }else{
                        nextBlocks.PB(MP(op, parts[0].second));
                    }

                    for(int i = 1; i<parts.size(); i++){
                        nextBlocks.PB(MP(parts[i].first, parts[i].second));
                    }

                    delta = 0;
                }else{
                    if(nextBlocks.size() > 0){
                        if(nextBlocks.back().first == op){
                            nextBlocks.back().second += blocks[i].second;
                        }else{
                            nextBlocks.PB(MP(op, blocks[i].second));
                        }
                    }else{
                        nextBlocks.PB(MP(op, blocks[i].second));
                    }
                    
                    delta -= excess;
                }
            }
            len += blocks[i].second;
        }

        if(delta > 0){
            vector<PII> parts;
            //part 1
            int num = delta/op;
            nextBlocks.back().second += num;

            len += num;
            delta -= op*num;
            // part 2
            if(delta > 0){
                nextBlocks.PB(MP(delta, 1));
                len += 1;
            }
        }

        blocks = nextBlocks;
        opsTurns[op] = len; 
    }

    vector<int> ans;
    for(int i = 0; i<q; i++){
        ans.PB(opsTurns[k[i]]);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<q; i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
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
        cout<<"CORRECT\n";
    }

    return 0;
}