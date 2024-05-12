#include<iostream>
#include <vector>

using namespace std;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>

int n, k;
vector<int> c;
int m,l;
vector<int> x;
vector<int> y;

void getData(){
    cin>>n>>k;
    for(int i =0 ;i<n; i++){
        int temp;
        cin>>temp;
        c.PB(temp);
    }
    cin>>m>>l;
    for(int i = 0; i<m; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0 ; i<l; i++){
        int temp;
        cin>>temp;
        y.PB(temp);
    }
}

vector<int> solve(){
    int left = 1;
    for(int i = 0; i<m-1; i++){
        if(c[left] != x[i]){
            left++;
            i--;
        }
        if(left >= m){
            break;
        }
    }
    int right = n-2;
    for(int i = 0; i<l-1; i++){
        if(c[right] != y[i]){
            right--;
            i--;
        }
        if(right < 0){
            break;
        }
    }
    vector<int> ans;
    for(int i = left; i<=right; i++){
        if(c[i] == x[m-1]){
            ans.PB(i+1);
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<int> ansS = solve();
    cout<<ansS.size()<<"\n";
    for(int i = 0; i<ansS.size(); i++){
        cout<<ansS[i]<<" ";
    }

    return 0;
}