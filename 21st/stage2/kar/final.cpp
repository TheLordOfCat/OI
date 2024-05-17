#include<iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n;
vector<PII> cards;
int m;
vector<PII> change;

void getData(){
    cin>>n;
    cards.PB(MP(-1,-1));
    for(int i = 0; i<n; i++){
        int a, b;
        cin>>a>>b;
        cards.PB(MP(a,b));
    }    
    cin>>m;
    change.PB(MP(-1,-1));
    for(int i =0; i<m; i++){
        int a, b;
        cin>>a>>b;
        change.PB(MP(a,b));
    }
}

vector<vector<vector<int>>> tree;
int R;
int totalDepth;

int parent(int v){
    return v/2;
}

int left(int v){
    return 2*v;
}

int right(int v){
    return 2*v+1;
}

int leaf(int v){
    return v+R;
}

int leftLeaf(int v, int depth){
    int l = v * 1<<(totalDepth - depth);
    return l;
}

int rightLeaf(int v, int depth){
    int r = leftLeaf(v, depth);
    if(totalDepth != depth) r += 1<<(totalDepth - depth);
    return r;
}

void merge(int v, int depth){
    vector<vector<int>> l = tree[left(v)];
    vector<vector<int>> r = tree[right(v)];

    vector<vector<int>> c;
    for(int i = 0; i<=n; i++){
        vector<int> temp;
        temp.PB(cards[i].first);
        temp.PB(cards[i].second);
        c.PB(temp);
    }

    vector<vector<int>> mid(2, vector<int>(2,0));
    for(int i = 0; i<=1; i++){
        for(int j = 0; j<=1; j++){

            for(int o = 0; o<=1; o++){
                for(int w = 0; w<=1; w++){

                    if(l[i][o] && r[w][j]){
                        int leftOne = c[rightLeaf(left(v), depth+1)-R][o];
                        int rightOne = c[leftLeaf(right(v), depth+1)-R][w];
                        if(leftOne <= rightOne){
                            mid[i][j] = 1;
                        }
                    }
                }
            }
        }
    }

    tree[v] = mid;
}

void update(int v){
    int V = leaf(v);
    int depth = totalDepth;
    while(V >= 1){
        merge(V, depth);
        V = parent(V);
        depth--;
    }
}

vector<int> solve(){
    tree.clear();
    R = 1;
    totalDepth = 1;
    // getting the size
    while(1<<totalDepth < n){
        R += 1<<totalDepth;
        totalDepth++;
    }
    totalDepth++;

    tree.assign(4*n+1, vector<vector<int>>(2,vector<int>(2,1)));
    int tempDepth = totalDepth-1;
    int count = 1<<(tempDepth-1);
    for(int i = R; i>=1; i--){
        if(count == 0){
            tempDepth--;
            count = 1<<(tempDepth-1);
        }
        count--;
        merge(i, tempDepth);
    }   

    // procesing the changes
    vector<int> ans;
    for(int i = 0; i<m; i++){
        //swap
        PII temp = cards[change[i].first];
        cards[change[i].first] = cards[change[i].second];
        cards[change[i].second] = temp;

        //update the tree
        update(change[i].first);
        update(change[i].second);

        if(tree[1][0][0] || tree[1][0][1] || tree[1][1][0]|| tree[1][1][1]){
            ans.PB(1);
        }else{
            ans.PB(0);
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();
    vector<int> ansS = solve();

    for(int i = 0; i<m; i++){
        cout<<ansS[i]<<" ";
    }
    cout<<"\n";


    return 0;
}