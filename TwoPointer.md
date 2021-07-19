# 双指针算法

## 核心性质
双指针算法的核心在于优化思想，将原本$O(n^2)$的时间复杂度的公式优化为O(n);
具体的方法可以是发现某种单调性。

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
int a[N],s[N];


int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0; i< n; i++)
        scanf("%d",&a[i]);

    
    int res = 0;
    for(int i = 0,j = 0; i< n; i++)
    {
        s[a[i]] ++ ;
        while(s[a[i]] > 1){
            s[a[j]] --;
            j++;
        }
        res = max(res, i - j + 1);
    }
    
    printf("%d\n",res);
    
    return 0;
}

```

思考的模板：

```c++

for(int i=0, j = 0; i <n; i++){
    while( j < n && check(i,j)) j++;
    //每道题的具体逻辑
}

```



### 常见问题的分类

* 对于一个序列，用两个指针维持一段区间。
* 对于两个序列，维护某种次序，比如归并排序中合并两个有序序列的操作。