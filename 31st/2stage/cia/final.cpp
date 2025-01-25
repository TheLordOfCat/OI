#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <set>
#include <map>
#include <cassert>

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
    q = 0;
    for(int i = 0; i<n; i++){
        for(int j = i; j<n; j++){
            for(int o = 0; o<n; o++){
                int l = i+1, r = j+1;
                if(l > r) swap(l,r);
                int k = o;
                query.PB(MT(l,r,k));
                q++;
            }
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<q<<"\n";
    for(int i = 0; i<n; i++){
        cout<<d[i]<<" ";
    }
    cout<<"\n";
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

    assert((1<<depth) >= 0);

    baseTree.assign((1<<depth)+R+1, MP(0,0));
    bottomLevel = (1<<depth);
}

bool customExtDCompare(PII a, PII b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    return a.first < b.first;
}

vector<int> getDToTree(set<int>& S){
    vector<PII> extD;
    for(int i = 0; i<d.size(); i++){
        extD.PB(MP(d[i],i));
    }
    sort(extD.begin(), extD.end(), customExtDCompare);

    vector<int> ans(n, 0);
    int ind = 0;
    for(int i =0 ;i<n; i++){
        assert(extD[i].second < ans.size());
        ans[extD[i].second] = ind;
        if(i < n-1){
            assert(i < extD.size()-1);
            if(extD[i].first != extD[i+1].first){
                ind++;
            }
        }
    }
    return ans;
}

void updateSingle(int v, int val, int len){
    int V = leaf(v);
    assert(V < baseTree.size());
    while(V >= 1){
        baseTree[V].first += val;
        baseTree[V].second += len;
        V = parent(V);
    }
}

int realIndex(int ind, vector<int>& dInd){
    int l = 0, r = dInd.size()-1;
    int ans = -1;
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

    int l = leaf(val), r = leaf(bottomLevel-1);

    ans.first += vecTree[indT][l].first;
    ans.second += vecTree[indT][l].second;
    if(l != r) {
        ans.first += vecTree[indT][r].first;
        ans.second += vecTree[indT][r].second;
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

PII findTree(int indL, int indR, int val, vector<int>& treeToD){
    int l = 0, r = bottomLevel-1;
    PII ans = MP(0,0); 
    int ind = bottomLevel;
    while(l <= r){
        int mid = (l+r)/2;
        PII tempL = queryTree(indL, mid), tempR = queryTree(indR, mid);
        if(tempR.first - tempL.first <= val){
            ans = MP(tempR.first - tempL.first, tempR.second - tempL.second);
            ind = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }

    //enlarge
    int count = 0;
    assert(leaf(ind-1) < vecTree[indR].size());
    assert(leaf(ind-1) < vecTree[indL].size());
    while(ans.first < val && ind >= 1 && count < vecTree[indR][leaf(ind-1)].first-vecTree[indL][leaf(ind-1)].first){
        ans.second += treeToD[ind-1];
        ans.first++;
        count++;
    }

    return ans;
}

int processQuery(int l, int r, int k, vector<int>& dInd, vector<int>& treeToD){
    int indL = realIndex(l, dInd), indR = realIndex(r, dInd);

    int ans1 = 0, ans2 = 0, ans3 = 0;
    
    if(indL < indR){
        int begSeg = -1, endSeg = -1;
        if(indL%2 == 0){
            assert(indL >= 0);
            begSeg = dInd[indL]-l; 
        }
        if(indR%2 == 0){
            assert(indR -1 >= 0);
            endSeg = r - dInd[indR-1]+1;
        }

        if(k >= 1){
            ans2 = max(begSeg, endSeg);
        }
        if(k >= 2){
            ans3 = begSeg + endSeg;
        }

        int temp = findTree(indL-1, indR-2, k/2, treeToD).second;
        ans1 += temp;
        
        temp = findTree(indL-1, indR-2, (k-1)/2, treeToD).second;
        ans2 += temp;
        
        temp = findTree(indL-1, indR-2, (k-2)/2, treeToD).second;
        ans3 += temp;
    }else if(indR == indL && indR%2 == 0){
        ans1 = r-l+1;
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
    vector<int> dInd;
    dInd.PB(0);
    int curInd = 1;
    for(int i = 0; i<n; i++){
        dInd.PB(curInd);
        curInd += d[i];
        assert(curInd >= 0);
    }
    dInd.PB(curInd);

    //process trees
    type = 1;
    for(int i =0; i<n; i++){
        vecTree.PB(baseTree);
        if(type == 1){
            updateSingle(dToTree[i], 1, d[i]);
        }
        type = (type+1)%2;
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
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansS = solve();
        for(int j = 0; j<ansS.size(); j++){
            if(ansS[j] < 0){
                cout<<"ERORR\n";
                printData();
                cout<<j<<"\n";
                return 0;
            }
        }
        cout<<"CORRECT\n";
        cout<<ansS[8]<<"\n";
    }

    return 0;
}