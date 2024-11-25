#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <bitset>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>

int n, k;
string start, finish;
vector<string> removed;

void getData(){
    start.clear(); finish.clear(); removed.clear();

    cin>>n>>k;
    cin>>start>>finish;
    for(int i = 0; i<k; i++){
        string temp;
        cin>>temp;
        removed.PB(temp);
    }
}

//hash method taken from original solution provided by OI

inline void hashSetInsert(long long* set, int* prev, int* hash, int &free, long long value, int size)
{
    set[free] = value;
    prev[free] = hash[value%size];
    hash[value%size] = free++;
}

inline bool hashSetLookup(long long* set, int* prev, int* hash, long long value, int size)
{
    for(int t = hash[value%size]; t>0; t=prev[t])
        if(set[t] == value) return true;
    return false;
}

inline void hashSetClear(int* hash, int &free, int size)
{
    free = 1;
    for(int i = 0; i<size; i++)
        hash[i] = 0;
}

const int HSIZE = 5000011;
const int EMPTY = 0;
const int MAXK = 500009;

long long forbidden[MAXK];
int fprev[MAXK];
int fhash[MAXK];
long long visited[HSIZE];
int vprev[HSIZE];
int vhash[HSIZE];
int vfree = 1, ffree = 1;
long long q[HSIZE];

bool solve(){
    //change to number
    vector<ll> vR;
    for(int i =0 ; i<removed.size(); i++){
        // ll temp = 0;
        // for(int j = removed[i].size()-1; j>=0; j--){
        //     if(removed[i][j] == '1'){
        //         temp += (1LL<<(removed[i].size()-j-1));
        //     }
        // }
        // vR.PB(temp);
        bitset<60> temp(removed[i]);
        hashSetInsert(forbidden,fprev,fhash,ffree,temp.to_ullong(),MAXK);
        // vR.PB(temp.to_ullong());
    }

    //get into set
    // unordered_set<ll> S(vR.begin(), vR.end());

    //bfs
    bitset<60> tempS(start), tempF(finish);
    ll vS = tempS.to_ullong(), vF = tempF.to_ullong();
    // for(int i = start.size()-1; i>=0; i--){
    //     if(start[i] == '1'){
    //         vS += (1LL<<(start.size()-i-1));
    //     }
    // }
    // for(int i = finish.size()-1; i>=0; i--){
    //     if(finish[i] == '1'){
    //         vF += (1LL<<(finish.size()-i-1));
    //     }
    // }

    vector<bool> bfsAns;
    vector<ll> vec = {vS, vF};
    for(int j = 0; j< vec.size(); j++){
        bool temp = false;
        // unordered_set<ll> U;
        queue<ll> Q;

        Q.push(vec[j]);
        hashSetInsert(visited,vprev,vhash,vfree, vec[j], HSIZE);        
        int used = 1;
        int limit = n*k + 1;

        while(!Q.empty() && used < limit){
            ll v = Q.front();
            Q.pop();

            if(v == vec[(j+1)%2]){
                temp = true;
            }

            for(int i = 0; i<n; i++){
                ll cur = v;
                cur ^= (1LL<<i);
                if(!hashSetLookup(forbidden,fprev,fhash,cur,MAXK) && !hashSetLookup(visited,vprev,vhash,cur,HSIZE)){
                    Q.push(cur);
                    hashSetInsert(visited,vprev,vhash,vfree,cur,HSIZE);
                    used++;
                }
            }
            if(used >= limit){
                temp = true;
            }
        }
        if(used >= limit){
            temp = true;
        }
        bfsAns.PB(temp);
        hashSetClear(vhash,vfree,HSIZE);
    }

    return bfsAns[0] && bfsAns[1]; 
}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    bool ansS = solve();
    if(ansS){
        cout<<"TAK\n";
    }else{
        cout<<"NIE\n";
    }

    return 0;
}

/*
//hash method taken from original solution provided by OI

inline void hashSetInsert(long long* set, int* prev, int* hash, int &free, long long value, int size)
{
    set[free] = value;
    prev[free] = hash[value%size];
    hash[value%size] = free++;
}

inline bool hashSetLookup(long long* set, int* prev, int* hash, long long value, int size)
{
    for(int t = hash[value%size]; t>0; t=prev[t])
        if(set[t] == value) return true;
    return false;
}

inline void hashSetClear(int* hash, int &free, int size)
{
    free = 1;
    for(int i = 0; i<size; i++)
        hash[i] = 0;
}

const int HSIZE = 5000011;
const int EMPTY = 0;
const int MAXK = 500009;

long long forbidden[MAXK];
int fprev[MAXK];
int fhash[MAXK];
long long visited[HSIZE];
int vprev[HSIZE];
int vhash[HSIZE];
int vfree = 1, ffree = 1;
long long q[HSIZE];

bool solve(){
    //change to number
    vector<ll> vR;
    for(int i =0 ; i<removed.size(); i++){
        // ll temp = 0;
        // for(int j = removed[i].size()-1; j>=0; j--){
        //     if(removed[i][j] == '1'){
        //         temp += (1LL<<(removed[i].size()-j-1));
        //     }
        // }
        // vR.PB(temp);
        bitset<60> temp(removed[i]);
        hashSetInsert(forbidden,fprev,fhash,ffree,temp.to_ullong(),MAXK);
        // vR.PB(temp.to_ullong());
    }

    //get into set
    // unordered_set<ll> S(vR.begin(), vR.end());

    //bfs
    ll vS = 0, vF = 0;
    for(int i = start.size()-1; i>=0; i--){
        if(start[i] == '1'){
            vS += (1LL<<(start.size()-i-1));
        }
    }
    for(int i = finish.size()-1; i>=0; i--){
        if(finish[i] == '1'){
            vF += (1LL<<(finish.size()-i-1));
        }
    }

    vector<bool> bfsAns;
    vector<ll> vec = {vS, vF};
    for(int j = 0; j< vec.size(); j++){
        bool temp = false;
        // unordered_set<ll> U;
        queue<ll> Q;

        Q.push(vec[j]);
        hashSetInsert(visited,vprev,vhash,vfree, vec[j], HSIZE);        
        int used = 1;
        int limit = n*k + 1;

        while(!Q.empty() && used < limit){
            ll v = Q.front();
            Q.pop();

            if(v == vec[(j+1)%2]){
                temp = true;
            }

            for(int i = 0; i<n; i++){
                ll cur = v;
                cur ^= (1LL<<i);
                if(!hashSetLookup(forbidden,fprev,fhash,cur,MAXK) && !hashSetLookup(visited,vprev,vhash,cur,HSIZE)){
                    Q.push(cur);
                    hashSetInsert(visited,vprev,vhash,vfree,cur,HSIZE);
                    used++;
                }
            }
            if(used >= limit){
                temp = true;
            }
        }
        if(used >= limit){
            temp = true;
        }
        bfsAns.PB(temp);
        hashSetClear(vhash,vfree,HSIZE);
    }

    return bfsAns[0] && bfsAns[1];    
}*/