# 双指针算法

## 核心性质
双指针算法的核心在于优化思想，将原本$O(n^2)$的时间复杂度的公式优化为O(n);
具体的方法可以是发现某种单调性。



## 思考的模板：

```c++
for(int i=0, j = 0; i <n; i++){
    while( j < n && check(i,j) ) j++;
    //每道题的具体逻辑
}
```



## 经典例题1
输出一段文本当中的每一个单词。

```c++
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
int main(){
    char str[1000];
    //输入一串char型字符
    gets(str);
    for(int i=0,j=0; i< strlen(str); i++){
        j = i;
        while( j < strlen(str) && str[j] != ' ') j++;

        for(int k = i; k < j; k++)  cout<< str[k];

        cout<<endl;

        i = j;
    }
    return 0;
}

```





## 经典例题2

最长不重复子串( 最长连续不重复子序列 ):

```
给定一个长度为 n 的整数序列，请找出最长的不包含重复的数的连续区间，输出它的长度。

输入格式
第一行包含整数 n。

第二行包含 n 个整数（均在 0∼105 范围内），表示整数序列。

输出格式
共一行，包含一个整数，表示最长的不包含重复的数的连续区间的长度。

数据范围
1≤n≤10^5
输入样例：
5
1 2 2 3 5
输出样例：
3
```


```c++
#include <iostream>
#include<algorithm>
using namespace std;

const int N = 1e5 + 10;
// s数组来记录个数
int a[N],s[N];

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0; i< n; i++)
        scanf("%d",&a[i]);
    int res = 0;
    // 双指针，i指针在前，j指针在后，一旦遇到重复的元素，后指针++，并把
    // 记录个数的数组值减一
    for(int i = 0,j = 0; i< n; i++)
    {
        s[a[i]] ++ ;
        while(s[a[i]] > 1){
            j++;
            s[a[j]] --;
        }
        res = max(res, i - j + 1);
    }
    
    printf("%d\n",res);
    
    return 0;
}

```



## 常见问题的分类

* 对于一个序列，用两个指针维持一段区间。
* 对于两个序列，维护某种次序，比如归并排序中合并两个有序序列的操作。





### Leetcode 76 最小覆盖子串

给你一个字符串 `s` 、一个字符串 `t` 。返回 `s` 中涵盖 `t` 所有字符的最小子串。如果 `s` 中不存在涵盖 `t` 所有字符的子串，则返回空字符串 `""` 。

**注意：**

- 对于 `t` 中重复字符，我们寻找的子字符串中该字符数量必须不少于 `t` 中该字符数量。
- 如果 `s` 中存在这样的子串，我们保证它是唯一的答案。

**示例 1：**

```
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
```

**示例 2：**

```
输入：s = "a", t = "a"
输出："a"
```

**示例 3:**

```
输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，因此没有符合条件的子字符串，返回空字符串。
```



**思路与解答：**

找到覆盖字符串t的s中的最小子串，使用双指针算法（`i,j`， `i >= j`）设计一个窗口，这个窗口的长度不断拓展，直到窗口中包含了字符串t中的所有元素。

- 如何判断是否一个窗口中包含了`t`中的所有元素呢？

首先遍历一遍t，维持一个哈希表，得到t中所有字母出现的次数；再维持一个哈希表hs，用来表示字符串s中的窗口里出现字符串t中的元素的个数。



```c++
class Solution {
public:
    string minWindow(string s, string t) {
        // 两个hashtable
        unordered_map<char, int> hs, ht;
        // cnt表示有效字符，即t中的字符，并且个数少于t中要求的个数
        int cnt = 0;
        for(int i = 0; i < t.size(); i ++){
            ht[t[i]] ++;
        }
        string res;
        for(int i =0, j = 0; i < s.size(); i++){
            // i ++ 表示： 窗口的长度 +1
            hs[s[i]]++;
            // if判断是否是有效字符
            if(hs[s[i]] <= ht[s[i]])    cnt ++;
			// 窗口左端边界 ++ 
            while(hs[s[j]] > ht[s[j]])  hs[s[j ++]] --;
            if(cnt == t.size()){
                // i -j + 1 < res.size() 即找到最小的字符串
                if(res.empty() || i - j + 1 < res.size()){
                    res = s.substr(j, i - j + 1);
                }
            }
        }
        return res;
    }
};
```







