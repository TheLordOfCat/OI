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

void getRandom(){
    blocks.clear();

    srand(time(0));
    n = rand()%30+1;
    for(int i = 0; i<n; i++){
        int temp = rand()%3;
        blocks.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        if(blocks[i] == 0){
            cout<<"B";
        }else if(blocks[i] == 1){
            cout<<"C";
        }else if(blocks[i] == 2){
            cout<<"S";
        }
    }
}

int brute(){
    int ans = -1;
    for(int i = 0; i<n; i++){
        for(int j = i; j<n; j++){
            vector<int> count = {0,0,0};
            for(int o = i; o<=j; o++){
                count[blocks[o]]++;
            }
            if((count[0] != count[1] || count[0] == 0) && (count[1] != count[2] || count[1] == 0) && (count[2] != count[0] || count[2] == 0)){
                ans = max(ans, j-i+1);
            }
        }
    }
    return ans;
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

    int op = 0;
    for(int test = 1; test<=10'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        int ansB = brute();
        int ansS = solve();
        if(ansB != ansS){
            cout<<"ERORR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }
    return 0;
}