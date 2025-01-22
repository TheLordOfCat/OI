#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <set>
#include <map>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define PLL pair<ll,ll>
#define MT make_tuple

int n;
vector<int> d;
int q;
vector<tuple<int,int,int>> query;

void getData(){
    d.clear(); query.clear();
    cin>>n>>q;
    for(int i =0; i<n; i++){
        int temp;
        cin>>temp;
        d.PB(temp);
    }
    for(int i =0 ; i<q; i++){
        int a, b, c;
        cin>>a>>b>>c;
        query.PB(MT(a,b,c));
    }
}

void getRandom(){
    d.clear(); query.clear();

    srand(time(0));

    n = rand()%10+1;
    int totalLen = 0;
    for(int i =0; i<n; i++){
        int temp = rand()%2+1;
        d.PB(temp);
        totalLen += temp;
    }
    q = rand()%10+1;
    for(int i = 0; i<q; i++){
        int l = rand()%totalLen+1, r = rand()%totalLen+1;
        if(l > r) swap(l,r);
        int k = rand()%3+1;
        query.PB(MT(l,r,k));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<d[i]<<" ";
    }
    cout<<"\n";
    cout<<q<<"\n";
    for(int i= 0; i<q; i++){
        int l = get<0>(query[i]), r = get<1>(query[i]), k = get<2>(query[i]);
        cout<<l<<" "<<r<<" "<<k<<"\n";
    }
}

vector<PII> baseTree;
int R;
int bottomLevel;

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
    return v+R+1;
}

void buildTree(int s){
    int depth = 0;
    R = 0;
    while((1<<depth) < s){
        R += (1<<depth);
        depth++;
    }

    baseTree.assign((1<<depth)+R+1, MP(0,0));
    bottomLevel = (1<<depth);
}

vector<int> getDToTree(set<int>& S){
    vector<int> ind(INF/2+1, -1);
    int count = 0;
    for(auto itr = S.begin(); itr != S.end(); itr++){
        if(ind[*itr] == -1){
            ind[*itr] = count;
            count++;
        }
    }
    vector<int> ans(n, 0);
    for(int i =0 ;i<n; i++){
        ans[i] = ind[i];
    }
    return ans;
}

void updateSingle(int v, int val, int len){
    int V = leaf(v);
    while(V >= 1){
        baseTree[V].first += val;
        baseTree[V].second += len;
        V = parent(V);
    }
}

int realIndex(int ind, vector<int>& dInd){
    int l = 0, r = n-1;
    int ans = 0;
    while(l<=r){
        int mid = (l+r)/2;
        if(dInd[mid] > ind){
            ans = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }

    return ans;
}

vector<vector<PII>> vecTree;

PII queryTree(int indT, int val){
    PII ans = MP(0,0);

    int l = leaf(val), r = leaf(bottomLevel);

    ans.first += vecTree[indT][l].first;
    ans.second += vecTree[indT][l].second;
    if(l != r) {
        ans.first += vecTree[indT][l].first;
        ans.second += vecTree[indT][l].second;
    }

    while(parent(l) != parent(r)){
        if(left(parent(l)) == l){
            ans.first += vecTree[indT][right(parent(l))].first;
            ans.second += vecTree[indT][right(parent(l))].second;
        }
        if(right(parent(r)) == r){
            ans.first += vecTree[indT][left(parent(r))].first;
            ans.second += vecTree[indT][left(parent(r))].second;
        }
        l = parent(l);
        r = parent(r);
    }

    return ans;
}

PII findTree(int indT, int val, vector<int>& treeToD){
    int l = 0, r = bottomLevel-1;
    PII ans = MP(0,0); 
    int ind = 0;
    while(l <= r){
        int mid = (l+r)/2;
        PII temp = queryTree(indT, mid);
        if(temp.first <= val){
            ans = temp;
            ind = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }

    //enlarge
    while(ans.first <= val && ind != 1){
        ans.second += d[treeToD[ind-1]];
        ans.first++;
    }

    return ans;
}

int processQuery(int l, int r, int k, vector<int>& dInd, vector<int>& treeToD){
    int indL = realIndex(l, dInd), indR = realIndex(r, dInd)-1;

    int begSeg = -1, endSeg = -1;
    if(indL%2 == 0){
        begSeg = indL-l; 
    }
    if(indR%2 == 1){
        endSeg = r - indR;
    }

    int ans1 = 0, ans2 = max(begSeg, endSeg), ans3 = begSeg + endSeg;
    if(indL < indR-1){
        int temp = findTree(indR-1, k/2, treeToD).second - findTree(indL, k/2, treeToD).second;
        ans1 += temp;
        
        temp = findTree(indR-1, (k-1)/2, treeToD).second - findTree(indL, (k-1)/2, treeToD).second;
        ans2 += temp;
        
        temp = findTree(indR-1, (k-2)/2, treeToD).second - findTree(indL, (k-2)/2, treeToD).second;
        ans3 += temp;
    }
    return max(ans1, max(ans2, ans3));
}   

vector<int> solve(){
    //get all lengths
    set<int> S;
    int type = 1;
    for(int i =0 ; i<n; i++){
        if(type == 1){
            S.insert(d[i]);
        }
        type = (type + 1)%2;
    }

    //build tree
    buildTree(S.size());

    //get d to tree
    vector<int> dToTree = getDToTree(S);

    //get tree to d
    vector<int> treeToD;
    for(auto itr = S.begin(); itr!= S.end(); itr++){
        treeToD.PB(*itr);
    }

    //get real d indexse
    vector<int> dInd(n, 0);
    int curInd = 1;
    for(int i = 0; i<n; i++){
        dInd[i] = curInd;
        curInd += d[i];
    }

    //process trees
    for(int i =0; i<n; i++){
        vecTree.PB(baseTree);
        updateSingle(dToTree[i], 1, d[i]);
    }
    vecTree.PB(baseTree);

    //process query
    vector<int> ans;
    for(int i = 0; i<q; i++){
        int l = get<0>(query[i]), r = get<1>(query[i]), k = get<2>(query[i]);

        int temp = processQuery(l,r,k, dInd, treeToD);
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
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansS = solve();
        for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<"\n";
    }

    return 0;
}