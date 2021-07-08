#include<iostream>

using namespace std;
/* the matrix prefit sum: the Q : to calculate the sum in a submatrix; 
*  question1 : how to calculate the S[i][j]
*  question2 : how to convert the S[i][j] to the res;
*  
*  S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + mat[i][j];
*  submatrix sum = S[x2][y2] - S[x1-1][y2] - S[x2][y1-1] + S[x1-1][y1-1]
*/
const int N = 1010;
int mat[N][N];
int S[N][N];
int main(){
    int m,n,q;
    cin >> m >> n >> q;
    for(int i = 1; i<=m; i++){
        for(int j = 1; j<=n; j++){
            cin >> mat[i][j];
            S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + mat[i][j];
        }
    }
    for(int i = 0 ; i < q; i++){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        int res = S[x2][y2] - S[x1-1][y2] - S[x2][y1-1] + S[x1-1][y1-1];
        printf("%d\n",res);
    }
}
