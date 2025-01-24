#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <set>

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

vector<int> brute(){
    vector<int> ans;

    vector<int> seq;
    int type = 1;
    for(int i = 0; i<d.size(); i++){
        for(int j = 0; j<d[i]; j++){
            seq.PB(type);
        }
        type = (type+1)%2;
    }

    for(int i = 0; i<query.size(); i++){
        int l = get<0>(query[i]), r = get<1>(query[i]), k = get<2>(query[i]);

        //check if l and r is within one d
        bool con = true;
        int s = seq[l-1];
        for(int j = l-1; j<r; j++){
            if(s != seq[j]){
                con = false;
                break;
            }
        }

        if(con && seq[l-1] == 1){
            ans.PB(r-l+1);
            continue;
        }

        //get segments
        int curLen = 0;
        vector<int> seg;
        int begSeg = -1, endSeg = -1;
        for(int j = l-1; j <r; j++){
            if(seq[j] == 0){
                if(begSeg == -1 && seq[l-1] == 1){
                    begSeg = curLen;
                }else{
                    seg.PB(curLen);
                }
                curLen = 0;
            }else{
                curLen++;
                if(j == r-1){
                    endSeg = curLen;
                }
            }
        }

        sort(seg.begin(), seg.end());

        int temp = 0;
        int count = 0;
        while(count < k){
            if(seg.size() > 0 && k-count >= 2){
                if(begSeg >= seg.back() && begSeg >= endSeg){
                    temp += begSeg;
                    begSeg = -1;
                    count += 1;
                }else if(endSeg >= seg.back() && endSeg >= begSeg){
                    temp += endSeg;
                    endSeg = -1;
                    count += 1;
                }else{
                    temp += seg.back();
                    seg.pop_back();
                    count += 2;
                }
            }else{
                if(begSeg >= endSeg && begSeg != -1){
                    count++;
                    temp += begSeg;
                    begSeg = -1;
                }else if(endSeg >= begSeg && endSeg != -1){
                    count++;
                    temp += endSeg;
                    endSeg = -1;
                }
            }

            if(count == k-1){
                if(begSeg >= endSeg && begSeg != -1){
                    count++;
                    temp += begSeg;
                    begSeg = -1;
                }else if(endSeg >= begSeg && endSeg != -1){
                    count++;
                    temp += endSeg;
                    endSeg = -1;
                }
                break;
            }

            if(seg.size() == 0 && begSeg == -1 && endSeg == -1){
                break;
            }
        }

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
        vector<int> ansB = brute();
        // for(int j = 0; j<ansB.size(); j++) cout<<ansB[j]<<" ";
    }

    return 0;
}