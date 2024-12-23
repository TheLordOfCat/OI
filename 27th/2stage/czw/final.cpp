#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>
#include <tuple>
#include <string>
#include <map>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back
#define MT make_tuple

int m;
vector<int> code;

void getData(){
    code.clear();

    cin>>m;

    string temp;
    cin>>temp;
    for(int i =0 ; i<temp.size(); i++){
        code.PB(temp[i]-'0');
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<m<<"\n";
    for(int i = 0; i<code.size(); i++){
        cout<<code[i];
    }
    cout<<"\n";
}

PII solve(){
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    PII ansS = solve();
    cout<<ansS.first<<"\n"<<ansS.second<<"\n";

    return 0;
}