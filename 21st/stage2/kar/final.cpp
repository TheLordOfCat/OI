#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;

int n;
vector<PII> cards;
int m;
// vector<PII> change;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        int a, b;
        cin>>a>>b;
        cards.PB(MP(a,b));
    }    
    cin>>m;
}

vector<vector<vector<int>>> tree;
vector<pair<vector<int>,vector<int>>> range;
int R = 1;
int depth = 1;
int totalSize;

inline int left(int v){
    return 2*v;
}

inline int right(int v){
    return 2*v+1;
}

inline int parent(int v){
    return v/2;
}

inline int leaf(int v){
    return v+R+1;
}

void update(int ind){
    if(ind <= R){
        range[ind].first = range[left(ind)].first;
        range[ind].second = range[right(ind)].second;
    }

    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){

            if(ind > R){
                
                if(range[ind].second[i] <= range[ind].first[j]){
                    tree[ind][i][j] = 1;
                }else{
                    tree[ind][i][j] = 0;
                }

            }else{

                int l = left(ind);
                int r = right(ind);
                int ok = 0;
                
                for(int o = 0; o<2; o++){
                    for(int t = 0; t<2; t++){
                        
                        if(tree[l][i][o] == 1 && tree[r][t][j] == 1){
                            if(range[l].second[o] <= range[r].first[t]){
                                ok = 1;
                            }
                        }

                    }
                }

                tree[ind][i][j] = ok;

            }
        }
    }
}

void edit(int v){
    int V = leaf(v);
    while(V >= 1){
        update(V);
        V = parent(V);
    }
}

void replace(int a, int b){
    swap(range[leaf(a-1)],range[leaf(b-1)]);
    
    edit(a-1);
    edit(b-1);
}

vector<int> solve(){
    tree.clear();
    range.clear();

    //initalizing the tree
    while(1<<depth < n){
        R += 1<<depth;
        depth++;
    }

    totalSize = R + (1<<depth);

    for(int i =0; i<=totalSize; i++) tree.PB(vector<vector<int>>(2, vector<int>(2,0)));
    for(int i =0; i<=totalSize; i++){
        vector<int> t = {INF,INF};
        range.PB(MP(t,t));
    }
    
    for(int i = 0; i<n; i++){
        vector<int> t1;
        t1.PB(cards[i].first); t1.PB(cards[i].second);
        range[leaf(i)] = MP(t1,t1);
    }

    for(int i = totalSize; i>=1; i--){
        update(i);
    }

    //process requests
    vector<int> ans;
    for(int i =0; i<m; i++){
        int a, b;
        cin>>a>>b;
        // change.PB(MP(a,b));
        // for(int i = 0; i<m; i++){
            // replace(change[i].first, change[i].second);
            replace(a, b);
            int num = 0;
            for(int i = 0; i<2; i++){
                for(int j = 0; j<2; j++){
                    num = max(num, tree[1][i][j]);
                }
            }
            if(num == 1){
                cout<<"TAK\n";
            }else{
                cout<<"NIE\n";
            }
            // ans.PB(num);
        // }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<int> ansS = solve();
    // for(int i = 0; i<m; i++){
    //     if(ansS[i] == 1){
    //         cout<<"TAK\n";
    //     }else{
    //         cout<<"NIE\n";
    //     }
    // }

    return 0;
}