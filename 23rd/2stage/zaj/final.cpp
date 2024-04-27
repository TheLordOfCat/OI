#include <iostream>
#include <vector>

using namespace std;

#define PB push_back

int n, m;
vector<int> A, B;

vector<int> prevA, prevB;

void getData() {
    cin >> n >> m;
    A.push_back(-1);
    B.push_back(-1);
    prevA.push_back(-1);
    prevB.push_back(-1);
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;    
        A.PB(temp);
        prevA.PB(-1);
        //unefficient due to little memory
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
        //unefficient due to little memory
        for(int j = i-1; j>0; j--){
            if(B[j] == B[i]){
                prevB[i] = j;
                break;
            }
        }
    }
}

int solve() {
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

    getData();
    int ansS = solve();
    cout << ansS << "\n";

    return 0;
}