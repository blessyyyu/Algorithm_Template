### Leetcode 416 分割等和子集

[416. 分割等和子集 - 力扣（LeetCode） (leetcode-cn.com)](https://leetcode-cn.com/problems/partition-equal-subset-sum/)

给你一个 **只包含正整数** 的 **非空** 数组 `nums` 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

**示例 1：**

```
输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11] 。
```



**示例 2：**

```
输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。
```



思路与解答：

0-1背包问题的应用题。实际上就是遍历一遍`nums`数组，得到数组和`sum`，如果这个数组可以分割成两个元素和相等的子集，那么一定有一部分可以凑成sum / 2; **这样相当于背包的体积是sum / 2**, 选择物品 ----> 选择数字。

- 状态表示：使用二维数组`f[i][j]` 表示所有从`nums`里下标[0 ~ i ]中挑选数字，`j`表示挑选出的数字和是`j`.
  - 属性（即`f[i][j]`的值表示的含义）： `f[i][j] = true`， 则从`[0~i]`中恰好可以挑选出和为`j`的数字。
- 状态计算：分为两种情况，选`nums[i]`和不选`nums[i]`,

​	如果选择`nums[i]`, 则`f[i][j] = f[i-1][j-nums[i]]`; 如果不选择`nums[i]`, 则`f[i][j] = f[i-1][j]`. **这两种情况中，只需要满足一种为true，即可以认为是正常划分。**

由于必须要考虑下标值非负的情况，所以`j`也判断一下是否大于`nums[i]`。



```c++
// 没有优化空间的情况
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum & 1) return false;
        
        sum /= 2;
        vector<vector<bool>> f(nums.size(), 
                    vector<bool>(sum + 1, false));
        // 边界条件表示从第0个物品中选，sum = 0 的物品，当然可以选择出来，因为不选第0个物品即可
        f[0][0] = true;
        // 与上面的语句类似，当选择第0个物品时，f[0][nums[0]] = true; 但是这一行不能要 因为第二维最大是sum, 而sum/=2后 数组中第一个数很可能会超过sum
        // f[0][nums[0]] = true;
        for(int i = 1; i < nums.size(); i ++){
            for(int j = 0; j <= sum; j ++){
                f[i][j] = f[i-1][j];
                if(j >= nums[i])    f[i][j] = f[i][j] | 
                                    f[i - 1][ j - nums[i] ];
            }
        }
        return f[nums.size() - 1][sum];
    }
};



// 优化空间复杂度
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(auto i : nums){
            sum += i;
        }
        if(sum & 1) return false;
        
        sum /= 2;
        vector<bool> f(sum + 1);
        // 这里设置为true的原因是
        // 当从nums[0]中选，并且能否凑出总和为0的方案，结果当然是可以，只要不选第一个元素即可。
        f[0] = true;
        for(int i = 1; i < nums.size(); i ++){
            for(int j = sum; j >= nums[i]; j --){
                f[j] = f[j] | f[ j - nums[i] ];
            }
        }

        return f[sum];
        
    }
};
```



### 变形Leetcode 474[一和零](https://leetcode-cn.com/problems/ones-and-zeroes/)

```c++
// 三维初始版本
const int C = 610, N = 110;
class Solution {
public:
    int f[C][N][N];
    int findMaxForm(vector<string>& strs, int m, int n) {
        int sz = strs.size();
        for(int k = 1; k <= sz; k ++){
            string str = strs[k-1];
            int count1 = 0, count0 = 0;
            for(auto c : str){
                if(c == '0')    count0 ++;
                else    count1 ++;
            }
            // 注意这里的费用开销一定要从0开始！从初始没有费用开始
            for(int i = 0; i <= m; i ++){
                for(int j = 0; j <= n; j ++){
                    f[k][i][j] = f[k-1][i][j];
                    if(i >= count0 && j >= count1){
                        f[k][i][j] = max(f[k][i][j], f[k-1][i-count0][j - count1] + 1);
                    }
                }
            }
        }
        return f[sz][m][n];
    }
};


// 二维压缩空间版本
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int sz = strs.size();
        vector<vector<int>> f = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        for(auto str : strs){
            int a = 0, b = 0;
            for(auto c : str){
                if(c == '0') a++;
                else b ++;
            }
            for(int i = m; i >= a; i --){
                for(int j = n; j >= b; j --){
                    f[i][j] = max(f[i][j] , f[i - a][j - b] + 1);
                }
            }

        }
        return f[m][n];
    }
};
```





### 完全背包问题Leetcode变种: 完全平方数问题

> https://leetcode-cn.com/problems/perfect-squares/

给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。

给你一个整数 n ，返回和为 n 的完全平方数的 最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

```
示例 1：

输入：n = 12
输出：3 
解释：12 = 4 + 4 + 4

示例 2：

输入：n = 13
输出：2
解释：13 = 4 + 9
```



#### 思路

可以把正整数n看成是背包的总体积，而把背包中的所有物品的体积看成是完全平方数1，4，9，16....; 每个物品都可以取无限次，同时所有物品的价值都看成1，求问所有选法中，价值最少是多少。

- 设`f[i]`为从前`i`个物品中选的所有选法。
- 属性是min, 表示`f[i] = x`里`x`是最小价值。
- 分解子问题：从1枚举到i中的所有完全平方数，取其中最小的价值。

```c++
class Solution {
public:
    int numSquares(int n) {
        vector<int> f(n + 1, n);
        f[0] = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= i / j; j ++){
                // min()括号中第二部分，经典先不取j*j，再把值 + 1; 
                f[i] = min(f[i], f[i - j * j] + 1);
            }
        }
        return f[n];
    }
};
```
