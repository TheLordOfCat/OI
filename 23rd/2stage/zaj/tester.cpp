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
    A.clear();
    B.clear();
    srand(time(0));
    n = rand() % 10 + 2;
    m = rand() % 15 + 2;
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
    vector<vector<int>> NWP(n+1, vector<int>(m+1, 0));

    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            if(A[i] == B[j]){
                int prevA = -1;
                for(int o = i-1; o > 0; o--){
                    if(A[o] == A[i]){
                        prevA = o;
                        break;
                    }
                }
                int prevB = -1;
                for(int o = j-1; o > 0; o--){
                    if(B[o] == B[j]){
                        prevB = o;
                        break;
                    }
                }
                if(prevA > 0 && prevB > 0){
                    NWP[i][j] = NWP[prevA-1][prevB-1] + 2;
                }else{
                    NWP[i][j] = 0;
                }
            }else{
                NWP[i][j] = 0;
            }
            NWP[i][j] = max(NWP[i][j], max(NWP[i-1][j],NWP[i][j-1]));
        }
    }

    return NWP[n][m];
}

int solve() {
    // creating prevA, prevB
    vector<int> prevA(n+1, -1), prevB(m+1, -1);

    //unefficient due to little memory
    for (int i = 1; i <= n; i++) {
        for(int j = i-1; j>0; j--){
            if(A[j] == A[i]){
                prevA[i] = j;
                break;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int temp;
        cin >> temp;
        B.PB(temp);
        prevB.PB(-1);
        for(int j = i-1; j>0; j--){
            if(B[j] == B[i]){
                prevB[i] = j;
                break;
            }
        }
    }

    // filling WNP
    vector<vector<int>> NWP(2, vector<int>(m+1, 0));

    vector<int> mem(m+1, 0); //holding the NWP for the last val
    for(int i = 1; i<=n; i++){
        NWP[i%2][0] = 0;
        for(int j = 1;j<=m; j++){
            if(A[i] == B[j] && prevA[i] > 0 && prevB[j] > 0){
                NWP[i%2][j] = mem[prevB[j]] + 2;
            }else{
                NWP[i%2][j] = 0;
            }
            NWP[i%2][j] = max(NWP[i%2][j], max(NWP[i%2][j-1], NWP[(i-1)%2][j]));
        }
        for(int j = 1; j<=m; j++){
            if(A[i] == B[j]){
                mem[j] = NWP[(i-1)%2][j-1]; 
            }
        }
    }

    int ans = NWP[n%2][m];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for (int test = 1; test <= 10'000; test++) {
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
            cout << "CORRECT\n";
    }
    return 0;
}