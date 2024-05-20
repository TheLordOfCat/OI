#include<iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>

const int INF = 2'000'000'000;

int n, k;
vector<int> c;
int m,l;
vector<int> x;
vector<int> y;

void getData(){
    cin>>n>>k;
    for(int i =0 ;i<n; i++){
        int temp;
        cin>>temp;
        c.PB(temp);
    }
    cin>>m>>l;
    for(int i = 0; i<m; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0 ; i<l; i++){
        int temp;
        cin>>temp;
        y.PB(temp);
    }
}

bool customPiarCompare(PII a, PII b){
    return a.first < b.first;
}

bool customTupleCompare(tuple<int,int,int> a, tuple<int,int,int> b){
    return get<1>(a) < get<1>(b);
}

vector<int> solve(){
    vector<tuple<int,int,int>> seg;
    //left
    vector<int> next(n+1, 0);
    vector<PII> begin(k+1, MP(INF,INF));

    for(int i = n-1; i>= 0; i--){
        next[i] = begin[c[i]].first;
        begin[c[i]].first = i;
    }

    vector<int> pos(k+1, 0);
    for(int i = 1; i<=k; i++){
        pos[i] = begin[i].first;
        begin[i].second = i;
    }

    sort(begin.begin(), begin.end(), customPiarCompare);

    for(int i = 0; i<k; i++){
        int limit = begin[i].first;
        if(limit == INF) limit--;
        for(int j = 0; j<x.size(); j++){
            int cur = x[j];
            while(pos[cur] <= limit){
                pos[cur] = next[pos[cur]];
            }
            limit = pos[cur];
            if(pos[cur] == INF){
                break;
            }
            if(limit == INF) limit--;
        }
        seg.PB(make_tuple(limit, 0, begin[i].second));
    }

    //right
    next.clear();
    begin.clear();
    next.assign(n+1, -INF);
    begin.assign(k+1, MP(-INF,-INF));

    for(int i = 0; i< n; i++){
        next[i] = begin[c[i]].first;
        begin[c[i]].first = i;
    }

    pos.clear();
    pos.assign(k+1, 0);
    for(int i = 1; i<=k; i++){
        pos[i] = begin[i].first;
        begin[i].second = i;
    }
    sort(begin.begin()+1, begin.end());

    for(int i = k-1; i>=0; i--){
        int limit = begin[i].first;
        if(limit == -INF) limit++;
        for(int j = 0; j<y.size(); j++){
            int cur = y[j];
            while(pos[cur] >= limit){
                pos[cur] = next[pos[cur]];
            }
            limit = pos[cur];
            if(pos[cur] == -1){
                break;
            }
            if(limit == -INF) limit++;
        }
        seg.PB(make_tuple(limit,1, begin[i].second));
    }

    //combine
    sort(seg.begin(),seg.end());

    vector<int> ans;
    vector<bool> started(k+1, false);
    int ind = 0;
    int active = 0;
    for(int i = 0; i<n; i++){
        while(get<0>(seg[ind]) <= i){
            if(get<1>(seg[ind]) == 1){
                if(!started[get<2>(seg[ind])]){
                    active--;
                }
                started[get<2>(seg[ind])] = true;
            }else{
                if(!started[get<2>(seg[ind])]){
                    active++;
                }
                started[get<2>(seg[ind])] = true;
            }
            ind++;
        }
        if(active > 0 && c[i] == x.back()){
            ans.PB(i+1);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<int> ansS = solve();
    cout<<ansS.size()<<"\n";
    for(int i = 0; i<ansS.size(); i++){
        cout<<ansS[i]<<" ";
    }

    return 0;
}