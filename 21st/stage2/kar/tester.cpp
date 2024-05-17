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

void getRandom(){
    srand(time(0));
    cards.clear();
    change.clear();
    cards.PB(MP(-1,-1));
    change.PB(MP(-1,-1));

    n =rand()%n+1;
    for(int i = 0; i<n; i++){
        int a = rand()%(3*n)+1;
        int b = rand()%(3*n)+1;
        cards.PB(MP(a,b));
    }
    m = rand()%5+1;
    for(int i = 0; i<m; i++){
        int a = rand()%n+1;
        int b = rand()%n+1;
        if(a == b){
            if(b == n){
                b--;
            }else{
                a++;
            }
        }
    }
}

void printData(){
    cout<<n<<"\n";
    for(int  i =0; i<cards.size(); i++){
        cout<<cards[i].first<<" "<<cards[i].second<<"\n";
    }
    cout<<m<<"\n";
    for(int i = 0 ;i<change.size(); i++){
        cout<<change[i].first<<" "<<change[i].second<<"\n";
    }
}

vector<int> brute(){
    vector<int> ans;

    for(int i = 1; i<=m; i++){
        //change
        PII temp = cards[change[i].first];
        cards[change[i].first] = cards[change[i].second];
        cards[change[i].second] = temp;

        //verifying
        int cur = min(cards[1].first, cards[1].second);
        bool ok = true;
        for(int j = 2; j<=n; j++){
            if(cur <= min(cards[j].first, cards[j].second)){
                cur = min(cards[j].first, cards[j].second);
            }else if(cur <= max(cards[j].first, cards[j].second)){
                cur = max(cards[j].first, cards[j].second);
            }else{
                ok = false;
                break;
            }
        }
        ans.PB(ok);
    }

    return ans;
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
    if(totalDepth != depth) r += 1<<(totalDepth - depth) -1;
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
                        int leftOne;
                        int rightOne;
                        if(depth == totalDepth-1){
                            leftOne = c[left(v)-R][i];
                            rightOne = c[right(v)-R][j];
                        }else{
                            leftOne = c[rightLeaf(left(v), depth+1)-R][o];
                            rightOne = c[leftLeaf(right(v), depth+1)-R][w];
                        }
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
    int V = parent(leaf(v));
    int depth = totalDepth-1;
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
    for(int i = 1; i<=m; i++){
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