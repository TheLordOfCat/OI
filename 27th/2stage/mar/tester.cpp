#include <iostream>
#include <vector>
#include <string>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, m;
vector<int> digits;
vector<int> querys;

void getData(){
    cin>>n>>m;
    for(int i =0 ; i<n; i++){
        char c;
        cin>>c;
        digits.PB(c-'0');
    }
    for(int i =0 ; i<m; i++){
        int temp;
        cin>>temp;
        querys.PB(temp);
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    m = rand()%5+1;
    for(int i =0 ; i<n; i++){
        int temp = rand()%2;
        digits.PB(temp);
    }
    for(int i =0 ; i<m; i++){
        int temp = rand()%n+1;
        querys.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<digits.size(); i++){
        cout<<digits[i];
    }
    cout<<"\n";
    for(int i = 0; i<querys.size(); i++){
        cout<<querys[i]<<"\n";
    }
}

int qBrute(vector<int> d){
    string s;
    for(int i = 0; i<d.size(); i++){
        if(d[i] == 0){
            s += '0';
        }else{
            s += '1';
        }
    }

    int totalSize = 1<<d.size();
    int len = 0;
    for(int i = 0; i<totalSize; i++){
        if(i > (1<<(len+1))){
            len++;
        }
        string f;
        for(int j = 0; j<len; j++){
            if(i & 1<<j){
                f += '1';
            }else{
                f += '0';
            }
        }
        
        auto itr = s.find(f);
        if(itr == s.npos){
            return len;
        }
    }

    return -1;
}

vector<int> brute(){
    vector<int> ans;

    vector<int> digAlt = digits;
    ans.PB(qBrute(digAlt));
    for(int i = 0; i<querys.size(); i++){
        digAlt[querys[i]-1] =  (digAlt[querys[i]-1]+1)%2;
        int temp = qBrute(digAlt);
        ans.PB(temp);
    }

    return ans;
}

int qSolve(int v, vector<int>& d,  vector<vector<int>>& dic){
    int R = 20;
    for(int i = min(v-R, 0); i<=v; i++){
        ll num = 0;
        for(int j = i; j<i+R && j<n; j++){
            if(d[j] == 1){
                num ^= (1<<(j-i));
            }
            if(j >= v) dic[j-i+1][num]--;
        }
    }

    d[v] =  (d[v]+1)%2;
    for(int i = min(v-R, 0); i<=v; i++){
        ll num = 0;
        for(int j = i; j<i+R && j<n; j++){
            if(d[j] == 1){
                num ^= (1<<(j-i));
            }
            if(j >= v) dic[j-i+1][num]++;
        }
    }

    for(int l = 1; l<R; l++){
        int maxSize = (1<<l);
        int minSize = (1<<(l-1));
        if(l == 1) minSize = 0;
        
        bool ok = true;

        for(int i = minSize; i<maxSize; i++){
            if(dic[l][i] == 0){
                ok = false;
                break;
            }
        }

        if(!ok){
            return l;
        } 
    }

    return -1;
}

vector<int> solve(){
    vector<int> ans;
    int R = 20;

    vector<int> digAlt = digits;
    vector<vector<int>> dic(R+1, vector<int>((1<<R)+1, 0));

    //initial traversal
    for(int i = 0; i<n; i++){
        ll num = 0;
        for(int j = i; j<i+R && j<n; j++){
            if(digAlt[j] == 1){
                num ^= (1<<(j-i));
            }
            dic[j-i+1][num]++;
        }
    }

    for(int l = 1; l<R; l++){
        int maxSize = (1<<l);
        int minSize = (1<<(l-1));
        if(l == 1) minSize = 0;
        
        bool ok = true;

        for(int i = minSize; i<maxSize; i++){
            if(dic[l][i] == 0){
                ok = false;
                break;
            }
        }

        if(!ok){
            ans.PB(l);
        } 
    }

    if(ans.size() == 0) ans.PB(-1);

    //proces query
    for(int i = 0; i<querys.size(); i++){
        int temp = qSolve(querys[i]-1, digAlt, dic);
        ans.PB(temp);
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
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERORR\n";
                cout<<"BRUTE: ";
                for(int j =0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j =0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}