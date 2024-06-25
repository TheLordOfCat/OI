#include<iostream>
#include <algorithm>
#include <vector>
#include <stack>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n;
vector<int> input;

vector<pair<int,vector<int>>> graph;
vector<int> leaves;
vector<int> leavesIndex;

void getData(){
    cin>>n;

    for(int i = 0; i<n; i++){
        int o;
        cin>>o;
        input.PB(o);
    }
}

void getRandom(){
    srand(time(0));

    input.clear();

    n = rand()%10+1;

    vector<bool> used(n+1, false);
    int last = 1;
    stack<int> S;
    S.push(last);
    while(!S.empty()){
        int v = S.top();
        S.pop();

        if(S.size() == n){
            int l = n;
            while(!used[l]){
                l = rand()%n+1;
            }
            used[l] = true;
            input.PB(l);
        }else{
            S.push(last+1);
            S.push(last+2);
            last += 2;
            input.PB(0);
        }
    }
}

void printData(){
    cout<<n<<"\n";

    stack<int> S;
    S.push(1);
    while(!S.empty()){
        int v = S.top();
        S.pop();

        cout<<graph[v].first<<"\n";
        for(int i = 0; i<graph[v].second.size(); i++){
            int cur = graph[v].second[i];
            S.push(cur);
        }
    }
}

ll brute(){
    //creating graph
    int last = 1;
    stack<int> S;
    S.push(1);
    graph.assign(1, pair<int,vector<int>>());
    leavesIndex.assign(n+1, -1);

    int ind = 0;

    while(!S.empty()){
        int v = S.top();
        S.pop();
        
        int o = input[ind];
        ind++;

        graph[v].first = o;
        if(o == 0){
            S.push(last+1);
            graph[v].second.PB(last+1);
            S.push(last+2);
            graph[v].second.PB(last+2);
            last += 2;
        }else{
            leaves.PB(o);
            leavesIndex[o] = leaves.size()-1;
        }
    }

    //geting ranges covered by each node
    vector<PII> range(graph.size()+1, MP(0,0));
    
    stack<pair<int,bool>> S;
    S.push(MP(1,false));
    
    int lastLeaf = 1;

    while(!S.empty()){
        int v = S.top().first;
        int b =  S.top().second;
        S.pop();

        if(graph[v].first == 0){
            range[v] = MP(lastLeaf,lastLeaf);
            lastLeaf++;
            continue;
        }
        if(b){
            range[v] = MP(range[graph[v].second[0]].first, range[graph[v].second[1]].second);
            continue;
        }

        S.push(MP(v,true));
        for(int i = 0; i<graph[v].second.size(); i++){
            int cur = graph[v].second[i];
            S.push(MP(cur,false));
        }
    }

    //travering through each node and finding inverions
    ll ans = 0;

    stack<int> T;
    T.push(1);
    while(!T.empty()){
        int v = T.top();
        T.pop();

        PII left = range[graph[v].second[0]];
        PII right = range[graph[v].second[1]];

        //getting inversions
        ll totalInv = 0;
        for(int i = left.first; i<= left.second; i++){
            for(int j  = right.first; j<= right.second; j++){
                if(leaves[i] > leaves[j]){
                    totalInv++;
                }
            }
        }

        //checking for rotation
        ll allCom = (left.second - left.first +1)* (right.second - right.first +1);
        ans += min(allCom - totalInv, totalInv);
    }

    return ans;
}

struct node{
    int count;
    node *left;
    node *right;
    node(int count=1): count(count), left(NULL), right(NULL) {};
};

ll count(node *A){
    if(A == NULL){
        return 0;
    }else{
        return A->count;
    }
}

ll inv1 = 0;
ll inv2 = 0;

node* merge(node* A, node* B){
    if(A == NULL){
        return B;
    }
    if(B == NULL){
        return A;
    }
    node* ans = new node(0);
    ans-> count = count(A)  + count(B);
    ans ->left = merge(A->left, B->left);
    ans -> right = merge(A->right, B->right);

    inv1 += count(A->left) * count(B->right);
    inv2 += count(A->right) * count(B->left);

    delete A;
    delete B;

    return ans;
}

node* createTree(){

}

ll solve(){
    ll ans = 0;

    

    return ans;
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
        ll ansB = brute();
        ll ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }
    return 0;
}