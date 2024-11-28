#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;

int n;
vector<vector<int>> cards;
int m;
// vector<PII> query;

void getData(){
    cards.clear(); 
    // query.clear();

    cin>>n;
    cards.PB({-1,-1});
    for(int i = 0; i<n; i++){
        int a, b;
        cin>>a>>b;
        cards.PB({a,b});
    }    
    cin>>m;
    // for(int i =0; i<m; i++){
    //     int a, b;
    //     cin>>a>>b;
    //     query.PB(MP(a,b));
    // }
}

vector<vector<bool>> tree[524287 + 1];
PII range[524287 + 1];
int R;

int parent(int v){
    return v/2;
}

int left(int v){
    return v*2;
}

int right(int v){
    return 2*v+1;
}

int leaf(int v){
    return v+R;
}

vector<vector<bool>> combine(int vL, int vR){
    vector<vector<bool>> matrix(2, vector<bool>(2, false));
    vector<vector<bool>> a = tree[vL], b = tree[vR];

    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){
            bool ok = false;

            for(int o = 0; o<2; o++){
                for(int k = 0; k<2; k++){

                    if(a[i][o] && b[k][j]){
                        if(cards[range[vL].second][o] <= cards[range[vR].first][k]){
                            ok = true;
                            break;
                        }
                    }

                }

                if(ok) break;
            }

            matrix[i][j] = ok;
        }
    }

    return matrix;
}

void buildTree(){
    R = 0;
    int depth = 0;
    while((1<<depth) < n){
        R += (1<<depth); 
        depth++;
    }

    while(cards.size() <= (1<<depth)) cards.PB({INF,INF});
    // vector<vector<bool>> matrix(2, vector<bool>(2, true));
    // tree.assign(R + (1<<depth) + 1, matrix);
    // range.assign(R + (1<<depth) + 1, MP(-1,-1));

    for(int i = R + (1<<depth); i>= 1; i--){
        if(i > R){
            tree[i] = {{true,false}, {false,true}};
            range[i] = MP(i- R,i - R); 
        }else{
            range[i].first = range[left(i)].first;
            range[i].second = range[right(i)].second;
            tree[i] = combine(left(i), right(i));
        }
    }
}

void updateTree(int v){
    int V = leaf(v);
    V = parent(V);

    while(V >= 1){
        vector<vector<bool>> matrix = combine(left(V), right(V));
        tree[V] = matrix;
        range[V] = MP(range[left(V)].first, range[right(V)].second);
        V = parent(V);
    }   
}

bool queryTree(){
    bool ans = false;
    if(tree[1][0][0] || tree[1][0][1] || tree[1][1][0] || tree[1][1][1]){
        ans = true;
    }
    return ans;
}

vector<bool> solve(){
    vector<bool> ans;

    buildTree();
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;

        // int s1 = query[i].first, s2 = query[i].second;
        // swap(cards[s1], cards[s2]);
        swap(cards[a], cards[b]);
        
        // updateTree(s1);
        // updateTree(s2);

        updateTree(a);
        updateTree(b);

        bool temp = queryTree();
        // ans.PB(temp);
        if(temp){
            cout<<"TAK\n";
        }else{
            cout<<"NIE\n";
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<bool> ansS = solve();
    // for(int i = 0; i<m; i++){
    //     if(ansS[i]){
    //         cout<<"TAK\n";
    //     }else{
    //         cout<<"NIE\n";
    //     }
    // }

    return 0;
}