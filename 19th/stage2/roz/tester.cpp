#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdlib>
#include <ctime>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using ull = unsigned long long int;

int k;

void getData(){
    cin>>k;
}

void getRandom(){
    srand(time(0));
    k = rand()%100+1;
}

void printData(){
    cout<<"\nDATA: "<<k<<"\n";
}

vector<int> fibonaci(int l){
    vector<int> ans;
    ans.PB(0);
    ans.PB(1);

    int cur = 0+1;
    while(cur <= l){
        cur = ans[ans.size()-1] + ans[ans.size()-2];
        ans.PB(cur);
    }

    return ans;
}

int brute(){
    vector<int> fib = fibonaci(k);

    int ans = 0;
    int cur = k;
    while(cur != 0){
        int m = 0;
        for(int i = 0; i<fib.size(); i++){
            if(fib[i+1] > cur){
                m = i;
                break;
            }
        }

        if(cur - fib[m] < fib[m+1] - cur){
            ans++;
            cur -= fib[m];
        }else{
            ans++;
            cur -= fib[m+1];
        }

        if(cur < 0 ){
            cur *= (-1);
        }
    }

    return ans;
}

int solve(){
    vector<int> fib = fibonaci(k);

    int ans = 0;
    int cur = k;
    while(cur != 0){
        auto itr = lower_bound(fib.begin(),fib.end(), cur);
        int m = itr - fib.begin()-1;

        if(cur - fib[m] < fib[m+1] - cur){
            ans++;
            cur -= fib[m];
        }else{
            ans++;
            cur = fib[m+1] - cur;
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;

    int p = 1;
    // cin>>p;
    for(int i = 0; i<p; i++){
        for(int test =1 ;test<=100000; test++){
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
                cout<<"BURUTE: "<<ansB<<"\n";
                cout<<"SOLVE: "<<ansS<<"\n";
                return 0;
            }
            cout<<"CORRECT\n";
        }
    }

    return 0;
}