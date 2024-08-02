#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

int n, k;
vector<int> m;

void getData(){
    cin>>n>>k;
    for(int i = 0; i<k; i++){
        int temp;
        cin>>temp;
        m.PB(temp);
    }
}

void getRandom(){
    srand(time(0));
    n = rand()%50+1;
    k = rand()%min(n,10)+1;
    vector<bool> vis(n+1, false);
    for(int i = 0; i<k; i++){
        int a = rand()%n+1;
        while(vis[a]){
            a = rand()%n+1;
        }
        vis[a] = true;
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<k<<"\n";
    for(int i = 0; i<k; i++){
        cout<<m[i]<<" ";
    }
    cout<<"\n";
}

int brute(){
    vector<bool> banned(n, false);
    for(int i = 1; i<n; i++){
        for(int j= 0; j<k-1; j++){
            if(m[j]%i == 0){
                banned[i] = true;
            }
        }
    }

    vector<bool> ok(n, false);
    
    int ind = m.back();
    while(!ok[ind]){
        ok[ind] = true;
        ind += m.back(); 
        ind %= n;
    }

    int ans = 0;
    for(int i = 0; i<n; i++){
        if(ok[i] && !banned[i]){
            ans++;
        }
    }
    return ans;
}

int solve(){
    vector<bool> banned(n, false);
    for(int i = 0; i<k-1; i++){
        for(int j = 1; j*j<= m[i]; j++){
            if(m[i]%j == 0){
                banned[j] = true;
            }
            if(m[i]/j != j){
                banned[j] = true;
            }
        }
    }

    vector<bool> ok(n, false);
    int ind = 24;
    while(!ok[ind]){
        ok[ind] = true;
        ind += m.back(); 
    }

    int ans = 0;
    for(int i = 0; i<n; i++){
        if(ok[i] && !banned[i]){
            ans++;
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
            cout<<"BRUTE:"<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }


    return 0;
}