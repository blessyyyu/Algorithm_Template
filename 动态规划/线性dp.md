# 线性DP问题

线性DP问题，往往指那些，存在一个模糊的从前往后（从后往前），从小到大的某个顺序进行递推的DP问题。

### 例题1：数字三角形

给定一个如下图所示的数字三角形，从顶部出发，在每一结点可以选择移动至其左下方的结点或移动至其右下方的结点，一直走到底层，要求找出一条路径，使路径上的数字的和最大。

```
        7
      3   8
    8   1   0
  2   7   4   4
4   5   2   6   5
```

#### 输入格式

第一行包含整数 n，表示数字三角形的层数。

接下来 n 行，每行包含若干整数，其中第 i 行表示数字三角形第 i 层包含的整数。

#### 输出格式

输出一个整数，表示最大的路径数字和。

#### 数据范围

1≤n≤500
−10000≤三角形中的整数≤10000

#### 输入样例：

```
5
7
3 8
8 1 0 
2 7 4 4
4 5 2 6 5
```

#### 输出样例：

```
30
```



#### 解答和思路：

* 状态的表示：`f[i][j]`，其中`i`,`j`表示走到第i层，第j个数字为止的所有路径的集合；
  * 属性：max属性，路径和的最大值。
* 状态的计算：

`f[i][j] = max(f[i-1][j-1] , f[i-1][j]) + t[i][j]`

要考虑下一层的很多边界问题，如三角形的最左边和最右边的路径，只有一条。

```c++
#include<bits/stdc++.h>

using namespace std;

const int N = 510;

int t[N][N];

int f[N][N];
int n;

int main(){
    cin >> n;
    
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= i; j++){
            cin >> t[i][j];
        }
    }
    // 初始边界
    f[1][1] = t[1][1];
    
    for(int i = 2; i <= n ; i ++){
        for(int j = 1; j <= i; j++){
            if( j == 1 ){
                f[i][j] = f[i-1][j] + t[i][j];
                continue;
            }   
            if( j == i){
                f[i][j] = f[i-1][j-1] + t[i][j];
                continue;
            } 
            f[i][j] = max(f[i-1][j-1] , f[i-1][j]) + t[i][j];
        }
    }
    // 用来debug的    
    // for(int i = 1; i <= n; i ++){
    //     for(int j = 1; j <= i; j ++){
    //         cout << f[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    
    int res = -1e9;
    for(int i = 1; i <= n; i++)
        res = max(res, f[n][i]);

    cout << res << endl;
    return 0;
}
```

使用一维滚动数组，减小空间复杂度；


```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 510;
int t[N][N];
int f[N];
int n;

int main(){
    cin >> n;
    
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= i; j++){
            cin >> t[i][j];
        }
    }
    
    f[1] = t[1][1];
    
    for(int i = 2; i <= n; i ++){
        for(int j = i; j >= 1; j --){
            if( j == 1 ){
                f[j] = f[j] + t[i][j];
                continue;
            }
            if( j == i){
                f[j] = f[j-1] + t[i][j];
                continue;
            } 
            f[j] = max(f[j-1] , f[j]) + t[i][j];
        }
    }
        
    
    int res = -1e9;
    for(int i = 1; i <= n; i++)
        res = max(res, f[i]);
            
    cout << res << endl;
    return 0;
}
```



**倒着求路径，缩短了代码行数，少了边界的特判。这种思路非常妙！**

```c++
#include<bits/stdc++.h>
using namespace std;

const int N=510;
int f[N][N];
int n;

int main(){
    cin>>n;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=i; j++){
            cin>>f[i][j];
        }
    }

    for(int i=n; i>=1; i--){
        for(int j=i; j>=1; j--){
            f[i][j]=max(f[i+1][j],f[i+1][j+1])+f[i][j];
        }
    }
    cout<<f[1][1]<<endl;
    return 0;
}
```



### 数字三角形拓展题：传纸条

