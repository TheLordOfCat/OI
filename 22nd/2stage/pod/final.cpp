#include <iostream>
#include <vector>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

const int INF = 2'000'000'000;
const int MAXN = 1'000'000;
const int MAXK = 1'000'000;

int n, k;
vector<int> r;

void getData(){
    r.clear();

    r.PB(-1);
    cin>>n>>k;
    for(int i = 0; i<n; i++){
        int a;
        cin>>a;
        r.PB(a);
    }
}

vector<ll> tree;
vector<int> banned;
int R;

int left(int v){
    return v*2;
}

int right(int v){
    return v*2+1;
}

int parent(int v){
    return v/2;
}

int leaf(int v){
    return v+R;
}

PII getRange(int v){ //not optiaml
    int vL = v;
    int vR = v;

    while(vL < R){
        vL = left(vL);
    }

    while(vR < R){
        vR = right(vR);
    }

    return MP(vL,vR);
}

void buildTree(){
    tree.clear();
    banned.clear();

    R = 0;
    int depth = 0;
    while((1<<depth) < n){
        R += (1<<depth);
        depth++;
    }
    
    int totalSize = R + (1<<depth);

    tree.assign(totalSize+1, 0);
    banned.assign(totalSize+1, 0);    
}

void updateNode(int v, int val){
    int V = leaf(v);
    tree[V] += val;
    if(tree[V] < 0){
        banned[V] = 1;
    }

    V = parent(V);
    while(V >= 1){
        banned[V] = banned[left(V)] + banned[right(V)];
        V = parent(V);
    }
}

void updateRange(int l, int r, int val){
    if(r<l){
        return;
    }
    int vL = leaf(l);
    int vR = leaf(r);

    tree[vL] += val;
    if(vL != vR){
        tree[vR] += val;
    }

    while(parent(vL) != parent(vR)){
        if(left(parent(vL)) == vL){
            tree[right(parent(vL))] += val;
            if(tree[right(parent(vL))]< 0){
                PII r = getRange(right(parent(vL)));
                banned[right(parent(vL))] = r.second-r.first+1;
            }
        }
        if(right(parent(vR)) == vR){
            tree[left(parent(vR))] += val;
            if(tree[left(parent(vR))]< 0){
                PII r = getRange(left(parent(vR)));
                banned[left(parent(vR))] = r.second-r.first+1;
            }
        }
        vL = parent(vL);
        vR = parent(vR);
    }

    vL = leaf(l); vR = leaf(r);
    if(tree[vL] < 0){
        banned[vL] = 1;
    }
    if(tree[vR] < 0 && vL != vR){
        banned[vR] = 1;
    }
    vL = parent(vL);
    vR = parent(vR);
    while(vL >= 1){
        banned[vL] = banned[left(vL)] + banned[right(vL)];
        vL = parent(vL);
    }
    while(vR >= 1){
        banned[vR] = banned[left(vR)] + banned[right(vR)];
        vR = parent(vR);
    }
}

ll queryRanges(){
    return n - banned[1];
}

int queryLongest(int start, int v){
    //find left and right
    int V = leaf(v);
    int leftNode = -1, rightNode = -1;
    while( V > 1){
        if(left(parent(V)) == V && rightNode == -1){
            PII r = getRange(right(parent(V)));
            if(banned[right(parent(V))] < r.second-r.first+1){
                rightNode = right(parent(V));
            }
        }
        if(right(parent(V)) == V && leftNode == -1){
            PII r = getRange(left(parent(V)));
            if(banned[left(parent(V))] < r.second-r.first+1){
                leftNode = left(parent(V));
            }
        }
        V = parent(V);
    }

    int ans = 0;
    //process left
    if(leftNode != -1){
        while(leftNode < R){
            PII r = getRange(right(leftNode));
            if(banned[right(leftNode)] <= r.second-r.first-1){
                leftNode = right(leftNode);
            }else{
                leftNode = left(leftNode);
            }
        }

        ans= max(start-leftNode+1, ans);
    }

    //process right
    if(rightNode != -1){
        while(rightNode < R){
            PII r = getRange(left(rightNode));
            if(banned[left(rightNode)] <= r.second-r.first-1){
                rightNode = left(rightNode);
            }else{
                rightNode = right(rightNode);
            }
        }

        ans= max(rightNode-start+1, ans);
    }

    return ans;
}

pair<ll,int> solve(){
    //get range and next
    vector<PII> range(k+1, MP(-1,-1));
    vector<int> next(n+1, -1); 

    vector<int> last(k+1, -1);
    for(int i = r.size()-1; i>0; i--){
        int cur = r[i];
        if(range[cur].second == -1){
            range[cur].second = i;
        }

        next[i] = last[cur];
        last[cur] = i;
    }

    for(int i = 1; i<last.size(); i++){
        range[i].first = last[i];
    }

    //intnialize the tree
    buildTree();

    for(int i = 1; i<=k; i++){
        updateRange(range[i].first, range[i].second-1, -1);
    }

    //process
    pair<ll,int> ans;
    ans.first += queryRanges();
    ans.second += queryLongest(1, n/2);

    for(int i = 2; i<=n; i++){
        updateNode(i-1, -1);
        if(next[i-1] != -1){
            updateRange(i-1, next[i-1], 1);
        }
        ans.first += queryRanges();
        int temp = queryLongest(i, min(n, n/2 + i));
        ans.second = max(ans.second, temp);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    pair<ll, int> ansS = solve();
    cout<<ansS.first<<" "<<ansS.second<<"\n";

    return 0;
}