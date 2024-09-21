#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int, int>
#define MP make_pair
#define PB push_back

int n;
vector<PII> col;
PII shortCol, tallCol;

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

    for(int i = 0; i<n; i++){
        int countS = shortCol.first, countT = tallCol.first;
        //right
        int con = countS + countT;
        int ind = i;
        while(countS > 0 || countT > 0){
            if(ind >= n-1){
                break;
            }
            int len = dist[ind];
            while(len > 0){
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

        //left
        con = countS + countT;
        ind = i;
        while(countS > 0 || countT > 0){
            if(ind <= 0){
                break;
            }
            int len = dist[ind-1];
            while(len > 0){
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
            ind--;
        }

        ans = max(ans,con);
    }

    return ans;
}

int solve() {
    int ans = 0;
    vector<int> dist;
    
    // distance to next collumn
    for(int i = 0; i<col.size()-1; i++){
        int dif = col[i+1].first - col[i].first + col[i].second;
        dist.PB(dif);
    }

    //processing catapilar method
    int left = 0; int right = 0;

    int countS = shortCol.first;
    int countT = tallCol.first;
    int wastedT = 0;
    while(right != n-1){
        if(dist[right] > addCount * height){
            ans = max(ans, right- left + 1 + shortCol.first + tallCol.first);
            while(dist[right] > addCount * height){

            }
        }else{
            addCount -= (dist[right]/ height + 1);
            right++;
        }
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
        int ansS = solve();
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