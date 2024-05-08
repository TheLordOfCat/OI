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

void getRandom(){
    srand(time(0));
    x.clear();
    y.clear();

    n = rand()%10+1;
    for(int i  = 0; i<n; i++){
        x.PB(rand()%40+1);
        y.PB(rand()%40+1);
    }
    m = rand()%10+1;
    for(int i = 0; i<m; i++){
        int a = rand()%n+1;
        int b = rand()%n+1;
        changes.PB(MP(a,b));
    }
}

void printData(){
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<x[i]<<" "<<y[i]<<"\n";
    }
    cout<<m<<"\n";
    for(int i =0 ;i<m; i++){
        cout<<changes[i].first<<" "<<changes[i].second<<"\n";
    }
}

vector<bool> brute(){
    vector<bool> ans;
    for(int i = 0; i<m; i++){
        //change
        int tempX = x[changes[i].first-1], tempY = y[changes[i].first-1];
        x[changes[i].first-1] = x[changes[i].second-1];
        y[changes[i].first-1] = y[changes[i].second-1];
        x[changes[i].second-1] = tempX;
        y[changes[i].second-1] = tempY;

        //verify
        bool ok = true;
        int last = min(x[0],y[0]);
        for(int  j = 1; j<n; j++){
            int smaller = min(x[j],y[j]);
            int bigger = max(x[j],y[j]);
            if(last <= smaller){
                last = smaller;
            }else if(last <= bigger){
                last = bigger;
            }else{
                ok = false;
                break;
            }
        }
        if(ok){
            ans.PB(true);
        }else{
            ans.PB(false);
        }
    }
    return ans;
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
    
    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){
            for(int o = 0; o<2; o++){
                if(l.B[i][o] && r.B[o][j] && l.I[i][o] <= r.I[o][j]){
                    tree[v].B[i][j] = true;
                }
            }
        }
    }
}

void update(int v, int cX, int xY){
    int V = leaf(v+1);
    V = parent(V);
    while(V >= 1){
        merge(v);
        V = parent(V);
    }
}

vector<bool> solve(){
    tree.clear();
    tree.assign(n, node());

    //prepare tree
    while(n > (1<<depth)){
        R += 1<<depth;
        depth++;
    }
    for(int i = 0; i<m; i++){
        int V = leaf(i+1);
        tree[V].I = {{x[i], y[i]}, {x[i], y[i]}};
        tree[V].B = {{false, false},{false, false}};
    }
    for(int i = R; i>=1; R++){
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

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<bool> ansB = brute();
        vector<bool> ansS = solve();
        for(int i = 0; i <m; i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int i = 0; i<m; i++){
                    cout<<ansB[i]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int i = 0; i<m; i++){
                    cout<<ansS[i]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}