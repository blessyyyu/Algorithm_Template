#include <bits/stdc++.h>

using namespace std;

vector<int> A;
int b;
string a;
vector<int> m_div(vector<int> & A, int b, int & r){
    vector<int> res;
    r = 0;
    for(int i = A.size() - 1; i >= 0; i --){
        r = r * 10 + A[i];
        res.push_back(r / b);
        r = r % b;
    }
    reverse(res.begin(), res.end());
    while(res.back() == 0 && res.size() > 1)    res.pop_back();
    return res;               
}


int main(){
    cin >> a >> b;
    for(int i = a.size() - 1; i >= 0; i --){
        A.push_back(a[i] - '0');    
    }
    
    vector<int> result;
    int remainder;
    auto C = m_div(A, b, remainder);
    
    for(int i = C.size() - 1; i >= 0; i --)  cout << C[i];
    // attention this.
    cout << endl <<  remainder << endl;;
    
    return 0;

}