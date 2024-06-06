#include<iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

int m;
vector<int> b;
int n;
vector<int> a;

void getData(){
    cin>>m;
    for(int i =0; i<m; i++){
        int temp;
        cin>>temp;
        b.PB(temp);
    }
    cin>>n;
    for(int i =0; i<n; i++){
        int temp;
        cin>>temp;
        a.PB(temp);
    }
}

void getRandom(){
    b.clear();
    a.clear();

    srand(time(0));
    m =rand()%300+1;
    int len = 1000;
    vector<bool> bon(len+1, false);
    for(int i =0; i<m; i++){
        int a = rand()%len +1;
        while(bon[a]){
            a = rand()%len +1;
        }
        bon[a] = true;
        b.PB(a);
    }
    n = rand()%700+1;
    for(int i =0; i<n; i++){
        int temp = rand()%10+1;
        a.PB(temp);
    }
}

void printData(){
    cout<<"DATA:\n";
    cout<<m<<"\n";
    for(int i = 0; i<m; i++){
        cout<<b[i]<<"\n";
    }
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<a[i]<<"\n";
    }
}

vector<int> brute(){
    //fidning maxB
    int maxB = -1;
    for(int i = 0; i<m; i++){
        maxB = max(maxB, b[i]);
    }

    vector<bool> bon(maxB+1, false);
    for(int i = 0; i<m; i++){
        bon[b[i]] = true;
    }

    int client = 1;
    vector<int> ans;
    vector<bool> vis(maxB+1, false);
    for(int i = 0; i<n; i++){
        int cur = a[i];
        int count = cur;
        int ind = cur;
        while(count > 0 && ind <= maxB){
            if(!vis[ind]){
                count--;
                vis[ind] = true;
                if(bon[ind]){
                    ans.PB(client);
                }
                client++;
            }
            ind += cur;
        }
        //adjusting for out of range
        if(count > 0){
            client += count;
        }
    }

    return ans;
}

vector<int> solve(){
    //finding maxB
    int maxB = -1;
    for(int i = 0; i<m; i++){
        maxB = max(maxB, b[i]);
    }

    vector<bool> bon(maxB+1, false);
        for(int i = 0; i<m; i++){
        bon[b[i]] = true;
    }

    //client should be unsinged long long int
    int client = 1;
    vector<int> ans;
    vector<bool> vis(maxB+1, false);
    vector<int> last(maxB+1, 0);

    for(int i = 0; i<n; i++){
        int cur = a[i];
        int count = cur;
        //checking for out of range
        if(cur <= maxB){
            //starting from last used
            int ind = last[cur]+cur;
            while(count > 0 && ind <= maxB){
                if(!vis[ind]){
                    count--;
                    vis[ind] = true;
                    if(bon[ind]){
                        ans.PB(client);
                    }
                    client++;
                }
                ind += cur;
            }
            //adjusting for out of range
            if(count > 0){
                client += count;
            }
            last[cur] = ind-cur;
        }else{
            client += cur;
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test =1; test<=100'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        if(ansB.size() != ansS.size()){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB.size()<<"\n";
            for(int i =0 ;i<ansB.size(); i++){
                cout<<ansB[i]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: "<<ansS.size()<<"\n";
            for(int i =0 ;i<ansS.size(); i++){
                cout<<ansS[i]<<" ";
            }
            cout<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}