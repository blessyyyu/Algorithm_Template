#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<int> m_add(vector<int>&A, vector<int> &B) {
	vector<int> C;
	int i = 0;
	int t = 0;
	for (int i = 0; i < A.size()|| i<B.size(); i++)
	{
		if (i < A.size())	t += A[i];
		if (i < B.size())	t += B[i];
		C.push_back(t % 10);
		t /= 10;
	}
	//Attention, you need to consider the t = 1 in the headfirst.
	if (t != 0)	C.push_back(1);
	return C;
}

int main() {
	string a, b;
	cin >> a >> b;
	vector<int> A, B;
	// 这里倒着存储的目的是：加法是先从个位开始加，如果最高位还有进位，那么需要在数组后面增加一位
	// 而数组在最后增加位数是比在开始增加位数方便的。

	for (int i = a.size() - 1; i >= 0; i--)    A.push_back(a[i] - '0');      // 9 8 7 6
	for (int i = b.size() - 1; i >= 0; i--)    B.push_back(b[i] - '0');
	
	auto C = m_add(A, B);

	for (int i = C.size() - 1; i >= 0; i--)   printf("%d", C[i]);
}
