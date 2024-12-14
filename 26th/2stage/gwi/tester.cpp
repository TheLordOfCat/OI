#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF =  9'000'000'000'000'000'000;
const ull ullINF =  18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PIV pair<int,vector<int>>
#define PLLV pair<ll,vector<int>>
#define PULLV pair<ull,vector<int>>
#define PB push_back

int n, s;
vector<PII> opsCost;

void getData(){
    cin>>n>>s;
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        opsCost.PB(MP(a,b));
    }
}

void getRandom(){
    opsCost.clear();

    srand(time(0));

    n = rand()%10+1;
    s = rand()%n+1;
    for(int i = 0; i<n-1; i++){
        int a, b;
        a = rand()%10+1;
        b = rand()%10+1;
        opsCost.PB(MP(a,b));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<s<<"\n";
    for(int i = 0; i<opsCost.size(); i++){
        cout<<opsCost[i].first<<" "<<opsCost[i].second<<"\n";
    }
}

bool getMovesBrute(PIV& ans, bool& firstOps, PII con, deque<int>& Q){
    if(firstOps){
        if(con.first == 0){
            if(s-1 < con.second){
                return false;
            }
        }else{
            if(n-s < con.second){
                return false;
            }
        }

        vector<int> moves;
        if(con.first == 0){
            for(int i =0; i< con.second; i++){
                moves.PB(Q.front());
                Q.pop_front();
            }
        }else{
            for(int i =0; i< con.second; i++){
                moves.PB(Q.back());
                Q.pop_back();
            }
        }

        while(moves.size() > 0){
            ans.second.PB(moves.back());
            moves.pop_back();
        }
        firstOps = false;
    }else{
        vector<int> moves;
        if(con.first == 0){
            for(int i =0; i< con.second; i++){
                if(Q.front() != s){
                    moves.PB(Q.front());
                }else{
                    i--;
                }
                Q.pop_front();
            }
        }else{
            for(int i =0; i< con.second; i++){
                if(Q.back() != s){
                    moves.PB(Q.back());
                }else{
                    i--;
                }
                Q.pop_back();
            }
        }

        while(moves.size() > 0){
            ans.second.PB(moves.back());
            moves.pop_back();
        }
    }

    return true;
}

PIV checkBrute(vector<int> ops){
    PIV ans = MP(0, vector<int>());
    ans.second.PB(s);
    deque<int> Q;
    for(int i = 1; i<=n; i++){
        Q.PB(i);
    }

    //get the moves
    bool ok = true;
    bool firstOps = true;
    PII con = MP(ops.front(),1);
    for(int i = 1; i<ops.size(); i++){
        if(con.first == ops[i]){
            con.second++;
        }else{
            ok = getMovesBrute(ans, firstOps, con, Q);
            con = MP(ops[i],1);
        }
    }
    ok = getMovesBrute(ans, firstOps, con, Q);

    if(!ok){
        return MP(INF,vector<int>());
    }

    //get the value
    for(int i =0 ; i<ops.size(); i++){
        if(ops[i] == 0){
            ans.first += opsCost[i].first;
        }else{
            ans.first += opsCost[i].second;
        }
    }

    return ans;
}

PIV brute(){
    PIV ans = MP(INF, vector<int>());

    int totalComb = 1<<(n-1);
    for(int i = 0; i<totalComb; i++){
        vector<int> ops;
        for(int j = 0;j <n-1;j ++){
            if(i&(1<<j)){
                ops.PB(0);
            }else{
                ops.PB(1);
            }
        }
        PIV temp = checkBrute(ops);
        if(temp.first < ans.first){
            ans = temp;
        }
    }

    return ans;
}

PULLV solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<"\n";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }

        PIV ansB = brute();
        PULLV ansS = solve();
        if(ansB.first != ansS.first){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n"<<ansB.first<<"\n";
            for(int i = 0; i<ansB.second.size(); i++){
                cout<<ansB.second[i]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: \n"<<ansS.first<<"\n";
            for(int i = 0; i<ansS.second.size(); i++){
                cout<<ansS.second[i]<<" ";
            }
            cout<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}