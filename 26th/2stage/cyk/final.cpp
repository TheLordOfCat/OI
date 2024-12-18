#include <iostream>
#include <vector>
#include "cyklib.hpp"

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

void solve(){
    const int log = 19;
    int ans = 0;
    
    //faze 1 - aproximating the ans
    ll base = circular_shift(0);
    ll cur = circular_shift(1);
    ans = 1;
    if(cur == base){
        give_answer(ans);       
    }
    int lastLen;
    for(int i = 1; i<log; i++){
        //verify
        ll temp = circular_shift(1<<i);
        if(temp == base){
            ans += (1<<i);
            give_answer(ans);
            break;
        }

        if(cur < base && base < temp){ //normal case
            lastLen = i;
            break;
        }else if(temp < cur && cur < base){ // the biggest case
            lastLen = i;
            break;
        }else if(temp < cur && base < cur){ // the smallest
            lastLen = i;
            break;
        }
        ans += (1<<i);
    }  

    //faze 2 - narrowing the ans
    int baseAns = ans;
    for(int i = lastLen-1; i>= 0; i--){
        ll base = circular_shift(ans);

        ll cur = circular_shift(1<<i);
        ll temp = circular_shift(1<<i);
        if(cur == base){
            baseAns += (1<<i);
            give_answer(baseAns);
            break;
        }
        if(temp == base){
            baseAns += 2*(1<<i);
            give_answer(baseAns);
            break;
        }

        if(cur < base && base < temp){
            baseAns += (1<<i);
        }else if(base < cur && base < temp && cur > temp){
            baseAns += (1<<i);
        }else if(cur <base && temp < base && cur > temp){
            baseAns += (1<<i);
        }
    }

    //ans
    give_answer(ans);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}