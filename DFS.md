## DFS

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
            dfs( u + 1);
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

