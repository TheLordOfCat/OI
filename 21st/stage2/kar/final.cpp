#include<iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n;
vector<int> x;
vector<int> y;

int m;
vector<PII> changes;

void getData(){
    cin>>n;
    for(int i =0; i<n; i++){
        int a,b;
        cin>>a>>b;
        x.PB(a);
        y.PB(b);
    }
    cin>>m;
    for(int i =0 ; i<m; i++){
        int a,b;
        cin>>a>>b;
        changes.PB(MP(a,b));
    }
}

struct node{
    vector<vector<int>> I;
    vector<vector<bool>> B;
    node(int xL1, int yL1, int xR1, int yR1, bool xx1, bool xy1, bool yx1, bool yy1){
        I = {{xL1, xR1}, {yL1, yR1}};
        B = {{xx1, xy1}, {yx1, yy1}};
    }
    node(){
        I = {{-1, -1}, {-1, -1}};
        B = {{false, false}, {false, false}};
    }
};

vector<node> tree;
int depth = 1;
int R = 1;

int leaf(int v){
    return R+v;
}

int parent(int v){
    return v/2;
}

int left(int v){
    return 2*v;
}

int right(int v){
    return 2*v+1;
}

void merge(int v){
    node l = tree[left(v)];
    node r = tree[right(v)];
    tree[v].B = {{false, false},{false, false}};
    tree[v].I = {{l.I[0][0], r.I[0][1]}, {l.I[1][0], r.I[1][1]}};
    
    if(left(v)> R || right(v) > R){
        for(int i = 0; i<2; i++){
            for(int j = 0; j<2; j++){
                if(l.I[i][0] <= r.I[j][0]){
                    tree[v].B[i][j] = true;
                    break;
                }
            }
        }
    }else{
        for(int i = 0; i<2; i++){
            for(int j = 0; j<2; j++){

                for(int k = 0; k<2; k++){
                    for(int o = 0; o<2; o++){
                        if(l.B[i][k] && r.B[o][j] && l.I[k][1] <= r.I[o][0]){
                            tree[v].B[i][j] = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void update(int v, int cX, int cY){
    int V = leaf(v+1);
    tree[V].I = {{cX,cX}, {cY,cY}};
    V = parent(V);
    while(V >= 1){
        merge(V);
        V = parent(V);
    }
}

vector<bool> solve(){
    tree.clear();
    tree.assign(4*n+1, node());

    //prepare tree
    while(n > (1<<depth)){
        R += 1<<depth;
        depth++;
    }
    for(int i = 0; i<n; i++){
        int V = leaf(i+1);
        tree[V].I = {{x[i], x[i]}, {y[i], y[i]}};
        tree[V].B = {{true, true},{true, true}};
    }
    for(int i = R; i>=1; i--){
        merge(i);
    }

    //proces chagnes
    vector<bool> ans;
    for(int i = 0; i<m; i++){
        int tempX = x[changes[i].first-1], tempY = y[changes[i].first-1];
        update(changes[i].first-1, x[changes[i].second-1], y[changes[i].second-1]);
        update(changes[i].second-1, tempX, tempY);
        if(tree[1].B[0][0] || tree[1].B[0][1] || tree[1].B[1][0] || tree[1].B[1][1]){
            ans.PB(true);
        }else{
            ans.PB(false);
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
    for(int i = 0; i<m; i++){
        if(ansS[i] == 0 ){
            cout<<"NIE\n";
        }else{
            cout<<"TAK\n";
        }
    }
    cout<<"\n";


    return 0;
}