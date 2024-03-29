## 数位DP问题

> 数位DP的问题很多，有专门的技巧，这里暂时先只提一下数位统计DP里的基本思路

例题：

给定两个整数 a 和 b，求 a 和 b 之间的所有数字中 0∼9的出现次数。

例如，a=1024，b=1032，则 a 和 b 之间共有 9 个数如下：

```
1024 1025 1026 1027 1028 1029 1030 1031 1032
```

其中 `0` 出现 10 次，`1` 出现 10 次，`2` 出现 77次，`3` 出现 3 次等等…

#### 输入格式

输入包含多组测试数据。

每组测试数据占一行，包含两个整数 a 和 b。

当读入一行为 `0 0` 时，表示输入终止，且该行不作处理。

#### 输出格式

每组数据输出一个结果，每个结果占一行。

每个结果包含十个用空格隔开的数字，第一个数字表示 `0` 出现的次数，第二个数字表示 `1` 出现的次数，以此类推。

#### 数据范围

0<a,b<100000000

#### 输入样例：

```
1 10
44 497
346 542
1199 1748
1496 1403
1004 503
1714 190
1317 854
1976 494
1001 1960
0 0
```

#### 输出样例：

```
1 2 1 1 1 1 1 1 1 1
85 185 185 185 190 96 96 96 95 93
40 40 40 93 136 82 40 40 40 40
115 666 215 215 214 205 205 154 105 106
16 113 19 20 114 20 20 19 19 16
107 105 100 101 101 197 200 200 200 200
413 1133 503 503 503 502 502 417 402 412
196 512 186 104 87 93 97 97 142 196
398 1375 398 398 405 499 499 495 488 471
294 1256 296 296 296 296 287 286 286 247
```

#### 思路与解答

要求一堆数字中某个数出现了多少次，首先是分类讨论：

如果要寻找[1, abcdefg]中的数里， 1出现的个数，就得先求1在每一个位置上出现的次数。

比如要找第4位上出现的1的个数有几个，就是要找满足`1 <= xxx1yyy <= abcdefg`的数一共有多少个。设为ans个。

情况1：xxx∈[000,abc-1] , yyy∈[000,999] , ans += abc*1000 (abc 表示 有 abc个数)

> 如果前三位没填满，则后三位就可以随便填 

情况2： xxx == abc, yyy?

if(d<1) yyy不存在 , ans += 0
if(d==1) yyy∈[000,efg] , ans += efg+1
if(d>1) yyy∈[000,999] , ans += 1000

> 如果前三位填满了，后三位怎么填取决于当前这一位



遍历每一位数上的数字，累加起来就是一个数总共出现的数字。

这样就求出来了`[1,n]`的，如果最后想要求解`[l,r]`的，使用前缀和搞定。



但是，在遍历每一位上的数字的时候，也有一些特殊情况：

1. 当`x`在最高位出现的时候，不用考虑前半段：

```
bcdefg∈[00000, bcdefg], ans += bcdefg + 1;
```

2. 当`x`在最后一位上出现时，不用考虑后半段:

```c++
如果 g < x, 那么最后一位上不存在这样的数，ans += 0;
如果 g == x, 那么最后一位上有一个这样的数，ans += 1;
如果 g > x , xxxxxx ∈ [000000, abcdef] , ans += abcdef + 1
```



3. 如果我们需要讨论`0`出现的次数时，0不能放在最高位上，即`xxx ∈ [001, abc - 1]`



```c++
#include<bits/stdc++.h>

using namespace std;

const int N = 1e8 + 10;

int n,a,b;
int num[N];


// 求数组num[] 第r位到第l位的数是多少
int get_num(int l, int r){
    int ans = 0;
    for(int i = l; i >= r ; i-- ){
        ans = ans * 10 + num[i];
    }
    return ans;
}

// 求10^i
int pow10(int i){
    int ans = 1;
    while(i--){
        ans *= 10;
    }
    return ans;
}

int work(int n, int x){
    // 当a = 1时，a-1 = 0，所以还是需要特判一下
    if(n == 0)  return 0;
    int len = 0;
    // 把n的每一位数存储在num[]中,个位存储在下标为1的地方
    while(n){
        num[++len] = n % 10;
        n /= 10;
    }
    int ans = 0;
    if(x != 0){
        // 要寻找的数不为0
        for(int i = len; i > 0; i --){
            // for循环里的i表示第i位，先从高位往低位遍历
            if( i < len)    ans += get_num(len, i + 1) * pow10(i-1);
            // if(i < len) 表示正在讨论的数的位置不在首位上
            if( num[i] == x)    ans += get_num(i-1,1) + 1;
            else if(num[i] > x) ans += pow10(i-1);
            else                ans += 0;
        }
        
    }else{
        // x == 0, i != len；因为0不能放在一个数的最高位上
        for(int i = len - 1; i > 0; i--){
            ans += ( get_num( len, i + 1) - 1 ) * pow10(i-1);
            if( num[i] == x)    ans += get_num(i-1,1) + 1;
            else if(num[i] > x) ans += pow10(i-1);
            else                ans += 0;
        }
        
    }
    return ans;
}


int main(){
    while(scanf("%d%d", &a, &b) && a != 0 && b != 0){
        if( a > b ) swap(a,b);
        for(int i = 0; i <= 9; i ++){
            // 前缀和公式
            int ans = work(b, i) - work(a-1, i);
            printf("%d ", ans);
        }
        printf("\n");
    }
    
    return 0;
}
```

