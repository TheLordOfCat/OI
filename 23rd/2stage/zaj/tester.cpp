#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define PB push_back

int n, m;
vector<int> A, B;

void getData() {
    cin >> n >> m;
    A.push_back(-1);
    B.push_back(-1);
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;    
        A.PB(temp);
    }
    for (int i = 0; i < m; i++) {
        int temp;
        cin >> temp;
        B.PB(temp);
    }
}

void getRandom() {
    srand(time(0));
    n = rand() % 10 + 1;
    m = rand() % 15 + 1;
    A.push_back(-1);
    B.push_back(-1);

    for (int i = 0; i < n; i++) {
        int temp = rand() % 10 + 1;
        A.PB(temp);
    }
    for (int i = 0; i < m; i++) {
        int temp = rand() % 10 + 1;
        B.PB(temp);
    }
}

void printData() {
    cout << n << " " << m << "\n";
    for (int i = 1; i <= n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";
    for (int i = 1; i <= m; i++) {
        cout << B[i] << " ";
    }
    cout << "\n";
}

int brute() {
    int ans = 0;
    int maxNum = 0;
    for(int i = 1; i<=n; i++) maxNum = max(maxNum, A[i]);
    for(int i = 1; i<=m; i++) maxNum = max(maxNum, B[i]);
    vector<int> nextA(maxNum+1, -1),nextB(maxNum+1, -1);

    vector<int> memo(maxNum+1, -1);
    for(int i = n; i>0; i--){
        nextA[i] = memo[A[i]];
        memo[A[i]] = i;
    }

    memo.clear();
    for(int i = 0; i<maxNum+1; i++)memo.PB(-1);

    for(int i = m; i>0; i--){
        nextB[i] = memo[B[i]];
        memo[B[i]] = i;
    }

    for(int i = 1; i<=n; i++){
        vector<int> avPair;
        for(int j = 1; j<=i;j ++){
            if(nextA[j] != -1){
                avPair.PB(A[j]);
                j = nextA[A[j]];
            }
        }
        bool ok = true;
        int ind = 0;
        int itr = 0;
        for(int j = 0; j<m;j++){
            if(ind > avPair.size()) break;
            if(B[j] == ind){
                if(itr == 0){
                    itr++;
                }else{
                    itr = 0;
                    ind++;
                }
            }
        }
        if(ind <= avPair.size()) ok = false;
        if(ok){
            ans = max(ans, (int)avPair.size());
        }
    }
    return ans;
}

int solve() {
    //creating prevA, prevB
    int maxNum = 0;
    for(int i = 0; i<n; i++) maxNum = max(maxNum, A[i]);
    for(int i = 0; i<m; i++) maxNum = max(maxNum, B[i]);
    vector<int> prevA(maxNum+1, -1), prevB(maxNum+1, -1);

    vector<int> last(maxNum+1, -1);
    for(int i = n-1; i>=0; i--){
        prevA[i] = last[A[i]];
        last[A[i]] = i;
    }

    last.clear();
    for(int i = 0; i<maxNum+1; i++) last.PB(-1);

    for(int i = m-1; i>=0; i--){
        prevB[i] = last[B[i]];
        last[B[i]] = i;
    }

    vector<int> NWP[2] = {vector<int>(m+1, 0), vector<int>(m+1, 0)};

    int ans = 0;
    vector<int> mem(m+1, 0); //holding the NWP for the last val
    for(int j = 0; j<=m; j++){
        NWP[0][j] = 0;
    }
    for(int i = 1; i<=n; i++){
        NWP[i%2][0] = 0;
        for(int j = 0;j<=m; j++){
            if(A[i] == B[j] && prevA[i] > 0 && prevB[i] > 0){
                NWP[i][j] = mem[prevB[i]] + 2;
            }else{
                NWP[i%2][j] = 0;
            }
            NWP[i%2][j] = max(NWP[i%2][j], max(NWP[i%2][j-1], NWP[(i-1)%2][j]));
        }
        for(int j = 0; j<=m; j++){
            if(A[i] == B[j]){
                mem[j] = NWP[(i-1)%2][j-1]; 
            }
        }
    }

    return NWP[n%2][m];
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
        return 0;
        }
        cout << "CORRECT\n";
        }
    return 0;
}