> [传纸条](https://www.acwing.com/problem/content/277/)

**题意分析：**

找到两条路径，分别都从矩阵的左上角`(1, 1)`走到右下角`(m, n)`，沿途不能交叉，走过的路径上的权重和要最大。

DP问题一定要考虑好**状态表示**和**状态计算**；一个好的状态表示应该满足：1. 任何一个情形都能被你设置的状态表示出来； 2. 状态表示能够依次推理，得到最终的状态。

而状态计算的推理，通常要考虑最后一步，按照最后一个动作进行分类。

一条路径，通常我们的状态设置为`f[i][j]`， 表示到达点`(i, j)`的任意一条路径的集合。而两条路径，可以很顺利的想到`f[x1][y1][x2][y2]`， 表示第一条路径从起点走到`[x1][y1]`， 第二条路径从起点走到`[x2][y2]`； 这样当然是可行的；只是最后时间复杂度高一些： 按照两条路径的最后一步进行划分，第一条路径有向下、向右两种选择，第二条路径有向下、向右两种选择；组合起来就是四种。所以时间复杂度就是$O(N*N*N*N*4)$;

- 状态表示：

两条路径不能相交的，且起点终点相同的问题；通常可以这么设置状态`f[k][x1][x2]`;  `k`表示一条路径中横纵坐标之和。那么第一条路径的点的坐标表示为`[x1][k-x1]`；第二条路径的点的坐标表示为`[x2][k-x2]`.  这里遍历的`x1,x2`的时候需要给一个范围： ` n>= x1 >= 1,   m >= k-x1 >= 1 `. 

- 属性：max
- 状态计算： 按照最后一步分为“右右”， “右下”， “下右”， “下下”四种。右右的情形，倒数第二步为: `(x1, k - x1 - 1) ---> (x1, k - x1)`, `(x2, k - x2 - 1) ---> (x2, k - x2)`； 所以倒数第二个状态为`f[k-1][x1][x2]`。
  -  同理可得，右下的倒数第二个状态： `f[k-1][x1][x2-1]`。 
  - 下右的倒数第二个状态：`f[k-1][x1-1][x2]`.
  - 下下的倒数第二个状态: `f[k-1][x1-1][x2-1]`
- 状态计算要加上最后一步所在格子的权值，并且要判断两者是否重合，只需要`x1 != x2`即可。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 55;

int w[N][N];
// 注意这里第一维要乘以2
int f[N * 2][N][N];
int n, m;

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            cin >> w[i][j];
        }
    }
    
    for(int k = 2; k <= n + m; k ++){
        for(int i = max(1, k - m); i <= n && i < k; i ++){
            for(int j = max(1, k - m); j <= n && j < k; j ++){
                for(int a = 0; a <= 1; a ++){
                    for(int b = 0; b <= 1; b ++){
                        // 先加上[i][k - i];
                        int t = w[i][k - i];
                        // 如果两个点不重合; 或者k == 2(即都位于点(1,1)处或者(n, m))
                        if (i != j || k == 2 || k == n + m){
                            // 加上另一条路径上的点权值
                            t += w[j][k - j];
                            f[k][i][j] = max(f[k][i][j], f[k - 1][i - a][j - b] + t);
                        }
                    }
                }
            }
        }
    }
    
    cout << f[n+m][n][n] << endl;
    return 0;
}
```







### 例题3 ： 最长公共子序列

给定两个长度分别为 N 和 M 的字符串 A 和 B，求既是 A 的子序列又是 B 的子序列的字符串长度最长是多少。

#### 输入格式

第一行包含两个整数 N 和 M。

第二行包含一个长度为 N 的字符串，表示字符串 A。

第三行包含一个长度为 M 的字符串，表示字符串 B。

字符串均由小写字母构成。

#### 输出格式

输出一个整数，表示最大长度。

#### 数据范围

1≤N,M≤1000

#### 输入样例：

```
4 5
acbd
abedc
```

#### 输出样例：

```
3
```



#### 思路和解答：

解决DP问题的通用思路：

- 状态表示：`f[i][j]`, `i`表示A字符串以下标`i`结尾， `j`表示B字符串以下标`j`结尾； 属性是max，即所有以`i`下标为结尾的A串与，以`j`下标为结尾的B串的公共子序列的长度的最大值。
- 状态计算：画图

![image-20211103230832419](线性dp.assets/image-20211103230832419.png)

为什么当`a[i] != b[j]` 时， `f[i][j] = max(f[i-1][j],  f[i][j-1] )`? 

![image-20211103230928187](线性dp.assets/image-20211103230928187.png)

比如我们看上面这个序列，将最后的结果分解成子问题，a串最后一个字符`d` != `c`, 那么只有可能出现两种情况：1. b串最后一个字符`c`不在最长公共子序列（答案序列）中，将其排除； 2. a串最后一个字符`d`不在最长公共子序列中，将其排除。 

即状态1只能分成状态2，或者状态3；将其取最大值即可！



```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

