## Flood Fill （洪水填充）算法

从一个**起始节点**开始把**附近与其连通的节点**提取出或填充成不同颜色颜色，直到封闭区域内的所有节点都被处理过为止，是从一个区域中提取若干个连通的点与其他相邻区域区分开(或分别染成不同颜色)的经典算法。



主要使用方法： 队列BFS算法。



### 例题1 ： 池塘计数

> [池塘技术](https://www.acwing.com/problem/content/description/1099/)

题意：给定一片图，W表示地图中该部位有水，水连通的区域形成池塘， 请问池塘有多少块？

注意：8连通，即除了上下左右，还有右上右下，左上左下。

```
输入样例：
10 12
W........WW.
.WWW.....WWW
....WW...WW.
.........WW.
.........W..
..W......W..
.W.W.....WW.
W.W.W.....W.
.W.W......W.
..W.......W.

输出样例：
3
```



**解决方法：**

设置一个`queue`用来bfs遍历存在水的点，用`st[]`表示是否遍历过。 重点是8连通的使用方法。

此题即考察`bfs()`调用的次数。

```cpp
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

int n, m;
const int N = 1010;
char g[N][N];
bool st[N][N];
queue<PII> q;

// 在每次bfs里把已经遍历过的点st[]状态改变
void bfs(int x, int y)
{
    q.push({x, y});
    st[x][y] = true;
    while (q.size()){
        auto t = q.front(); q.pop();
        int a = t.first, b = t.second;
        // 重点掌握8连通的方法
        for (int i = a - 1; i <= a + 1; i ++) {
            for (int j = b - 1; j <= b + 1; j ++) {
                // 把中间的点挖去
                if (i == a && j == b)   continue;
                if (st[i][j] || g[i][j] == '.')     continue;
                if (i < 0 || i >= n || j < 0 || j >= m) continue;
                q.push({i, j});
                st[i][j] = true;
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    getchar();
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j++) {
            scanf("%c", &g[i][j]);
        }
        getchar();
    }

    int res = 0;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (!st[i][j] && g[i][j] == 'W') {
                bfs(i, j);
                res += 1;
            }
        }
    }
    
    printf("%d\n", res);
    
    return 0;
}
```



### 例题2： 城堡问题

> [城堡问题] (https://www.acwing.com/problem/content/1100/)

图1是一个城堡的地形图。

请你编写一个程序，计算城堡一共有多少房间，最大的房间有多大。

城堡被分割成 m∗n个方格区域，每个方格区域可以有0~4面墙。

```
    1   2   3   4   5   6   7  
   #############################
 1 #   |   #   |   #   |   |   #
   #####---#####---#---#####---#
 2 #   #   |   #   #   #   #   #
   #---#####---#####---#####---#
 3 #   |   |   #   #   #   #   #
   #---#########---#####---#---#
 4 #   #   |   |   |   |   #   #
   #############################
           (图 1)

   #  = Wall   
   |  = No wall
   -  = No wall

   方向：上北下南左西右东。
```



**墙体的二进制表示**： 每个方块中墙的特征由数字 P 来描述，我们用1表示西墙，2表示北墙，4表示东墙，8表示南墙，P 为该方块包含墙的数字之和。

例如，如果一个方块的 P 为3，则 3 = 1 + 2，该方块包含西墙和北墙。

城堡的内墙被计算两次，方块(1,1)的南墙同时也是方块(2,1)的北墙。

输入的数据保证城堡至少有两个房间。

输入输出：

```
输入：
4 7 
11 6 11 6 3 10 6 
7 9 6 13 5 15 5 
1 10 12 7 13 7 5 
13 11 10 8 10 12 13 

输出：
5
9
```



**解决方法：**

使用Flood Fill算法，遍历所有的房间，其中的变化在于，一个房间走到另一个房间的时候要判断是否有墙体阻挡。

上下左右的墙都是二进制表示，只需要采用位运算，`if (P >> k & 1 )`判断是否是1即可，是1则有墙。

**这道题的特点是，在bfs里判断所有走过的路径长度。**

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 55;
typedef pair<int, int> PII;

queue<PII> q;
int n, m;
int g[N][N];
bool st[N][N];

// bfs可以直接记录flood fill算法走过的所有面积
int bfs(int x, int y) 
{
    int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
    q.push({x, y});
    st[x][y] = true;
    int area = 0;
    while (q.size()) {
        auto t = q.front();
        q.pop();
        area += 1;
        
        int a = t.first, b = t.second;
        for (int i = 0; i < 4; i ++) {
            int adj_x = a + dx[i], adj_y = b + dy[i];
            if (adj_x < 0 || adj_x >= n || adj_y < 0 || adj_y >= m) continue;
            if (st[adj_x][adj_y])   continue;
            if (g[a][b] >> i & 1)   continue;
            q.push({adj_x, adj_y});
            st[adj_x][adj_y] = true;
        }
    }
    return area;
}

int main()
{
    cin >> n >> m;      // 习惯采用n行, m列
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            cin >> g[i][j];
        }
    }
    
    int area = 0;
    int cnt = 0;
    
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (!st[i][j]) {
                area = max(area, bfs(i, j));
                cnt += 1;
            }
        }
    }
    
    cout << cnt << endl << area << endl;
    return 0;
}
```



### 例题3：山峰和山谷

> [山峰和山谷](https://www.acwing.com/problem/content/1108/)

题意大意：该题主要考察，地图连通块和周围格子之间的关系。

同样是8连通。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> PII;
const int N = 1e3 + 10;
int g[N][N];
bool st[N][N];
queue<PII> q;
int n;

void bfs(int sx, int sy, bool &has_higher, bool &has_lower)
{
    q.push({sx, sy});
    st[sx][sy] = true;
    int res = 0;
    while (q.size()) {
        auto t = q.front();
        q.pop();
        
        int x = t.first, y = t.second;
        for (int i = x - 1; i <= x + 1; i ++ ) {
            for (int j = y - 1; j <= y + 1; j ++) {
                if (i < 0 || i >= n || j < 0 || j >= n) continue;
                if (i == x && j == y) continue;
                if (g[i][j] != g[x][y]){
                    if (g[i][j] > g[x][y])  has_higher = true;
                    else    has_lower = true;
                }else {
                    if (!st[i][j]) {
                        q.push({i, j});
                        st[i][j] = true;                        
                    }
                }
            }
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            cin >> g[i][j];
        }
    }
    
    int cnt_high = 0, cnt_low = 0;
    
    
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (!st[i][j]) {
                bool has_higher = false, has_lower = false;
                bfs(i, j, has_higher, has_lower);
                if (!has_higher)    cnt_high ++;
                if (!has_lower)     cnt_low ++;
            }
        }
    }
    
    cout << cnt_high << " " << cnt_low << endl;
    return 0;
    
}
```



