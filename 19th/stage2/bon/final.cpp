#include<iostream>
#include <vector>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

using ull = unsigned long long int;

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

vector<ull> solve(){
    //finding maxB
    int maxB = -1;
    for(int i = 0; i<m; i++){
        maxB = max(maxB, b[i]);
    }

    vector<bool> bon(maxB+1, false);
        for(int i = 0; i<m; i++){
        bon[b[i]] = true;
    }

    ull client = 1;
    vector<ull> ans;
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

    getData();

    vector<ull> ansS = solve();
    cout<<ansS.size()<<"\n";
    for(int i =0 ;i<ansS.size(); i++){
        cout<<ansS[i]<<"\n";
    }

    return 0;
}