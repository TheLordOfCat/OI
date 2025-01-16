#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

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

vector<int> baseTree;
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
    return v+R+1;
}

void buildTree(int interSize){
    int depth = 0;
    R = 0;
    while((1<<depth) < interSize){
        R += (1<<depth);
        depth++;
    }

    baseTree.assign(R+(1<<depth)+1, 0);
}

void updateVer(int v){
    if(v <= R){
        baseTree[v] = baseTree[left(v)] + baseTree[right(v)];
    }
}

vector<vector<int>> verTree;

void queryTree(int val, int treeInd){

}

vector<int> solve(){
    //create base tree
    buildTree();

    //iterate throught d
    int type = 1;
    int curInd = 0;
    vector<int> dIndexed(n+1, 0);
    vector<int> oneSeg;
    for(int i = 0; i<d.size(); i++){
        if(type == 1){
            oneSeg.PB(d[i]);
        }
        dIndexed[i] = curInd;
        curInd += d[i];
        type = (type+1)%2;
    }



    //process query
    vector<int> ans;
    for(int i = 0; i<q; i++){
        int l = get<0>(query[i]), r = get<1>(query[i]), k = get<2>(query[i]);

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
        for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<" ";
        cout<<"\n";
    }

    return 0;
}