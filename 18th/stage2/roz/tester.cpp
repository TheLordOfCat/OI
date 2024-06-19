#include<iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int ALPHA = 26;
const int INF = 2'000'000'000;

int n;
vector<char> s;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        char temp;
        cin>>temp;
        s.PB(temp);
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    for(int  i = 0; i<n; i++){
        int temp = rand()%26;
        char cTemp = temp + 'a';
        s.PB(cTemp);
    }
}

void printData(){
    cout<<"DATA:\n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<s[i];
    }
    cout<<"\n";
}

int brute(){
    int ans = 0;

    for(int left = 0; left<n; left++){
        for(int right = left; right<n; right++){
            
            vector<int> let(ALPHA, 0);
            for(int i = left; i<=right; i++){
                let[s[i] - 'a']++;
            }   

            for(int i = 0; i<ALPHA; i++){
                for(int j = 0; j<ALPHA; j++){
                    if(let[i] > 0 && let[j] > 0){
                        int dif = let[i] - let[j];
                        ans = max(ans,dif);
                    }
                }
            }
        }
    }

    return ans;
}

int solve(){
    int ans = 0;

    vector<vector<int>> next(26, vector<int>());
    for(int i = 0; i<n; i++){
        next[s[i] - 'a'].PB(i);
    }

    for(int i = 0; i<ALPHA; i++){
        next[i].PB(INF);
    }

    for(int l = 0; l<ALPHA; l++){
        for(int k = 0; k<ALPHA; k++){

            if(next[l].size() > 0 && next[k].size() > 0 ){
                int sum = 0, mini = INF, lastSum = 0;
                int len = next[l].size() + next[k].size();                
                int itrL = 0, itrK = 0;

                for(int  i = 0; i<len; i++){
                    if(next[k][itrK] > next[l][itrL]){
                        sum += 1;
                        itrL++;
                    }else if(itrK != INF){
                        sum -= 1;
                        itrK ++;
                        mini = min(mini, lastSum);
                        lastSum = sum;
                    }
                    ans = max(ans, sum - mini);
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }   
        int ansB = brute();
        int ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}