#include <iostream>
#include <vector>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

const int K = 31;

int n;
vector<char> s;
int q;
vector<PII> seg;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        char temp;
        cin>>temp;
        s.PB(temp);
    }
    cin>>q;
    for(int i =0; i<q; i++){
        int a, b;
        cin>>a>>b;
        seg.PB(MP(a,b));
    }
}

vector<int> sieve(){
    vector<int> div(n+1, 1);
    for(int i = 2; i<=n; i++){
        if(div[i] == 1){
            for(int j = i; j<=n; j += i){
                div[j] = i;
            }
        }
    }
    return div;
}

vector<int> hashTab;
vector<int> pot;

bool hashCompare(int a, int b, int c, int d){
    int left = (hashTab[b] - hashTab[a-1]) * pot[n-b];
    int right = (hashTab[d] - hashTab[c-1]) * pot[n-d];
    return left == right;
}

bool isCyclyc(int a, int b, int k){
    return hashCompare(a, b-k, a+k, b);
}

int minCycle(int left, int right, vector<int>& div){
    int len = right - left +1;
    int L = 1;
    while(len != L){
        int k = div[len/L];
        if(isCyclyc(left, right, len/k)){
            right = left + len/k - 1;
            len = right - left +1;
        }else{
            int a = 0;
            int temp = k;
            while(len%temp == 0){
                temp *= k;
                a++;
            }
            temp/=k;
            L *= temp;
        }
    }
    return L;
}

vector<int> solve(){
    vector<int> div = sieve();
    vector<int> ans;

    //preparing hash
    pot.assign(n+1, 1);
    for(int i = 1; i<=n; i++){
        pot[i] = pot[i-1]*K;
    }

    hashTab.assign(n+1, 0);
    for(int i = 1; i<=n; i++){
        hashTab[i] = hashTab[i-1] + (s[i-1]-'a' + 1)*pot[i];
    }

    //processing request
    for(int i = 0; i<q; i++){
        int left = seg[i].first;
        int right = seg[i].second;

        int cycle = minCycle(left, right, div);    
        ans.PB(cycle);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<int> ansS = solve();
    for(int i =0; i<ansS.size(); i++){
        cout<<ansS[i]<<"\n";
    }

    return 0;
}