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
#define MP make_pair
#define PB push_back

int n;
vector<PULLI> col;
PULLI shortCol, tallCol;

void getData() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        col.PB(MP(a, b));
    }
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    shortCol = MP(a, b);
    tallCol = MP(c, d);
}

bool pairCompare(PII a, PII b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

void getRandom() {
    srand(time(0));

    n = rand() % 10 + 1;

    for (int i = 0; i < n; i++) {
        int a = rand() % n + 1, b = rand() % 3 + 2;
        col.PB(MP(a, b));
    }

    sort(col.begin(), col.end(), pairCompare);

    int a = rand() % n + 1, b = rand() % 5 + 3, c = rand() % n + 1,
    d = rand() % 5 + 3;
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

int brute() {
    int ans = 0;
    vector<int> dist;
    
    // distance to next collumn
    for(int i = 0; i<col.size()-1; i++){
        int dif = col[i+1].first - col[i].first + col[i].second;
        dist.PB(dif);
    }

    //right = left 
    for(int i = 0; i<n; i++){
        int countS = shortCol.first, countT = tallCol.first;

        int con = countS + countT;
        int ind = i;
        while(countS > 0 || countT > 0){
            if(ind >= n-1){
                break;
            }
            int len = dist[ind];
            while(len > 0){
                //want to fill tall first
                if(len > tallCol.second){
                    if(countT > 0){
                        len -= tallCol.second;
                        countT--;
                    }else{
                        len -= shortCol.second;
                        countS--;
                    }
                }else{
                    if(countS > 0){
                        len -= shortCol.second;
                        countS--;
                    }else{
                        len -= tallCol.second;
                        countT--;
                    }
                }
                if(countS == 0 && countT == 0){
                    break;
                }
            }
            if(len <= 0) con++;
            ind++;
        }
        ans = max(ans,con);
    }

    return ans;
}

ull solve() {
    ull ans = 0;
    vector<ull> dist;
    
    // distance to next collumn
    for(int i = 0; i<col.size()-1; i++){
        ll dif = col[i+1].first - col[i].first + col[i].second;
        dist.PB(dif);
    }

    //processing catapilar method
    ull left = 0; ull right = 0;
    set<pair<ull,ull>> S;
    
    ull countT = tallCol.first;
    ull countS = shortCol.first;

    vector<pair<ull,ull>> reduceSeg(n+1, MP(0,0));

    while(right != n-1){
        bool opti = false;
        do{
            ull reduceT = 0;
            ull reduceS = 0;
            opti = false;

            ull len = dist[right + 1];

            //use tall
            ull use = len / tallCol.second;
            if(len % tallCol.second != 0){
                use++;
            }

            if(use < countT){
                reduceT += countT;
                len %= tallCol.second;
            }else{
                len -= tallCol.second * (countT-reduceT);
                reduceT += countT-reduceT;
            }

            //minimize short


            //use short 
            ull use = len / shortCol.second;
            if(len % shortCol.second != 0){
                use++;
            }

            if(use < countS){
                reduceS += countS;
                len %= shortCol.second;
            }else{
                len -= shortCol.second * (countS-reduceS);
                reduceS += countS-reduceS;
            }

            if(len != 0){
                opti = true;
                ans = max(ans, right - left + 1 + shortCol.first + tallCol.first);
                countS += reduceSeg[left].first;
                countT += reduceSeg[left].second;
                left++;
            }else{
                reduceSeg[right] = MP(reduceS, reduceT);
                right++;
            }

        }while(opti);
        ans = max(ans, right- left + 1 + shortCol.first + tallCol.first);

        right++;
    }

    ans = max(ans, right- left + 1 + shortCol.first + tallCol.first);

    return ans;
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
        ull ansS = solve();
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