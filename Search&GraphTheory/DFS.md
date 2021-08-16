## DFS 和 BFS

DFS算法 从数据结构来看：使用栈， 并且每次只需要记录从根节点到目前结点的路径就可以，所需要的空间是`O(h)`的； 

BFS算法 从数据结构来看：使用队列queue, 所需要的空间是$O(2^h)$,  但是BFS第一次扩展到的点，具有"最短路"的性质；

**DFS使用的是一棵树的形式来进行搜索**，一般用递归来做；递归也一般画一棵树

每次存都是取一条路径，并且回溯的时候一定要记得**恢复现场**。

```c++
#include<iostream>

const int N = 10;
int path[N], n;
// st表示记录当前已经有哪些数被使用过了
bool st[N];


// 参数表示的是位置，u = 0表示先看三位数的第0位
void dfs(int u){
    if( u == n){
        for(int i = 0; i< n; i++)   printf("%d ",path[i]);
        printf("\n");
        return;
    }
    for(int i = 0; i<=n; i++){
        if(!st[i]){
            path[u] = i;
            st[i] = true;
            // 向下深搜
            dfs( u + 1);
            // 恢复现场
            path[u] = 0;
            st[i] = false;
        }
    }
}

int main(){
    scanf("%d", &n);
    // 从第0个位置开始看
    dfs(0);
    
    return 0;
}

```





八皇后：

```c++
// 全排列的方式
#include<iostream>

using namespace std;

const int N = 20;

//  全排列的思路
char g[N][N];
int n;
int path[N];
// dg[]表示正对角线， udg[] 表示反对角线
bool col[N], dg[N], udg[N];

void dfs(int u){
    if( u == n){
        for(int i = 0 ; i< n ; i++)  puts(g[i]);
        puts("");
        return;
    }
    
    for(int i = 0; i < n; i ++){
        if(!col[i] && !dg[i + u] && !udg[n - u + i]){
            g[u][i] = 'Q';
            col[i] = dg[u + i] = udg[n - u + i] = true;
            dfs(u + 1);
            col[i] = dg[u + i] = udg[n - u + i] = false;
            g[u][i] = '.';
        }
    }
}

int main(){
    cin >> n;
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0; j < n; j++){
            g[i][j] = '.';
        }
    }
    dfs(0);
    
    return 0;
}
```

