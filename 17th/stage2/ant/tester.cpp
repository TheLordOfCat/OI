#include<iostream>
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

const int INF = 2'000'000'000;

int n;
vector<int> s;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        s.PB(temp);
    }
}

void getRandom(){
    srand(time(0));
    s.clear();

    //complete random
    n = rand()%10+1;
    for(int i =0 ;i<n; i++){
        int temp = rand()%2;
        s.PB(temp);
    }

    //couple antipalindroms
    n = 0;
    int pal = rand()%3+1;
    for(int i =0 ;i<pal; i++){
        int len = rand()%3+1;
        vector<int> temp;
        for(int j = 0; j<=len; j++){
            int val = rand()%2;
            if(val == 0){
                temp.insert(temp.begin(), val);
                temp.PB(1);
            }else{
                temp.insert(temp.begin(), val);
                temp.PB(0);
            }
        }
        for(int j = 0; j<temp.size(); j++){
            s.PB(temp[j]);
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<s[i];
    }
    cout<<"\n";
}

ull brute(){
    ull ans = 0;
    for(int i = 0; i<n; i++){
        for(int j = i; j<n; j++){

            //check if antisymetrical
            bool ok = true;

            for(int o  = 0; i+o<=j-o; o++){
                if(s[i+o] == s[j-o]){
                    ok =false;
                    break;
                }
            }

            if(ok){
                ans++;
            }
        }
    }
    return ans;
}

ull solve(){
    ull ans = 0;

    vector<int> S = s;
    S.insert(S.begin(), INF);
    S.PB(INF-1);
    vector<int> negS;
    for(int i = 0; i<S.size(); i++){
        if(S[i] == 0){
            negS.PB(1);
        }else if(S[i] == 1){
            negS.PB(0);
        }else{
            negS.PB(S[i] * (-1));
        }
    }

    //edited Manacher algorithm 
    vector<int> R(S.size(), 0);
    int i = 1;
    int j = 0;    
    while(i<=S.size()-1){
        while(S[i-j] == negS[i+j+1]) j++;
        R[i] = j;
        int k = 1;
        while(R[i-k] != R[i] - k && k<=j){
            R[i+k] = min(R[i-k], R[i] - k);
            k++;
        }
        j = max(j-k, 0);
        i += k;
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
        ull ansB = brute();
        ull ansS = solve();
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