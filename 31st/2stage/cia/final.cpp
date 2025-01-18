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
int R, bottomSize;

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

void buildTree(int interSize){
    int depth = 0;
    R = 0;
    while((1<<depth) < interSize){
        R += (1<<depth);
        depth++;
    }
    bottomSize = (1<<depth);

    baseTree.assign(R+bottomSize+1, MP(0,0));
}

void updateVer(int v){
    if(v <= R){
        baseTree[v].first = baseTree[left(v)].first + baseTree[right(v)].first;
        baseTree[v].second = baseTree[left(v)].second + baseTree[right(v)].second;
    }
}

void updateSingle(int v, vector<int> indToNum){
    int V = leaf(v);
    baseTree[V].first++; baseTree[V].second += indToNum[v];
    while(V>=1){
        updateVer(V);
        V = parent(V);
    }
}

vector<vector<PII>> verTree;

int findIndex(int val, vector<int>& dIndex){
    int l = 0, r = dIndex.size()-1;

    int ans = 0;
    while(l <=r ){
        int mid = (l+r)/2;
        if(dIndex[mid] >= val){
            ans = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    return ans;
}

PII queryTree(int l, int r, int indT){
    PII ans = MP(0,0);

    int vL = leaf(l);
    int vR = leaf(r);

    ans.first += verTree[indT][vL].first;
    ans.second += verTree[indT][vL].second;
    if(vL != vR){
        ans.first += verTree[indT][vR].first;
        ans.second += verTree[indT][vR].second;
    }

    while(parent(vL) != parent(vR)){
        if(left(parent(vL)) == vL){
            ans.first += verTree[indT][right(parent(vL))].first;
            ans.second += verTree[indT][right(parent(vL))].second;
        }
        if(right(parent(vR)) == vR){
            ans.first += verTree[indT][left(parent(vR))].first;
            ans.second += verTree[indT][left(parent(vR))].second;
        }
        vL = parent(vL);
        vR = parent(vR);
    }
    return ans;
}

int findD(int t1, int t2, int val){
    int l = 0, r = bottomSize-1;

    int bestInd = 0, ans = 0, left = 0;
    while(l <= r){
        int mid = (l+r)/2;
        PII val1 = queryTree(mid, bottomSize-1, t1), val2 = queryTree(mid, bottomSize-1, t2);
        if(val2.first - val1.first <= val){
            bestInd = mid;
            ans = max(val2.second - val1.second,ans);
            left = val - (val2.first - val1.first);

            l = mid +1;
        }else{
            r = mid-1;
        }
    }

    if(bestInd-1 > t1){
        while(left > 0){
            ans += d[bestInd-1];
            left--;
        }
    }

    return ans;
}

int processQuery(int l, int r, int k, vector<int>& dIndex){
    //get indexes
    int indL = findIndex(l, dIndex), indR = findIndex(r, dIndex);
    if(dIndex[indR] != r) indR--;

    if((indL == indR && ((dIndex[indL] == l) || (dIndex[indL-1] <= l && r < dIndex[indR]))) || (indL+1 == indR && dIndex[indL] == l && r < dIndex[indR])){
        return r-l+1;
    }

    //get sides
    int leftSide = 0, rightSide = 0;
    
    if((dIndex[indL] != l && indL%2 == 0) || (dIndex[indL] == l && indL%2 == 1)){
        int cur = l;
        while(cur < dIndex[indL+1]){
            leftSide++;
            cur++;
        }
        indL++;
    }
    if(dIndex[indR] + d[indR-1] != r && indR%2 == 1){
        int cur = r;
        while(cur >= dIndex[indR]){
            rightSide++;
            cur--;
        }
        indR--;
    }

    int temp1 = findD(indL-1, indR, k/2);
    int temp2 = findD(indL-1, indR, (k-1)/2);
    if(k > 0) temp2 += max(leftSide, rightSide);
    int temp3 = findD(indL-1, indR, (k-2)/2);
    if(k > 1) temp3 += leftSide + rightSide;

    return max(temp1,max(temp2,temp3));
}

vector<int> solve(){
    //get unice d[i]
    set<int> S;
    int type = 1;

    vector<int> dIndexed;
    dIndexed.PB(0);
    int cur = 1;
    int maxVal = 0;
    for(int i = 0; i<d.size(); i++){
        if(type == 1){
            S.insert(d[i]);
        }
        dIndexed.PB(cur);
        cur += d[i];
        type = (type+1)%2;
        maxVal = max(maxVal, d[i]);
    }
    dIndexed.PB(cur);
    
    vector<int> indToNum, numToInd(maxVal+1, -1);
    for(auto itr = S.begin(); itr != S.end(); itr++){
        indToNum.PB(*itr);
        numToInd[*itr] = indToNum.size()-1;
    }

    //create base tree
    buildTree(S.size());

    //create prexfix sum tree
    type = 1;
    verTree.PB(baseTree);
    for(int i =0 ; i<n; i++){
        if(type == 1){
            updateSingle(numToInd[d[i]], indToNum);
        }
        verTree.PB(baseTree);
        type = (type+1)%2;
    }
    verTree.PB(baseTree);

    //process query
    vector<int> ans;
    for(int i =0 ;i<q; i++){
        int l = get<0>(query[i]), r = get<1>(query[i]), k = get<2>(query[i]);

        int temp = processQuery(l, r, k, dIndexed);

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