#include<iostream>
#include <vector>
#include <queue>

using namespace std;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>

int n, k;
int start = 0, finish = 0;
vector<int> removed;

void getData(){
    cin>>n>>k;
    for(int i = 1; i<=n; i++){
        int temp;
        cin>>temp;
        start += (1<<(n-i)) * temp;
    }
    for(int i = 1; i<=n; i++){
        int temp;
        cin>>temp;
        start += (1<<(n-i)) * temp;
    }
    for(int i = 0; i<k; i++){
        int num = 0;
        for(int j = 1; j<=n; j++){
            int temp;
            cin>>temp;
            num += (1<<(n-j)) * temp;
        }
        removed.PB(num);
    }
}

void getRandom(){
    n = rand()%3+1;
    k = rand()%5+1;
    start = rand()%(1<<(n-1))+1;
    finish = rand()%(1<<(n-1))+1;
    vector<bool> used(1<<n, false);
    for(int i = 0; i<k; i++){
        int a = rand()%(1<<(n-1))+1;
        while(used[a] || a == start || a == finish){
            a = rand()%(1<<(n-1))+1;
        }
        used[a] = true;
        removed.PB(a);
    }
}

void printData(){
    cout<<n<<" "<<k<<" ";
    for(int i = n; i>=1; i--){
        cout<<start && (1<<i);
    }
    for(int i = n; i>=1; i--){
        cout<<finish && (1<<i);
    }
    for(int i = 0; i<k; i++){
        for(int j = n; j>=1; j--){
            cout<<removed[i] && (1<<j);
        }
    }
}

bool brute(){
    vector<bool> vis((1<<n), false);
    for(int i = 0; i<k; i++){
        vis[removed[i]] = true;
    }
    queue<int> Q;
    Q.push(start);
    while(!Q.empty()){
        int v =  Q.front();
        Q.pop();
        for(int j = 0; j<n; j++){
            int cur = v;
            cur ^= (1<<j);
            if(!vis[cur]){
                vis[cur] = true;
                Q.push(cur);
                if(cur == finish){
                    return true;
                }
            }
        }
    }   
    return false;
}

bool solve(){
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1;test<=1 ;test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        bool ansB = brute();
        bool ansS = solve();
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