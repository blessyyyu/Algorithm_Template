# 正则表达式标准库

```cpp
/*
regex_match()：完全匹配一个字符串；
regex_search()：在字符串里查找一个正则匹配；
regex_replace()：正则查找再做替换。

使用了lambda表达式做模板

*/


#include <assert.h>

#include <iostream>
#include <regex>
#include <string>

using std::cout;
using std::endl;
using namespace std::literals::string_literals;  //必须打开名字空间
int main(int argc, char* argv[]) {
    // 生产正则表达式
    auto make_regex = [](const auto& txt) { return std::regex(txt); };
    // 生产正则匹配结果
    auto make_match = []() { return std::smatch(); };


    auto str = "god of war"s;  // 待匹配的字符串

    auto reg = make_regex(R"((\w+)\s(\w+))");  // 原始字符串定义正则表达式
    auto what = make_match();                  // 准备获取匹配的结果

    auto found = regex_search(  // 正则查找，和匹配类似
        str, what, reg);

    assert(found);             // 断言找到匹配
    assert(!what.empty());     // 断言有匹配结果
    assert(what[1] == "god");  // 看第一个子表达式
    assert(what[2] == "of");   // 看第二个子表达式

    auto new_str = regex_replace(  // 正则替换，返回新字符串
        str,                       // 原字符串不改动
        make_regex(R"(\w+$)"),     // 就地生成正则表达式对象
        "peace"                    // 需要指定替换的文字
    );

    cout << new_str << endl;  // 输出god of peace


    return 0;
}
```

![image-20250409224721277](E:\Algorithm_Template\assets\image-20250409224721277.png)