char a[N], b[N];
int n,m;
int f[N][N];

int main(){
    cin >> n >> m >> a + 1 >> b + 1;
    
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j++){
            if(a[i] == b[j])    f[i][j] = f[i-1][j-1] + 1;
            else{
                f[i][j] = max(f[i-1][j], f[i][j-1]);
            }
        }
    }
    cout << f[n][m]<<endl;
    
    return 0;
}
```



### 例题4：最少编辑距离

给定两个字符串 A 和 B，现在要将 A 经过若干操作变为 B，可进行的操作有：

1. 删除–将字符串 A 中的某个字符删除。
2. 插入–在字符串 A 的某个位置插入某个字符。
3. 替换–将字符串 A 中的某个字符替换为另一个字符。

现在请你求出，将 A 变为 B 至少需要进行多少次操作。

#### 输入格式

第一行包含整数 n，表示字符串 A 的长度。

第二行包含一个长度为 n 的字符串 A。

第三行包含整数 m，表示字符串 B 的长度。

第四行包含一个长度为 m 的字符串 B。

字符串中均只包含大写字母。

#### 输出格式

输出一个整数，表示最少操作次数。

#### 数据范围

1≤n,m≤1000

#### 输入样例：

```
10 
AGTCTGACGC
11 
AGTAAGTAGGC
```

#### 输出样例：

```
4
```



#### 思路与解答：

- 状态表示：`f[i][j]`表示的集合是，所有将a[1] ~ a[i] 变成 b[1] ~ b[j] 的所有操作方式。
  - 属性： min, 即所有操作方式中操作次数的最小值。（注意： 动态规划之所以比暴搜快，是因为它将很多情况汇聚成了一种表示方式）
- 状态计算（画图）：我们往往从大的问题往前找，这样的思路是分解成小的问题

因为所有的操作就三种，所以可以将状态划分成三部分：

![image-20211104115209788](线性dp.assets/image-20211104115209788.png)





```c++
#include<bits/stdc++.h>

using namespace std;

const int N = 1010;
char a[N],b[N];
int f[N][N];
int n,m;
int main(){
    cin >> n >> a + 1 >> m >> b + 1;
    
    // 边界初始化
    // 如果想让a串从0开始与b串相同，需要做i次添加操作
    for(int i = 0; i <=m; i ++) f[0][i] = i;
    
    // 如果想让a串从n开始与b串相同，需要做i次删除操作
    for(int i = 0; i <= n; i ++)    f[i][0] = i;
    
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            // 删除、增加两项操作中的最小值
            f[i][j] = min(f[i-1][j] + 1, f[i][j-1] + 1);
            // 如果最后a[i] == b[j]，那么不需要替换操作
            if(a[i] == b[j]){
                f[i][j] = min(f[i][j], f[i-1][j-1]);
            }else{
                f[i][j] = min( f[i][j], f[i-1][j-1] + 1);
            }
        }
    }
    
    printf("%d\n", f[n][m]);
    
    
    return 0;
    
}

// 更加简洁的写法
// leetcode 72 编辑距离
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        word1 = " " + word1;
        word2 = " " + word2;
        vector<vector<int>> f = vector<vector<int>>(n + 1, vector<int>(m + 1));
        for(int i = 1; i <= n; i ++)    f[i][0] = i;
        for(int j = 1; j <= m; j ++)    f[0][j] = j;
        
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
                if(word1[i] == word2[j])    f[i][j] = f[i-1][j-1];
                else{
                    // 第一项是修改，第二项是删除word1[i], 第三项是增加word2[j]
                    f[i][j] =  min(f[i-1][j-1], min(f[i-1][j] , f[i][j-1]) ) + 1;
                }
            }
        }
        return f[n][m];
    }
};
```



编辑距离的应用：

```c++
#include<bits/stdc++.h>

using namespace std;

const int N = 15, M = 1010;

int n, m;
int f[N][N];
char str[M][N];

int edit_distance(char a[], char b[])
{
    int la = strlen(a + 1), lb = strlen(b + 1);

    for (int i = 0; i <= lb; i ++ ) f[0][i] = i;
    for (int i = 0; i <= la; i ++ ) f[i][0] = i;

    for (int i = 1; i <= la; i ++ )
        for (int j = 1; j <= lb; j ++ )
        {
            f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
            if(a[i] == b[j])
                f[i][j] = min(f[i][j], f[i-1][j-1]);
            else
                f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
        }

    return f[la][lb];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ ) scanf("%s", str[i] + 1);

    while (m -- )
    {
        char s[N];
        int limit;
        scanf("%s%d", s + 1, &limit);

        int res = 0;
        for (int i = 0; i < n; i ++ )
            if (edit_distance(str[i], s) <= limit)
                res ++ ;

        printf("%d\n", res);
    }

    return 0;
}

