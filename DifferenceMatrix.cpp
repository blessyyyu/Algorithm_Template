/*
 * @Author: Cyan
 * @Date: 2021-07-06 20:41:55
 * @LastEditors: Cyan
 * @LastEditTime: 2021-07-06 20:41:55
 * @Description: file content
 */
#include<iostream>

using namespace std;

const int N = 1010;
int a[N][N],b[N][N];
int m,n,q;

void insert(int x1, int y1, int x2, int y2,int c){
    b[x1][y1] += c;
    b[x2 + 1][y1] -= c;
    b[x1][y2+1] -= c;
    b[x2+1][y2+1] += c;
}

int main(){
    scanf("%d%d%d",&m,&n,&q);
    for(int i = 1; i<= m; i++)
        for(int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    
    // 初始化b矩阵 为a矩阵的差分矩阵
    for(int i = 1; i<=m; i++)
        for(int j = 1; j<=n; j++)
            insert(i,j,i,j,a[i][j]);
    
    // 输入
    while(q--){
        int x1,y1,x2,y2,c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        insert(x1,y1,x2,y2,c);
    }
    
    // 反过来求前缀和,得到最后的结果
    for(int i = 1; i<=m; i++)
        for(int j = 1; j<=n ; j++)
            b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1];

    // 输出
    for(int i = 1; i <= m; i++){
        for(int j =1 ;j<=n; j++)
            printf("%d ",b[i][j]);
        cout<<endl;
    }
        

}