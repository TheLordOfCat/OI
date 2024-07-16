#include <iostream>
#include <vector>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using ll = long long int;
using ull = unsigned long long int;

const int MAXN = 1'000'000;
const int MAXK = 1'000'000;

int n, k;
vector<int> c;
int lenX, lenY;
vector<int> vecX;
vector<int> vecY;

void getData(){
    cin>>n>>k;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        c.PB(temp);
    }
    cin>>lenX>>lenY;
    for(int i = 0; i<lenX; i++){
        int temp;
        cin>>temp;
        vecX.PB(temp);
    }
    for(int i =0; i < lenY; i++){
        int temp;
        cin>>temp;
        vecY.PB(temp);
    }
}

bool customSortLeft(const PII a, const PII b){
    return a.first < b.first;
}

bool customSortRight(const PII a, const PII b){
    return a.first > b.first;
}

vector<int> solve(){
    vector<PII> colorPairs(k+1, MP(-1,-1));

    //left
    vector<PII> lastLeft(k+1, MP(MAXN+1, MAXN+1));
    for(int i = 1; i<=k; i++) lastLeft[i].second = i;
    vector<int> next(n+1, MAXN+1);
    for(int i = n-1; i>=0; i--){
        next[i] = lastLeft[c[i]].first;
        lastLeft[c[i]].first = i;
    }

    vector<int> chain(lenX-1, 0);
    for(int i = 0; i<lenX-1; i++){
        chain[i] = lastLeft[vecX[i]].first;
    }

    // lastLeft.erase(lastLeft.begin());
    // sort(lastLeft.begin(), lastLeft.end(), customSortLeft);

    /*
    bool ok = true;
    for(int i = 0; i<k; i++){
        int ind = lastLeft[i].first;
        for(int j = 0; j<chain.size(); j++){
            while(chain[j] <= ind){
                chain[j] = next[chain[j]];
                if(chain[j] > n){
                    ok = false;
                    break;
                }
            }
            if(!ok){
                break;
            }else{
                ind = chain[j];
            }
        }
        if(ok){
            if(chain.size() == 0){
                colorPairs[lastLeft[i].second].first = lastLeft[i].first+1;
            }else{
                colorPairs[lastLeft[i].second].first = chain.back()+1;
            }
        }else{
            for(int j = i; j<k; j++){
                colorPairs[lastLeft[j].second].first = MAXN+1;
            }
            break;
        }
    }
    */

    vector<bool> vis(k+1, false);
    bool ok = true;
    for(int i = 0; i<n; i++){
        if(!vis[c[i]]){
            int ind = i;
            for(int j = 0; j<chain.size(); j++){
                while(chain[j] <= ind){
                    chain[j] = next[chain[j]];
                    if(chain[j] > n){
                        ok = false;
                        break;
                    }
                }
                if(!ok){
                    break;
                }else{
                    ind = chain[j];
                }
            }
            if(ok){
                if(chain.size() == 0){
                    colorPairs[c[i]].first = lastLeft[c[i]].first+1;
                }else{
                    colorPairs[c[i]].first = chain.back()+1;
                }
            }else{
                for(int j = 1; j<=k; j++){
                    if(!vis[j]){
                        colorPairs[j].first = MAXN+1;
                        vis[j] = true;
                    }
                }
                break;
            }
            vis[c[i]] = true;
        }
    }

    //right
    vector<PII> lastRight(k+1, MP(-1,-1));
    for(int i = 1; i<=k; i++) lastRight[i].second = i;
    for(int i = 0; i<n; i++){
        next[i] = lastRight[c[i]].first;
        lastRight[c[i]].first = i;
    }

    chain.clear();
    chain.assign(lenY-1, 0);

    for(int i = 0; i<lenY-1; i++){
        chain[i] = lastRight[vecY[i]].first;
    }

    lastRight.erase(lastRight.begin());
    sort(lastRight.begin(), lastRight.end(), customSortRight);

    /*
    ok = true;
    for(int i = 0; i<k; i++){
        int ind = lastRight[i].first;
        for(int j = 0; j<chain.size(); j++){
            while(chain[j] >= ind){
                chain[j] = next[chain[j]];
                if(chain[j] < 0){
                    ok = false;
                    break;
                }
            }
            if(!ok){
                break;
            }else{
                ind = chain[j];
            }
        }
        if(ok){
            if(chain.size() == 0){
                colorPairs[lastLeft[i].second].second = n-1;
            }else{
                colorPairs[lastRight[i].second].second = chain.back();
            }
        }else{
            for(int j = i; j<k; j++){
                colorPairs[lastRight[j].second].second = -1;
            }
            break;
        }
    }     
    */

    ok = true;
    for(int i = 0; i<=k; i++) vis[i] = false;
    for(int i = n-1; i>=0; i--){
        if(!vis[c[i]]){
            int ind = i;
            for(int j = 0; j<chain.size(); j++){
                while(chain[j] >= ind){
                    chain[j] = next[chain[j]];
                    if(chain[j] < 0){
                        ok = false;
                        break;
                    }
                }
                if(!ok){
                    break;
                }else{
                    ind = chain[j];
                }
            }
            if(ok){
                if(chain.size() == 0){
                    colorPairs[c[i]].second = lastRight[c[i]].second;
                }else{
                    colorPairs[c[i]].second = chain.back();
                }
            }else{
                for(int j = 1; j<=k; j++){
                    if(!vis[j]){
                        colorPairs[j].second = -1;
                        vis[j] = true;
                    }
                }
                break;
            }
            vis[c[i]] = true;
        }
    }
    
    //plotting the segments
    vector<int> seg(n+1, 0);
    for(int i = 1; i<=k; i++){
        if(!(colorPairs[i].first > n || colorPairs[i].second < 0 || colorPairs[i].first > colorPairs[i].second)){
            seg[colorPairs[i].first]++;
            seg[colorPairs[i].second]--;
        }
    }

    //getting the ans
    vector<int> ans;
    int sum = 0;
    for(int i = 0; i<n; i++){
        sum += seg[i];
        if(sum > 0){
            if(vecX.back() == c[i]){
                ans.PB(i+1);
            }
        }
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    vector<int> ansS = solve();

    cout<<ansS.size()<<"\n";
    for(int j =0; j<ansS.size(); j++){
        cout<<ansS[j]<<" ";
    }
    cout<<"\n";

    return 0;
}