```





### Leetcode96 不同的二叉搜索树

给你一个整数 `n` ，求恰由 `n` 个节点组成且节点值从 `1` 到 `n` 互不相同的 **二叉搜索树** 有多少种？返回满足题意的二叉搜索树的种数。

**样例：**

```
输入：3
输出：5
解释：
给定 n = 3, 共有5种不同的二叉搜索树，如下所示：

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```

- `1 <= n <= 19`

#### 思路与解答：

可以注意到，`1-10`数字组成的二叉搜索树的种数实际上和`2-11`数字组成的二叉搜索树的种数是一致的。所以实际上二叉搜索树的个数并不需要考虑树中节点的数值具体是多少，而是只需要考虑结点数值之间的相对关系就可以了。

- 状态集合：`f[i]`表示长度为`i`的区间所能表示的二叉搜索树的所有集合。
  - 属性是count。
- 状态计算：

![image-20211122210449252](线性dp.assets/image-20211122210449252.png)

当在区间`[L, R]`里选择结点K作为树的根节点时，`[L, K-1]`区间都可以作为根节点的左子树，`[K+1 , R]` 区间都可以作为根节点的右子树。那么以K作为根节点的所有二叉搜索树 的种数 = 左边区间的所有种数 $\times$ 右边区间的所有种数

```c++

class Solution {
public:
    int numTrees(int n) {
        vector<int> f(n + 1, 0);
        // 初始化边界
        f[0] = 1;
        for(int i = 1; i <= n; i++){
            // 第一层循环，枚举区间长度
            for(int j = 1; j <= i; j++){
                // 第二层循环，枚举位于区间内，以j结点为根节点的所有二叉搜索树的种数
                f[i] += f[j - 1] * f[i - j]; 
            }
        }
        return f[n];
    }
};
```



### Leetcode 1866 

[1866. 恰有 K 根木棍可以看到的排列数目 - 力扣（LeetCode） (leetcode-cn.com)](https://leetcode-cn.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/)

有 n 根长度互不相同的木棍，长度为从 1 到 n 的整数。请你将这些木棍排成一排，并满足从左侧 可以看到 恰好 k 根木棍。从左侧 可以看到 木棍的前提是这个木棍的 **左侧** 不存在比它 **更长的** 木棍。

例如，如果木棍排列为 [1,3,2,5,4] ，那么从左侧可以看到的就是长度分别为 1、3 、5 的木棍。
给你 n 和 k ，返回符合题目要求的排列 数目 。由于答案可能很大，请返回对 $10^9 + 7$ 取余 的结果。

```
输入：n = 3, k = 2
输出：3
解释：[1,3,2], [2,3,1] 和 [2,1,3] 是仅有的能满足恰好 2 根木棍可以看到的排列。


输入：n = 5, k = 5
输出：1
解释：[1,2,3,4,5] 是唯一一种能满足全部 5 根木棍可以看到的排列。
```





#### 思路与解答

- 状态表示：
  - 用`f[n][k]`来表示有n根木棍，恰好可以看到k根木棍的所有方案。
  - 属性： count，方案数。
- 状态计算：

从最后一根开始思考：

![image-20211129224051593](线性dp.assets/image-20211129224051593.png)

```c++
typedef long long LL;
const int N = 1010, mod = 1e9 + 7;
class Solution {
public:
    int f[N][N];
    int rearrangeSticks(int n, int k) {
        memset(f, 0 , sizeof f);
        for(int i = 1; i <= n; i ++)    f[i][i] = 1;

        for(int i = 2; i <= n; i ++)
            for(int j = 1; j <= i - 1; j ++)
                f[i][j] = (f[i-1][j-1] + (LL)(i - 1) * f[i-1][j] % mod) % mod;

        return f[n][k];
    }
};
```



### Leetcode 91 解码方法

> https://leetcode-cn.com/problems/decode-ways/submissions/

一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：

'A' -> 1
'B' -> 2
...
'Z' -> 26
要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。例如，"11106" 可以映射为：

"AAJF" ，将消息分组为 (1 1 10 6)
"KJF" ，将消息分组为 (11 10 6)
注意，消息不能分组为  (1 11 06) ，因为 "06" 不能映射为 "F" ，这是由于 "6" 和 "06" 在映射中并不等价。

给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数 。

题目数据保证答案肯定是一个 32 位 的整数。

```
示例 1：

