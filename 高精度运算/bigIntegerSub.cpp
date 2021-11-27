#include<iostream>
#include<string>
#include<vector>

using namespace std;

bool cmp(vector<int> & A, vector<int>& B){
    if(A.size() != B.size())    return A.size() > B.size();
    for(int i = A.size() -1 ; i>=0; i--){
        if(A[i] != B[i])    return A[i] > B[i];
    }
    return true;
}

vector<int> sub(vector<int>&A, vector<int> &B) {
	vector<int> C;
	int i = 0;
	int t = 0;
	for (int i = 0; i < A.size(); i++)
	{
        t = A[i] - t;
        if(i < B.size())    t -= B[i];
		C.push_back( (t+10) % 10);
		if(t < 0)   t = 1;
		else    t = 0;
	}
	//remove the leading 0,but need to remain at least one 0
    while(C.back()==0 && C.size()>1)  C.pop_back();
	return C;
}

int main() {
	string a, b;
	cin >> a >> b;
	vector<int> A, B;

	for (int i = a.size() - 1; i >= 0; i--)    A.push_back(a[i] - '0');      // 9 8 7 6
	for (int i = b.size() - 1; i >= 0; i--)    B.push_back(b[i] - '0');
	vector<int> C;
	if(cmp(A,B)){
	    C = sub(A,B);
	}else{
	    printf("-");
	    C = sub(B,A);
	}
	
	for (int i = C.size() - 1; i >= 0; i--)   printf("%d", C[i]);
}
