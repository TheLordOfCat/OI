#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

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
    shortCol = MP(a, b);
    tallCol = MP(c, d);
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

    n = rand() % 10 + 1;

    for (int i = 0; i < n; i++) {
        ll a = rand() % n + 1, b = rand() % 3 + 2;
        col.PB(MP(a, b));
    }

    sort(col.begin(), col.end(), pairCompare);

    ll a = rand() % n + 1, b = rand() % 5 + 3, c = rand() % n + 1, d = rand() % 5 + 3;
    shortCol = MP(a, b);
    tallCol = MP(c, d);
}

void printData() {
    cout << "DATA: \n";
    cout << n << "\n";
    for (int i = 0; i < col.size(); i++) {
        cout << col[i].first << " " << col[i].second << "\n";
    }
    cout << shortCol.first << " " << shortCol.second << "\n";
    cout << tallCol.first << " " << tallCol.second << "\n";
}

int brutePush(ll v, vector<PLL>& plane){
    ll multi = tallCol.first/shortCol.first;
    ll shortCount = shortCol.first, tallCount = tallCol.first;

    int ans = 1 + shortCount + tallCount;
    ll cur = v;
    while(cur <plane.size()-1){
        ll len = plane[cur+1].first - (plane[cur].first + plane[cur].second);
        ll div = len/tallCol.first;
        ll r = len - div*tallCol.first;
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
                shortCount-= multi;
            }else{
                return ans;
            }
        }
        ans++;
        cur++;
    }

    return ans;
}

int brute() {
    int ans = 0;

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

ll solve() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for (int test = 1; test <= 1; test++) {
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
    }

    return 0;
}