输入：s = "12"
输出：2
解释：它可以解码为 "AB"（1 2）或者 "L"（12）。
```



#### 思路

经典的线性DP问题；有些类似于跳台阶问题，需要额外做一些判断。

- 状态集合： `f[i] = x`表示所有前`i`个字符里，所有解码的方案；
  - 属性：count属性。
- 状态计算：

边界条件f[0] = 1, 当一个字符都没有的时候，只有一种解码方法。

而当最后一个字符可以单独解码的时候，`f[i] = f[i-1]`;

最后两个字符合起来可以解码：`f[i] = f[i-2]`；

上述两种情况都可以时，`f[i] = f[i-1] + f[i-2]`;

```c++
class Solution {
public:
    int numDecodings(string s) {
        // 先求长度n
        int n = s.size();
        // 再用首字符加上，使得index保持一致；
        s = ' ' + s;
        vector<int> f(n + 1);
        f[0] = 1;
        for(int i = 1; i <= n; i ++){
            if(s[i] >= '1' && s[i] <= '9')  f[i] += f[i-1];
            if(i > 1){
                // 先成为一个整数，再来判断范围，可以节省很多代码
                int t = (s[i-1] - '0') * 10 + s[i] - '0';
                if(t >= 10 && t <= 26){
                    f[i] += f[i-2];
                }
            }
        }
        return f[n];
    }
};
```



### Leetcode 53 + 152 最大子数组和 + 最大乘积子数组
> [最大乘积子数组](https://leetcode.cn/problems/maximum-product-subarray/)
> [最大子数组和](https://leetcode.cn/problems/maximum-subarray/)

首先来看**最大子数组和**的问题：
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组是数组中的一个连续部分。
```
样例输入：
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 
```

**思路**： 如果采用暴力枚举的做法，枚举连续子数组的两个端点，求得其中的和，再取最大值。时间复杂度是O(n^3), 如果采用前缀和优化，时间复杂度可以为O(n^2). 
但是使用动态规划的思想， 时间复杂度可以优化为O(n)：
- 状态表示: `f[i] = x`，`f[i]`为以下标i作为结束的所有序列集合。`x`表示所有集合中的和的最大值。
- 属性： max。
- 状态计算： `f[i] = max(f[i-1] + nums[i], nums[i])`。

解答：
```cpp
const int N = 1e5 + 10;
class Solution {
public:
    int f[N];
    int maxSubArray(vector<int>& nums) {
        memset(f , 0, sizeof f);
        int len = nums.size();
        f[0] = nums[0];
        int res = f[0];
        for(int i = 1; i < len; i ++){
            f[i] = max(f[i-1] + nums[i], nums[i]);
            res = max(f[i], res);
        }
        return res;
    }
};
```

**最大子数组积：**
给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

测试用例的答案是一个 32-位 整数。

子数组 是数组的连续子序列。

```
输入: nums = [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。

输入: nums = [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
```

**受上一题的启发，也可以用动态规划的思想**
同样设`f[i] = x`为以下标i结束的所有子序列乘积的最大值，但是与之前不同的是，乘法会出现负负得正的情况，即`f[i-1] * nums[i]`， 如果nums[i] < 0， 那么`f[i-1]`越小，最后的乘积越大。
如果nums[i] >0, 那么还是f[i-1]越大越好。

所以需要另外引进一个数组`g[i] = y `，表示以下标i结束的所有子序列乘积的最小值。这样从前往后枚举数组中的每一个数，都要判断一下nums[i]与0的大小关系，然后选择与`g[] or f[]`相乘。
为了更方便写代码，可以直接和`g[i-1], f[i-1]`都相乘取最大值最小值来更新`f[], g[]`即可。
又因为只用到了`f[i-1], g[i-1]`, 所以可以用滚动数组的思想，压缩空间。
太强了！

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int f = nums[0], g = nums[0];
        int res = nums[0];
        for (int i = 1; i < n; i ++) {
            int a = nums[i], fa = f * a, ga = g * a;
            f = max(nums[i], max(fa, ga));
            g = min(nums[i], min(fa, ga));
            res = max(res, f);
        }
        return res;
    }
};
```



