# 正则表达式标准库

```cpp
#include <bits/stdc++.h>

using namespace std;
void test();
void test2();
void test_replace();


int main(){
    test();
    test2();
    test_replace();
    return 0;
}

void test()
{
    // 只能搜索在test_str中出现的第一个符合的单词
    // 查找不是在字符c之后的ei组合存在的单词
	string pattern("[^c]ei");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	regex r(pattern);
	smatch results;
	string test_str("receipt reinforce theif receive");
	if (regex_search(test_str, results, r))
		cout << results.str() << endl;//reinforce
}

void test2()
{
    // sregex的方法可以检查出所有匹配的部分
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    smatch result;
    string test_str("receipt reinforce theif receive");
    for (sregex_iterator it(test_str.begin(), test_str.end(), r), end_it; it != end_it; it ++ ){
        cout << it -> str() << endl;
    }
    // reinforce theif
}


void test_replace()
{
    // regex_replace 将正则表达式匹配出来的部分全部替换成自定义的字符串
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    smatch result;
    string test_str("receipt reinforce theif receive");
    string to_replace("abcabc");
    string ret = regex_replace(test_str, r, to_replace);
    cout << ret << endl;  //receipt abcabc abcabc receive
}
```

