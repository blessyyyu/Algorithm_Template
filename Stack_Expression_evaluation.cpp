#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <stack>
#include <cctype>

using namespace std;

unordered_map<char, int> pr = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

stack<int> num;
stack<char> op;

string s;

void eval()
{
    int a = num.top();
    num.pop();
    int b = num.top();
    num.pop();
    char tempOp = op.top();
    op.pop();
    int r = 0;
    if (tempOp == '+')
    {
        r = b + a;
    }
    else if (tempOp == '-')
    {
        r = b - a;
    }
    else if (tempOp == '*')
    {
        r = b * a;
    }
    else
    {
        r = b / a;
    }
    num.push(r);
}

int main()
{
    // 这里的s是表达式
    cin >> s;
    
    // for循环用来将数字和操作符变成两个栈中的元素
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
        {
            int x = 0, j = i;
            while (j < s.size() && isdigit(s[j]))
            {
                x = x * 10 + s[j] - '0';
                j++;
            }
            i = j - 1;
            // x计算完一定要记得放入到num里
            num.push(x);
        }
        else if (s[i] == '(')
        {
            op.push(s[i]);
        }
        else if (s[i] == ')')
        {
            while (op.top() != '(')
                eval();
            op.pop();
        }
        else
        {
            while (op.size() && pr[s[i]] <= pr[op.top()])
            {
				// 先把栈中的高优先级符号的运算先计算了
                eval();
            }
            op.push(s[i]);
        }
    }
    while (op.size())
        eval();
    cout << num.top() << endl;

    return 0;
}
