#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int, int>
#define PULLI pair<ull,int>
#define PLL pair<ll,ll>
#define MP make_pair
#define PB push_back

int n;
vector<PLL> col;
PLL shortCol, tallCol;

void getData() {
    col.clear();

    cin >> n;
    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        col.PB(MP(a, b));
    }
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    tallCol = MP(a, b);
    shortCol = MP(c, d);
}

bool pairCompare(PLL a, PLL b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

void getRandom() {
    col.clear();

    srand(time(0));

    int len = 100;
    n = rand() % 3 + 3;
    vector<bool> used(len, false);
    for (int i = 0; i < n; i++) {
        ll a = rand() % len + 1, b = rand() % 10 + 10;
        while(used[a]){
            a = rand() % len + 1;
        }
        used[a] = true;
        col.PB(MP(a, b));
    }

    sort(col.begin(), col.end(), pairCompare);

    ll a = rand() % n + 1, b = rand() % 10 + 5, c = rand() % n + 1, d = rand() % 4 + 1;
    shortCol = MP(a, b);
    tallCol = MP(c, d*b);
}

void printData() {
    cout << "DATA: \n";
    cout << n << "\n";
    for (int i = 0; i < col.size(); i++) {
        cout << col[i].first << " " << col[i].second << "\n";
    }
    cout << tallCol.first << " " << tallCol.second << " " << shortCol.first << " " << shortCol.second << "\n";
}

int brutePush(ll v, vector<PLL>& plane){
    ll multi = tallCol.second/shortCol.second;
    ll shortCount = shortCol.first, tallCount = tallCol.first;

    int ans = 1 + shortCount + tallCount;
    ll cur = v;
    while(cur <plane.size()-1){
        ll len = plane[cur+1].first - (plane[cur].first + plane[cur].second);
        ll div = len/tallCol.second;
        ll r = len - div*tallCol.second;
        if(len > 0){
            if(r != 0){
                if(r <= shortCol.first){
                    if(shortCount > 0){
                        shortCount--;
                    }else  if(tallCount > 0){
                        tallCount--;
                    }else{
                        return ans;
                    }
                }else{
                    if(tallCount > 0){
                        tallCount--;
                    }else if(shortCount > 0){
                        shortCount--;
                    }else{
                        return ans;
                    }
                }
            }
            for(int i = 0; i<div; i++){
                if(tallCount > 0){
                    tallCount--;
                }else if(shortCount>=multi){
                    shortCount-= multi*div;
                }else{
                    return ans;
                }
            }
        }
        ans++;
        cur++;
    }

    return ans;
}

int brute() {
    int ans = shortCol.first + tallCol.first;
    if(col.size() == 1) ans++;

    vector<PLL> colCopy = col;
    for(int i =0 ; i<col.size()-1; i++){
        int temp = brutePush(i,colCopy);
        ans = max(ans, temp);
    }

    ll last = colCopy.back().first; 
    for(int i = colCopy.size()-1; i>=0; i--){
        colCopy[i].first = last - colCopy[i].first;
    }

    reverse(colCopy.begin(), colCopy.end());

    for(int i =0 ; i<col.size()-1; i++){
        int temp = brutePush(i,colCopy);
        ans = max(ans, temp);
    }

    return ans;
}

ll solvePush(vector<PLL> c){
    ll ans = shortCol.first + tallCol.first + 1;

    //catapilar method
    vector<ll> gaps;
    for(int i =0; i<c.size()-1; i++){
        ll len = c[i+1].first - (c[i].first+c[i].second);
        gaps.PB(len);
    }

    int beg = 0, end = 0;
    vector<PLL> gapsUse(c.size()+1, MP(0,0));
    vector<bool> used(n+1, false);
    priority_queue<PII> E;
    queue<int> Q;
    ll shortCount = shortCol.first, tallCount = tallCol.first;


    while(end != c.size()-1){
        ll len = gaps[end];

        if(len < 0){
            end++;
            ll b = end-beg+1 + shortCol.first + tallCol.first;
            ans = max(ans, b);
            continue;
        }

        ll div = len/shortCol.second;
        ll r = len - div*shortCol.second;
        if(r != 0){
            div++;
        }

        ll multi = tallCol.second/shortCol.second;
        if(div <= shortCount + tallCount*multi){ //add gap
            ll t = div/multi;
            if(t > tallCount){
                t = tallCount;
            }
            tallCount -= t;
            div -= multi*t;

            gapsUse[end].second = t;
            if(div > 0){
                if(shortCount > div){
                    shortCount -= div;
                    gapsUse[end].first = div;
                }else{ //excessive tall
                    tallCount--;
                    gapsUse[end] = MP(0, t+1);
                    E.push(MP(end, div));
                }
            }
            Q.push(end);
            end++;
        }else{ // remove gap
            if(Q.size() != 0){
                int v = Q.front();
                PLL p = gapsUse[v];
                used[v] = true;
                Q.pop();

                shortCount += p.first;
                tallCount += p.second;

                if(!E.empty()){
                    PII e = E.top();
                    E.pop();

                    if(shortCount >= e.second){
                        shortCount -= e.second;
                        gapsUse[e.first].first--;
                        gapsUse[e.first].second += e.second;
                    }

                    E.push(e);
                }

                beg++;
            }else{
                beg++;
                end++;
            }
        }

        ll b = end-beg+1 + shortCol.first + tallCol.first;
        ans = max(ans, b);
    }

    return ans;
}

ll solve() {
    ll ans = shortCol.first + tallCol.first + 1;

    ll temp = solvePush(col);
    ans = max(ans, temp);

    vector<PLL> colCopy = col;
    ll last = colCopy.back().first; 
    for(int i = colCopy.size()-1; i>=0; i--){
        colCopy[i].first = last - colCopy[i].first;
    }

    reverse(colCopy.begin(), colCopy.end());

    temp = solvePush(colCopy);
    ans = max(ans, temp);
    
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for (int test = 1; test <= 1000000; test++) {
        cout << "TEST nr." << test << " = ";
        if (op == 1) {
            getData();
        } else {
            getRandom();
        }
        int ansB = brute();
        ll ansS = solve();
        if (ansB != ansS) {
            cout << "ERROR\n";
            cout << "BRUTE: " << ansB << "\n";
            cout << "SOLVE: " << ansS << "\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}