#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

int n; ull d;
vector<int> X;

void getData(){
    X.clear();

    cin>>n>>d;
    string temp;
    cin>>temp;
    for(int i = 0; i<n; i++){
        X.PB(temp[i] - '0');
    }
}

void getRandom(){
    X.clear();

    srand(time(0));

    n = rand()%10+1;
    d = rand()%20+1;
    for(int i = 0; i<n; i++){
        int temp = rand()%2;
        X.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<d<<"\n";
    for(int i = 0; i<n; i++){
        cout<<X[i];
    }
    cout<<"\n";
}

int XOR(int a, int b){
    if((a == 0 && b == 0) || (a == 1 && b == 1)){
        return 0;
    }
    if((a == 1 && b == 0) || (a == 0 && b == 1)){
        return 1;
    }
    return -1;
}

vector<int> brute(){
    queue<int> Q;
    for(int i =0; i<n; i++){
        Q.push(X[i]);
    }

    for(ull i = 1; i<=d; i++){
        int a = Q.front();
        Q.pop();

        int temp = XOR(a,Q.front());
        Q.push(temp);
    }

    vector<int> ans;
    while(!Q.empty()){
        ans.PB(Q.front());
        Q.pop();
    }

    return ans;
}

vector<vector<int>> fastMultiply(vector<vector<int>> a, vector<vector<int>> b){
    //compress matrix
    vector<vector<ull>> compressA, compressB;
    for(int i =0; i<a.size(); i++){
        ull temp = 0;
        int ind = 0;
        int count = 0;
        while(ind < n){
            temp *= 10;
            temp += a[i][ind];
            ind++;

            if(count == 0){
                compressA[i].PB(temp);
                temp = 0;
                count = 0;
            }  
        }
        if(temp != 0){
            compressA[i].PB(temp);
        }
    }
    for(int i =0; i<b.size(); i++){
        ull temp = 0;
        int ind = 0;
        int count = 0;
        while(ind < n){
            temp *= 10;
            temp += b[i][ind];
            ind++;

            if(count == 0){
                compressB[i].PB(temp);
                temp = 0;
                count = 0;
            }  
        }
        if(temp != 0){
            compressB[i].PB(temp);
        }
    }

    //multiply
    vector<vector<int>> ans(a.size(), vector<int>(b.size(), 0));
    for(int i = 0; i<a.size(); i++){
        for(int j = 0; j<b.front().size(); j++){
            
            for(int o = 0; o<compressA[i].size(); o++){
                ull tempA = compressA[i][o];
                ull tempB = compressB[j][o];
                ull value = tempA & tempB;
                ans[i][j] += popcount(value);
            }
        }
    }

    return ans;
}

vector<vector<int>> fastPower(vector<vector<int>> m, ull x){
    vector<vector<vector<int>>> powers;
    powers.PB(m);
    int ind = 1;
    while((((ull)1)<<ind) < x){
        vector<vector<int>> temp = fastMultiply(powers.back(), powers.back());
        powers.PB(temp);
    }

    //get ans
    vector<vector<int>> ans;
    bool first = true;  
    for(int i =0 ; i<powers.size(); i++){
        if(x & (1<<i)){
            if(first){
                first = false;
                ans = powers[i];
            }else{
                vector<vector<int>> temp = fastMultiply(ans, powers[i]);
                ans = temp;
            }
        }
    }

    return ans;
}

vector<int> solve(){
    //creating matrix like
    //  000...001
    //  100...001
    //  010...000
    //  001...000
    //  ...
    //  000000100
    //  000000010

    vector<vector<int>> matrix(n,vector<int>(n, 0));
    for(int i =0 ; i <n-1; i++){
        matrix[i+1][i] = 1;
    }
    matrix[0][n-1] = 1;
    matrix[1][n-1] = 1;

    //fast power
    vector<vector<int>> temp = fastPower(matrix, d);
    vector<vector<int>> tempInput;
    tempInput.PB(X);

    //get ans
    vector<vector<int>> ansTemp = fastMultiply(tempInput, temp);

    vector<int> ans;
    for(int i = 0; i<n; i++){
        ans.PB(ansTemp[0][i]);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}