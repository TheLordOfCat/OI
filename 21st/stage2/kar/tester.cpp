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
vector<PII> cards;
int m;
vector<PII> query;

void getData(){
    cards.clear(); query.clear();

    cin>>n;
    cards.PB(MP(-1,-1));
    for(int i = 0; i<n; i++){
        int a, b;
        cin>>a>>b;
        cards.PB(MP(a,b));
    }    
    cin>>m;
    for(int i =0; i<m; i++){
        int a, b;
        cin>>a>>b;
        query.PB(MP(a,b));
    }
}

void getRandom(){
    cards.clear(); query.clear();

    srand(time(0));

    // n = rand()%10+1;
    n = 4;
    cards.PB(MP(INF,INF));
    for(int i = 0; i<n; i++){
        int a = rand()%10+1;
        int b = rand()%10+1;
        cards.PB(MP(a,b));
    }

    // m = rand()%10+1;
    m = 4;
    for(int i = 0; i<m; i++){
        int a = rand()%n + 1;
        int b = rand()%n + 1;
        query.PB(MP(a,b));
    }
}

void printData(){
    cout<<n<<"\n";
    for(int  i =0; i<cards.size(); i++){
        cout<<cards[i].first<<" "<<cards[i].second<<"\n";
    }
    cout<<m<<"\n";
    for(int i = 0; i<query.size(); i++){
        cout<<query[i].first<<" "<<query[i].second<<"\n";
    }
}

vector<bool> brute(){
    vector<bool> ans;
    vector<PII> cB = cards;

    for(int i = 0; i<m; i++){
        //swap
        int s1 = query[i].first, s2 = query[i].second;
        swap(cB[s1],cB[s2]);

        //verify
        bool ok = true;
        int head = -1;
        for(int j = 1 ;j <=n; j++){
            int a = cB[j].first, b = cB[j].second;
            if(a >= head && b >= head){
                head = min(a,b);
            }else if(a >= head){
                head = a;
            }else if(b >= head){
                head = b;
            }else{
                ok = false;
            }
        }
        ans.PB(ok);
    }

    return ans;
}

vector<vector<vector<bool>>> tree;
vector<PII> range;
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

vector<vector<bool>> combine(int vL, int vR, vector<vector<int>>& cB){
    vector<vector<bool>> matrix(2, vector<bool>(2, false));
    vector<vector<bool>> a = tree[vL], b = tree[vR];

    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){
            bool ok = false;

            for(int o = 0; o<2; o++){
                for(int k = 0; k<2; k++){

                    if(a[i][o] && b[k][j]){
                        if(cB[range[vL].second][o] <= cB[range[vR].first][k]){
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

void buildTree(vector<vector<int>>& cB){
    R = 0;
    int depth = 0;
    while((1<<depth) < n){
        R += (1<<depth); 
        depth++;
    }

    vector<vector<bool>> matrix(2, vector<bool>(2, true));
    tree.assign(R + (1<<depth), matrix);
    range.assign(R + (1<<depth), MP(-1,-1));

    for(int i = R + (1<<depth); i>= 1; i++){
        if(i > R){
            range[i] = MP(i- R,i - R); 
        }else{
            range[i].first = range[left(i)].first;
            range[i].second = range[right(i)].second;
            tree[i] = combine(left(i), right(i), cB);
        }
    }
}

void updateTree(int v, vector<vector<int>>& cB){
    int V = leaf(v);
    V = parent(V);

    while(V >= 1){
        vector<vector<bool>> matrix = combine(left(V), right(V), cB);
        tree[V] = matrix;
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
    vector<vector<int>> cB(cards.size(), vector<int>());
    for(int i =0; i<cards.size(); i++){
        cB[i].PB(cards[i].first);
        cB[i].PB(cards[i].second);
    }

    buildTree(cB);
    for(int i = 0; i<m; i++){
        int s1 = query[i].first, s2 = query[i].second;
        swap(cB[s1], cB[s2]);
        
        updateTree(s1, cB);
        updateTree(s2, cB);

        bool temp = queryTree();
        ans.PB(temp);
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