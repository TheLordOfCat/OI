#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define PB push_back
#define PII pair<int,int>
#define MP make_pair

int n;
vector<int> blocks;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        char c;
        cin>>c;
        if(c == 'B'){
            blocks.PB(0);
        }else if(c == 'C'){
            blocks.PB(1);
        }else if(c == 'S'){
            blocks.PB(2);
        }
    }
}

int solve(){
    int ans = 0;

    //left
    vector<int> count = {0,0,0};
    for(int i = 0; i< n; i++){
        count[blocks[i]]++;
        if((count[0] != count[1] || count[0] == 0) && (count[1] != count[2] || count[1] == 0) && (count[2] != count[0] || count[2] == 0)){
            ans = max(ans, i+1);
        }
    }

    count = {0,0,0};
    for(int i = 1; i< n; i++){
        count[blocks[i]]++;
        if((count[0] != count[1] || count[0] == 0) && (count[1] != count[2] || count[1] == 0) && (count[2] != count[0] || count[2] == 0)){
            ans = max(ans, i+1 - 1);
        }
    }

    count = {0,0,0};
    for(int i = 2; i< n; i++){
        count[blocks[i]]++;
        if((count[0] != count[1] || count[0] == 0) && (count[1] != count[2] || count[1] == 0) && (count[2] != count[0] || count[2] == 0)){
            ans = max(ans, i+1 - 2);
        }
    }

    //right
    count = {0,0,0};
    for(int i = n-1; i >= 0; i--){
        count[blocks[i]]++;
        if((count[0] != count[1] || count[0] == 0) && (count[1] != count[2] || count[1] == 0) && (count[2] != count[0] || count[2] == 0)){
            ans = max(ans, n-i);
        }
    }

    count = {0,0,0};
    for(int i = n-2; i >= 0; i--){
        count[blocks[i]]++;
        if((count[0] != count[1] || count[0] == 0) && (count[1] != count[2] || count[1] == 0) && (count[2] != count[0] || count[2] == 0)){
            ans = max(ans, n-1-i);
        }
    }

    count = {0,0,0};
    for(int i = n-3; i >= 0; i--){
        count[blocks[i]]++;
        if((count[0] != count[1] || count[0] == 0) && (count[1] != count[2] || count[1] == 0) && (count[2] != count[0] || count[2] == 0)){
            ans = max(ans, n-2-i);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    int ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}